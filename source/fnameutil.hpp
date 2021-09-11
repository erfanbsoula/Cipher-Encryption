#ifndef _FNAMEUTIL_H_
#define _FNAMEUTIL_H_

#include <string>
#include <stdexcept>

const int EXTENTION_LENGTH_LIMIT = 10;

class FileNameUtil
{
public:
    FileNameUtil(std::string file_addr);
    std::string get_file_name() const;
    std::string get_file_extention() const;

protected:
    std::string file_name;
    std::string file_extention;

    std::string find_base_name(std::string file_addr);
    std::string find_extention(std::string file_addr);
};

#endif