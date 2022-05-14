#ifndef STORAGE_INTERFACES_HPP
#define STORAGE_INTERFACES_HPP

#include <string>

class IBaseStorage
{
    virtual bool insert(std::string site, std::string user, std::string password) = 0;

    virtual std::string getPassword(std::string site, std::string user) = 0;

};

class ILocalStorage : public IBaseStorage
{
    virtual void initStorage(std::string fileName) = 0;


};

class IServerStorage : public IBaseStorage
{
    virtual void initStorage(std::string address, int port) = 0;
};

#endif // STORAGE_INTERFACES_HPP