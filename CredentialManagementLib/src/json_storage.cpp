#include <json_storage.hpp>

void JsonStorage::initStorage(std::string fileName)
{
    file.open(fileName, std::fstream::in | std::fstream::out);
    file >> data;
}

bool JsonStorage::insert(std::string site, std::string user, std::string password)
{

    data[site][user] = password;
}