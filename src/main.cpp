#include <cred_management.hpp>
#include <json_storage.hpp>
#include <sqlite_storage.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace po = boost::program_options;

enum struct StorageType
{
    json,
    sqlite
};

enum struct OpType
{
    insert,
    get
};

const std::vector<std::string> storageTypeAllowedArgs{"json", "sqlite"};
const std::vector<std::string> operationTypeAllowedArgs{"insert", "get"};

int main(int argc, char const *argv[])
{
    std::string helpMessage = "Credential Manager\n"
                              "Usage: " +
                              std::string(argv[0]) + " --type <storage type> [storage parameters] --operation <op> <site> <user> [<password>]\n"
                                                     "Arguments";

    std::string type, op, site, user, password;

    std::string tableName;

    po::options_description desc(helpMessage);
    desc.add_options()("help,h", "help message")("type,t", po::value<std::string>(&type)->required(), "set storage type (json, sqlite)")("file,f", po::value<std::string>(), "file name")("table,T", po::value<std::string>(&tableName)->default_value("credentials"), "file name")("operation,o", po::value<std::string>(&op)->required(), "operation (insert, get)")("site", po::value<std::string>(&site)->required())("user", po::value<std::string>(&user)->required())("password", po::value<std::string>(&password));

    po::positional_options_description positionalArgs;
    positionalArgs.add("site", 1).add("user", 1).add("password", 1);

    po::variables_map vm;

    StorageType storageType;
    OpType opType;

    std::string fileName;

    try
    {

        po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalArgs).run(), vm);
        po::notify(vm);

        if (vm.count("help") || argc == 1)
        {
            throw std::runtime_error("Dummy error");
        }

        if (std::find(storageTypeAllowedArgs.begin(), storageTypeAllowedArgs.end(), type) == storageTypeAllowedArgs.end())
        {
            throw std::invalid_argument("invalid value for option '--type'");
        }

        if (type == "json")
        {
            storageType = StorageType::json;
            if (!vm.count("file"))
            {
                throw std::runtime_error("the option '--file' is required whe storage type is json");
            }
            fileName = vm["file"].as<std::string>();
        }

        if (type == "sqlite")
        {
            storageType = StorageType::sqlite;
            if (!vm.count("file"))
            {
                throw std::runtime_error("the option '--file' is required whe storage type is sqlite");
            }
            fileName = vm["file"].as<std::string>();
        }

        if (std::find(operationTypeAllowedArgs.begin(), operationTypeAllowedArgs.end(), op) == operationTypeAllowedArgs.end())
        {
            throw std::invalid_argument("invalid value for option '--operation'");
        }

        if (op == "insert")
        {
            opType = OpType::insert;

            if (!vm.count("password"))
            {
                throw std::runtime_error("the paramter <password> is required when inserting");
            }

            site = vm["site"].as<std::string>();
            user = vm["user"].as<std::string>();
            password = vm["password"].as<std::string>();
        }

        if (op == "get")
        {
            opType = OpType::get;

            site = vm["site"].as<std::string>();
            user = vm["user"].as<std::string>();
        }
    }
    catch (std::exception &e)
    {
        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        std::cerr << "ERROR: " << e.what() << std::endl
                  << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }

    try
    {

        switch (storageType)
        {
        case StorageType::json:
        {
            CredentialManager<JsonStorage> credJson;
            credJson.initStorage(fileName);

            switch (opType)
            {
            case OpType::insert:
                if (!credJson.insert(site, user, password))
                    throw std::runtime_error("failed to insert data");
                break;
            case OpType::get:
                auto result = credJson.get(site, user);
                if (result.empty())
                    std::cout << "Not found!" << std::endl;
                else
                    std::cout << site + " " + user + " " + result << std::endl;
            }
            break;
        }

        case StorageType::sqlite:
        {
            CredentialManager<SqliteStorage> credSqlite;
            credSqlite.initStorage(fileName, tableName);

            switch (opType)
            {
            case OpType::insert:
                if (!credSqlite.insert(site, user, password))
                    throw std::runtime_error("failed to insert data");
                break;
            case OpType::get:
                auto result = credSqlite.get(site, user);
                if (result.empty())
                    std::cout << "Not found!" << std::endl;
                else
                    std::cout << site + "\t" + user + "\t" + result << std::endl;
            }
            break;
        }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
