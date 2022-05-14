#ifndef STORAGES_HPP
#define STORAGES_HPP

#include <storage_interfaces.hpp>
#include <external/nlohmann/json.hpp>
#include <fstream>

class JsonStorage : public ILocalStorage
{
public:
    void initStorage(std::string fileName) override;

    bool insert(std::string site, std::string user, std::string password) override;

    std::string getPassword(std::string site, std::string user) override;

private:
    nlohmann::json data;
    std::fstream file;
    std::string fName;
};

#endif // STORAGES_HPP