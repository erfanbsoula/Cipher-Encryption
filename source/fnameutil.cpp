#include "fnameutil.hpp"

FileNameUtil::FileNameUtil(std::string file_addr)
{
    file_extention = find_extention(file_addr);
    if (file_extention.size() > EXTENTION_LENGTH_LIMIT)
        throw std::runtime_error("ERROR: length of file extention is not supported!");

    file_name = file_addr.substr(0, file_addr.size()-file_extention.size()-(file_extention != ""));
}

std::string FileNameUtil::find_base_name(std::string file_addr)
{
    for (int i = file_addr.size()-1; i >= 0; i--)
        if (file_addr[i] == '/')
            return file_addr.substr(i+1, file_addr.size()-i-1);

    return file_addr;
}

std::string FileNameUtil::find_extention(std::string file_addr)
{
    file_addr = find_base_name(file_addr);
    for (int i = file_addr.size()-1; i > 0; i--)
        if (file_addr[i] == '.')
            return file_addr.substr(i+1, file_addr.size()-i-1);

    return "";
}

std::string FileNameUtil::get_file_name() const { return file_name; }
std::string FileNameUtil::get_file_extention() const { return file_extention; }