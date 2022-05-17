#include <sqlite_storage.hpp>
#include <stdexcept>

void SqliteStorage::init(std::string fileName, spanArgs args)
{

    db = SQLite::Database(fileName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    table = "credentials";

    if (!args.empty())
    {
        table = std::get<std::string>(args[0]);
    }

    SQLite::Statement create(db, "CREATE TABLE IF NOT EXISTS ?("
                                 "site TEXT NOT NULL,"
                                 "user TEXT NOT NULL,"
                                 "password TEXT NOT NULL,"
                                 "PRIMARY_KEY(site, user);");

    create.bind(1, table);

    create.exec();
}

bool SqliteStorage::insert(std::string site, std::string user, std::string password)
{
    SQLite::Statement replace(db, "REPLACE INTO ? (site, user,password) "
                                  "VALUES(?, ?, ?);");

    replace.bind(1, table);
    replace.bind(2, site);
    replace.bind(3, user);
    replace.bind(4, password);

    return replace.exec() != 0;
}

std::string SqliteStorage::getPassword(std::string site, std::string user)
{
    SQLite::Statement select(db, "SELECT password FROM ?"
                                 "WHERE site = ? AND user = ?"
                                 "LIMIT 1;");

    select.bind(1, table);
    select.bind(2, site);
    select.bind(3, user);

    std::string password;
    while(select.executeStep()){
        const char *val = select.getColumn("password");
        password = val;
    }

    return password;
}