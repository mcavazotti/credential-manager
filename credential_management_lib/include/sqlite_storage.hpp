#ifndef SQLITE_STORAGE_HPP
#define SQLITE_STORAGE_HPP

#include <storage_interfaces.hpp>
#include <SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h>
#include <memory>

class SqliteStorage : public ILocalStorage
{
public:
    void init(std::string fileName, spanArgs args) override;

    bool insert(std::string site, std::string user, std::string password) override;

    std::string getPassword(std::string site, std::string user) override;

private:

    SQLite::Database db;
    std::string fileName;
    std::string table;
};

#endif // SQLITE_STORAGE_HPP
