//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PLAIN_FORM_HPP
#define CARROT_PLAIN_FORM_HPP

#include <carrot/form.hpp>

#include <string>

namespace carrot
{
class plain_form final : public form
{
public:
    plain_form(long int rows_ = 0, long int columns_ = 0);

    virtual ~plain_form() = default;

    void set(long int row, long int column, glyph value) override;

    std::string to_string(const target_info& target) const;

    void clear();
    void clear(glyph value);
private:
    void resize_if_outside_matrix(long int row, long int column);

    boost::multi_array<glyph, 2> data_;
    glyph clear_glyph_;
};
}

#endif
