//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FORM_VIEW_HPP
#define CARROT_FORM_VIEW_HPP

#include <carrot/form.hpp>

#include "carrot_export.hpp"

namespace carrot
{

class CARROT_EXPORT form_view final : public form
{
public:
    form_view(form & base_form_, long int row_offset_, long int column_offset_);
    virtual ~form_view() = default;

    void set(long int row, long int column, glyph value) override;

    const target_info& target() const override;
private:
    form* base_form_;
    long int row_offset_;
    long int column_offset_;
};
}

#endif
