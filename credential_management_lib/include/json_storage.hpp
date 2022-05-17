#ifndef JSON_STORAGE_HPP
#define JSON_STORAGE_HPP

#include <storage_interfaces.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

class JsonStorage : public ILocalStorage
{
public:
    void init(std::string fileName, spanArgs args) override;

    bool insert(std::string site, std::string user, std::string password) override;

    std::string getPassword(std::string site, std::string user) override;

    ~JsonStorage()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

private:
    nlohmann::json data;
    std::fstream file;
    std::string fName;
};

#endif // JSON_STORAGE_HPP