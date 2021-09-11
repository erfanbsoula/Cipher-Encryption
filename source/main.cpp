#include <string>
#include <stdexcept>
#include <iostream>

#include "cipher.hpp"
#include "console/progbar.hpp"

Cipher::Mode detect_mode(std::string mode)
{
    if (mode == "-e" || mode == "encrypt")
        return Cipher::Mode::ENCRYPTION;
    if (mode == "-d" || mode == "decrypt")
        return Cipher::Mode::DECRYPTION;

    throw std::runtime_error("ERROR: invalid command!");
}

bool output_command_is_valid(std::string command, std::string output_addr)
{
    return (command == "-o" || command == "output") &&
        output_addr.length() > 0;
}

void execute(int argc, char* argv[])
{
    if (argc != 3 && argc != 5)
        throw std::runtime_error("ERROR: ivalid input argument!");

    Cipher::Mode mode = detect_mode(argv[1]);
    Cipher cipher(argv[2]);
    cipher.set_operation_mode(mode);
    cipher.subscribe_to_progress(new ConsoleProgressBar);

    if (argc == 5)
        if (output_command_is_valid(argv[3], argv[4]))
            cipher.set_output_file_name(argv[4]);

    std::string key;
    std::cout << "key: ";
    std::cin >> key;

    cipher.process(key);
    std::cout << "\ndone!" << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        execute(argc, argv);
        return 0;
    }
    catch(const std::exception& error)
    {
        std::cout << error.what() << std::endl;
        return -1;
    }
}