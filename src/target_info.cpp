#include <carrot/target_info.hpp>

namespace carrot
{

target_info::target_info(bool supports_colorized_output_, long int tab_width_)
: supports_colorized_output_(supports_colorized_output_), tab_width_(tab_width_)
{
}

bool target_info::supports_colorized_output() const
{
    return supports_colorized_output_;
}

long int target_info::tab_width() const
{
    return tab_width_;
}

target_info get_stdout_target(long int tab_width)
{
    return target_info(false, tab_width);
}

target_info get_file_target(long int tab_width)
{
    return target_info(false, tab_width);
}

}