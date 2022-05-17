# credential-manager
C++ project for a Recruitment Challenge

## Cloning
This project contains a submodule, therefore it must be cloned with the option `--recursive`

## Building
```sh
cd credential-manager
cmake -S . -B ./build
make -C build
```
Executable will be generated in `build/bin`

## About security
Here are some of its security flaws:
- Passwords are typed in the command line (it means they get stored in the terminal history)
- There is no sanitization of user input for the SQLite storage
- Passwords are not encrypted before saving.
