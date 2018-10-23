//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TARGET_INFO_HPP
#define CARROT_TARGET_INFO_HPP

#include <carrot/exception.hpp>

#include <locale>
#include <stdexcept>

namespace carrot
{

class invalid_target_error : public virtual exception, public virtual std::logic_error
{
public:
    explicit invalid_target_error(const std::string& reason_);
};

class target_info
{
public:
    explicit target_info(bool supports_colorized_output_, long int tab_width_);

    bool supports_colorized_output() const;
    long int tab_width() const;
    const std::locale& locale() const;

private:
    bool supports_colorized_output_;
    long int tab_width_;
};

target_info get_stdout_target(long int tab_width = 4);
target_info get_file_target(long int tab_width = 4);
target_info get_colorized_target(long int tab_width = 4);

}

#endif
