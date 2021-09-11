#ifndef _CIPHER_H_
#define _CIPHER_H_

#include <string>
#include <stdexcept>

#include "fnameutil.hpp"
#include "progress.hpp"

class Cipher : public FileNameUtil
{
public:

    enum Mode
    {
        NOT_SET,
        ENCRYPTION,
        DECRYPTION
    };

    static const std::string GEN_EXTENTION;

    Cipher(std::string file_addr);
    void set_output_file_name(std::string output_name_);
    void set_operation_mode(Cipher::Mode mode_);
    void subscribe_to_progress(ProgressSubscriber* subscriber_);
    void process(std::string key);

private:
    Mode mode;
    std::string output_name;
    Psteps file_size;
    ProgressHandler progress_handler;

    std::string complement(const std::string& str);
    void analyze_input_file();
    void check_input_file_extention();
    std::string read_encrypted_file_extention();
};

#endif