#include <cred_management.hpp>
#include <json_storage.hpp>

int main(int argc, char const *argv[])
{
    CredentialManager<JsonStorage> cred;

    cred.initStorage("teste.json");
    cred.insert("google.com","mcavazotti","1234");
    cred.insert("google.com","hacker","2323");
    cred.insert("google.com","booty","asdasd");

    return 0;
}
