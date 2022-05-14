#ifndef CRED_MNGMNT_HPP
#define CRED_MNGMNT_HPP

#include <type_traits>
#include <storage_interfaces.hpp>
#include <memory>

template <typename Storage, typename _ = void>
class CredentialManager
{
    static_assert(std::is_base_of<IBaseStorage, Storage>::value, "Storage must derive from IBaseStorage");

public:


private:
    Storage storage;
};

#endif // CRED_MNGMNT_HPP