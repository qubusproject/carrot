#include <carrot/target_info.hpp>

#ifdef __unix__

#include <unistd.h>

#endif

#ifdef HAVE_TERMINFO

extern "C" int setupterm(char* term, int filedes, int* errret);
extern "C" struct term* set_curterm(struct term* termp);
extern "C" int del_curterm(struct term* termp);
extern "C" int tigetnum(char* capname);

#include <mutex>

#endif

namespace carrot
{

namespace
{

#ifdef HAVE_TERMINFO
std::mutex term_mutex;
#endif

bool terminal_has_colors(int fd)
{
#ifdef HAVE_TERMINFO
    std::lock_guard<std::mutex> guard(term_mutex);

    int errret = 0;
    if (setupterm(static_cast<char*>(nullptr), fd, &errret) != 0)
        return false;

    bool has_colors = tigetnum(const_cast<char*>("colors")) > 0;

    struct term* termp = set_curterm(static_cast<struct term*>(nullptr));
    (void)del_curterm(termp);

    if (has_colors)
        return true;
#endif
    return false;
}

bool has_color_support(int fd)
{
#ifdef __unix__
    return isatty(fd) && terminal_has_colors(fd);
#else
    return false;
#endif
}
}

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
#ifdef __unix__
    bool colorize_output = has_color_support(STDOUT_FILENO);
#else
    bool colorize_output = false;
#endif
    return target_info(colorize_output, tab_width);
}

target_info get_file_target(long int tab_width)
{
    return target_info(false, tab_width);
}
}