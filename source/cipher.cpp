#include "cipher.hpp"
#include <fstream>

const std::string Cipher::GEN_EXTENTION = "locked";

Cipher::Cipher(std::string file_addr)
    : FileNameUtil(file_addr)
{
    mode = Mode::NOT_SET;
    analyze_input_file();
    output_name = file_name;
}

void Cipher::analyze_input_file()
{
    std::ifstream source_file(file_name + "." + file_extention, std::ios::binary);
    if (!source_file.good())
        throw std::runtime_error("ERROR: couldn't open the input file!");

    source_file.seekg(0, std::ios::end);
    file_size = source_file.tellg();
    source_file.close();
}

void Cipher::check_input_file_extention()
{
    if (file_extention != GEN_EXTENTION)
        throw std::runtime_error("ERROR: unrecognized file extention! ("+file_extention+")");
}

std::string Cipher::read_encrypted_file_extention()
{
    std::ifstream source_file(file_name + "." + GEN_EXTENTION, std::ios::binary);
    source_file >> std::noskipws;
    int len = 0;
    std::string extention = "";
    char buf;
    while (source_file >> buf && len < EXTENTION_LENGTH_LIMIT)
    {
        if (buf == '\n')
        {
            source_file.close();
            file_size -= len + 1;
            return extention;
        }
        extention += buf;
        len += 1;
    }

    source_file.close();
    throw std::runtime_error("ERROR: could'nt detect encrypted file extention!");
}

void Cipher::set_output_file_name(std::string output_name_)
{
    if (output_name_.length() < 1)
        throw std::runtime_error("ERROR: invalid name for output file!");

    output_name = output_name_;
}

void Cipher::set_operation_mode(Cipher::Mode mode_)
{
    mode = mode_;
    if (mode == Mode::DECRYPTION)
    {
        check_input_file_extention();
        file_extention = read_encrypted_file_extention();
    }
}

void Cipher::subscribe_to_progress(ProgressSubscriber* subscriber_)
{
    progress_handler.subscribe(subscriber_);
}

std::string Cipher::complement(const std::string& str)
{
    std::string res;
    for (int i = 0; i < str.length(); i++)
        res += static_cast<char>(256 - str[i]);

    return res;
}

void Cipher::process(std::string key)
{
    if (mode == Mode::NOT_SET)
        throw std::runtime_error("ERROR: operation mode is not set!");

    std::ifstream source_file;
    std::ofstream output_file;

    if (mode == Mode::ENCRYPTION)
    {
        source_file.open(file_name + "." + file_extention, std::ios::binary);
        output_file.open(output_name + "." + GEN_EXTENTION, std::ios::binary);
    }
    else if (mode == Mode::DECRYPTION)
    {
        source_file.open(file_name + "." + GEN_EXTENTION, std::ios::binary);
        output_file.open(output_name + "." + file_extention, std::ios::binary);
        key = complement(key);
    }

    if (!source_file.good())
        throw std::runtime_error("ERROR: couldn't open the input file!");
    if (!output_file.good())
        throw std::runtime_error("ERROR: couldn't write the output file!");

    source_file >> std::noskipws;

    if (mode == Mode::ENCRYPTION)
        output_file << file_extention << "\n";

    else if (mode == Mode::DECRYPTION)
        source_file.ignore(EXTENTION_LENGTH_LIMIT, '\n');

    progress_handler.initialize_new_process(file_size);

    int cur = 0;
    const int len = key.size();
    char buf;
    while (source_file >> buf)
    {
        buf += key[cur++];
        output_file << buf;
        cur %= len;
        progress_handler.update();
    }

    source_file.close();
    output_file.close();
}