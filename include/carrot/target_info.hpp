//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TARGET_INFO_HPP
#define CARROT_TARGET_INFO_HPP

#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <locale>
#include <stdexcept>

namespace carrot
{

class CARROT_EXPORT invalid_target_error : public virtual exception, public virtual std::logic_error
{
public:
    explicit invalid_target_error(const std::string& reason_);
};

class CARROT_EXPORT target_info
{
public:
    explicit target_info(const std::locale& locale_, bool supports_colorized_output_,
                         long int tab_width_);

    [[nodiscard]] bool supports_colorized_output() const;
    [[nodiscard]] long int tab_width() const;
    [[nodiscard]] const std::locale& locale() const;

private:
    std::locale locale_;
    bool supports_colorized_output_;
    long int tab_width_;
};

[[nodiscard]] CARROT_EXPORT target_info get_stdout_target(long int tab_width = 4);
[[nodiscard]] CARROT_EXPORT target_info get_stdout_target(const std::locale& locale,
                                                          long int tab_width = 4);

[[nodiscard]] CARROT_EXPORT target_info get_file_target(long int tab_width = 4);
[[nodiscard]] CARROT_EXPORT target_info get_file_target(const std::locale& locale,
                                                        long int tab_width = 4);

[[nodiscard]] CARROT_EXPORT target_info get_colorized_target(long int tab_width = 4);
[[nodiscard]] CARROT_EXPORT target_info get_colorized_target(const std::locale& locale,
                                                             long int tab_width = 4);

} // namespace carrot

#endif
