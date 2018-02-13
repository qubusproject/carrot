//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/target_info.hpp>

#include <boost/locale/boundary/facets.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/info.hpp>

#ifdef __unix__

#include <unistd.h>

#endif

#ifdef HAVE_TERMINFO

extern "C" int setupterm(char* term, int filedes, int* errret);
extern "C" struct term* set_curterm(struct term* termp);
extern "C" int del_curterm(struct term* termp);
extern "C" int tigetnum(char* capname);

#include <locale>
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
    bool is_a_tty = isatty(fd) > 0;
    bool has_colors = terminal_has_colors(fd);

    return is_a_tty && has_colors;
#else
    return false;
#endif
}
}

invalid_target_error::invalid_target_error(const std::string& reason_)
: std::logic_error("Invalid target: " + reason_)
{
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

target_info get_colorized_target(long int tab_width)
{
    return target_info(true, tab_width);
}

const std::locale& get_locale()
{
    using namespace boost::locale;

    static const std::locale loc = [] {
        generator gen;

        auto loc = gen("");

        try
        {
            const auto& info = std::use_facet<boost::locale::info>(loc);

            if (!info.utf8())
                throw invalid_target_error("The target's encoding is not UTF-8.");

            bool supports_boundary_indexing =
                std::has_facet<boost::locale::boundary::boundary_indexing<char>>(loc);

            if (!supports_boundary_indexing)
                throw invalid_target_error("Boundary indexing is not supported by the native "
                                           "locale. Maybe ICU is not detected correctly.");

            return loc;
        }
        catch (const std::bad_cast&)
        {
            throw invalid_target_error("Invalid locale '" + loc.name() +
                                       "': Locale info is unavailable.");
        }
    }();

    return loc;
}
}