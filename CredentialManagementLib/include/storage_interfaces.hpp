#ifndef STORAGE_INTERFACES_HPP
#define STORAGE_INTERFACES_HPP

#include <string>

class IBaseStorage
{
    virtual bool insert(std::string site, std::string user, std::string password);

    virtual std::string getPassword(std::string site, std::string user);
};

class ITextStorage : public IBaseStorage
{
    virtual void initStorage(std::string fileName);
};

class IDBStorage : public IBaseStorage
{
    virtual void initStorage(std::string address, int port);
};

#endif // STORAGE_INTERFACES_HPP