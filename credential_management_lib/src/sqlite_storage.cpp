#include <sqlite_storage.hpp>
#include <stdexcept>

void SqliteStorage::init(std::string fileName, spanArgs args)
{
    int returnCode = sqlite3_open(fileName.c_str(), &db);
    if(returnCode) {
        sqlite3_close(db);
        throw new std::runtime_error("Couldn't open sqlite database");
    }

    table = "credentials";

    if(!args.empty()) {
        table = std::get<std::string>(args[0]);
    }

}