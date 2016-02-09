#ifndef CARROT_TARGET_INFO_HPP
#define CARROT_TARGET_INFO_HPP

namespace carrot
{

class target_info
{
public:
    explicit target_info(bool supports_colorized_output_, long int tab_width_);

    bool supports_colorized_output() const;
    long int tab_width() const;
private:
    bool supports_colorized_output_;
    long int tab_width_;
};

target_info get_stdout_target(long int tab_width = 4);
target_info get_file_target(long int tab_width = 4);

}

#endif
