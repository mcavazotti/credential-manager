#ifndef STORAGE_INTERFACES_HPP
#define STORAGE_INTERFACES_HPP

#include <string>
#include <array>
#include <variant>
#include <tcb/span.hpp>

typedef tcb::span<std::variant<std::string, int>> spanArgs;

class IBaseStorage
{
public:
    virtual bool insert(std::string site, std::string user, std::string password) = 0;

    virtual std::string getPassword(std::string site, std::string user) = 0;
};

class ILocalStorage : public IBaseStorage
{
public:
    template <typename... Args>
    void initStorage(std::string fileName, Args... args)
    {
        std::array<std::variant<std::string, int>, sizeof...(Args)> arguments = {std::variant<std::string, int>{std::forward<Args>(args)}...};

        init(fileName, arguments);
    }

private:
    virtual void init(std::string fileName, spanArgs args) = 0;
};

class IServerStorage : public IBaseStorage
{
public:
    template <typename... Args>
    void initStorage(std::string address, int port, Args... args)
    {
        std::array<std::variant<std::string, int>, sizeof...(Args)> arguments = {std::variant<std::string, int>{std::forward<Args>(args)}...};

        init(address, port, arguments);
    }

private:
    virtual void init(std::string address, int port, spanArgs args) = 0;
};

#endif // STORAGE_INTERFACES_HPP