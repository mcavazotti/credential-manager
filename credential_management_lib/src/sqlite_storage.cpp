#include <sqlite_storage.hpp>
#include <stdexcept>
#include <iostream>

void SqliteStorage::init(std::string fileName, spanArgs args)
{

    db = std::make_unique<SQLite::Database>(fileName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    table = "credentials";

    if (!args.empty())
    {
        table = std::get<std::string>(args[0]);
    }
    SQLite::Statement create(*db, "CREATE TABLE IF NOT EXISTS " + table + " ("
                                                                          "site TEXT NOT NULL,"
                                                                          "user TEXT NOT NULL,"
                                                                          "password TEXT NOT NULL,"
                                                                          "PRIMARY KEY (site, user));");

    // create.bind(1, );
    create.exec();
}

bool SqliteStorage::insert(std::string site, std::string user, std::string password)
{
    SQLite::Statement replace(*db, "REPLACE INTO " + table + " (site, user,password) "
                                                             "VALUES(?, ?, ?);");

    replace.bind(1, site);
    replace.bind(2, user);
    replace.bind(3, password);

    return replace.exec() != 0;
}

std::string SqliteStorage::getPassword(std::string site, std::string user)
{
    SQLite::Statement select(*db, "SELECT password FROM " + table + " "
                                                                    "WHERE site = ? AND user = ?"
                                                                    "LIMIT 1;");

    select.bind(1, site);
    select.bind(2, user);

    std::string password;
    while (select.executeStep())
    {
        const char *val = select.getColumn("password");
        password = val;
    }

    return password;
}