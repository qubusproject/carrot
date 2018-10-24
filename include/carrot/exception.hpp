//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_EXCEPTION_HPP
#define CARROT_EXCEPTION_HPP

#include "carrot_export.hpp"

#include <exception>
#include <stdexcept>

namespace carrot
{

class CARROT_EXPORT exception : public std::exception
{
};

class CARROT_EXPORT runtime_error : public virtual exception, public virtual std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}

#endif
