#ifndef CRED_MNGMNT_HPP
#define CRED_MNGMNT_HPP

#include <type_traits>
#include <storage_interfaces.hpp>
#include <memory>

template <typename Storage>
class CredentialManager
{
    static_assert(std::is_base_of<IBaseStorage, Storage>::value, "Storage must derive from IBaseStorage");

public:
    // Method for template arguments that are derived from ILocalStorage
    template <typename... Args>
    typename std::enable_if<std::is_base_of<ILocalStorage, Storage>::value> initStorage(std::string fileName, Args... args)
    {
        storage.initStorage(fileName, args...);
    }

    // Method for template arguments that are derived from IServerStorage
    template <typename... Args>
    typename std::enable_if<std::is_base_of<IServerStorage, Storage>::value> initStorage(std::string address, int port, Args... args)
    {
        storage.initStorage(address, port, args...);
    }

    bool insert(std::string site, std::string user, std::string password)
    {
        return storage.insert(site, user, password);
    }

    std::string get(std::string site, std::string user)
    {
        return storage.getPassword(site, user);
    }

private:
    Storage storage;
};

#endif // CRED_MNGMNT_HPP