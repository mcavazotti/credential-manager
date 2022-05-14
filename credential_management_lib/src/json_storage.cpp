#include <json_storage.hpp>
#include <iostream>

void JsonStorage::initStorage(std::string fileName)
{
    fName = fileName;
    file.open(fileName, std::fstream::in | std::fstream::out);
    if (!file.is_open())
    {
        file.open(fileName, std::fstream::out);
    }
    if (file.peek() != std::fstream::traits_type::eof())
    {
        file >> data;
    }
}

bool JsonStorage::insert(std::string site, std::string user, std::string password)
{
    try
    {
        data[site][user] = password;
        file.close();
        file.open(fName, std::fstream::in | std::fstream::out | std::fstream::trunc);
        file << data;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

std::string JsonStorage::getPassword(std::string site, std::string user)
{
    if (data.contains(site) && data[site].contains(user))
    {
        return data[site][user];
    }
    else
    {
        return nullptr;
    }
}