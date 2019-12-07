//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_EXCEPTION_HPP
#define CARROT_EXCEPTION_HPP

#include "carrot_export.hpp"

#include <exception>
#include <stdexcept>
#include <utility>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief The base class for all exceptions thrown by carrot.
 */
class CARROT_EXPORT exception : public std::exception
{
};

/** @brief A runtime error thrown by carrot.
 */
class CARROT_EXPORT runtime_error : public virtual exception
{
public:
    explicit runtime_error(std::string message)
    : m_message(std::move(message))
    {
    }

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }
private:
    std::string m_message;
};

}

#endif
