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
    typename std::enable_if<std::is_base_of<ILocalStorage, Storage>::value, void> initStorage(std::string fileName)
    {
        storage.initStorage(fileName);
    }

    typename std::enable_if<std::is_base_of<IServerStorage, Storage>::value, void> initStorage(std::string address, int port);

    bool insert(std::string site, std::string user, std::string password) {
        return storage.insert(site, user, password);
    }

private:
    Storage storage;
};

#endif // CRED_MNGMNT_HPP