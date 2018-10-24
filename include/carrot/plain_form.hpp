//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PLAIN_FORM_HPP
#define CARROT_PLAIN_FORM_HPP

#include <carrot/form.hpp>
#include <carrot/target_info.hpp>

#include "carrot_export.hpp"

#include <string>

namespace carrot
{
class CARROT_EXPORT plain_form final : public form
{
public:
    plain_form(target_info target_, long int rows_ = 0, long int columns_ = 0);

    virtual ~plain_form() = default;

    void set(long int row, long int column, glyph value) override;

    const target_info& target() const override;

    std::string to_string() const;

    void clear();
    void clear(glyph value);

private:
    void resize_if_outside_matrix(long int row, long int column);

    target_info target_;
    boost::multi_array<glyph, 2> data_;
    glyph clear_glyph_;
};
} // namespace carrot

#endif
