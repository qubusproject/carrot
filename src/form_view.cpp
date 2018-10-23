//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/form_view.hpp>

namespace carrot
{

form_view::form_view(form & base_form_, long int row_offset_, long int column_offset_)
: base_form_(&base_form_), row_offset_(row_offset_), column_offset_(column_offset_)
{
}

void form_view::set(long int row, long int column, glyph value)
{
    base_form_->set(row_offset_ + row, column_offset_ + column, value);
}

const target_info& form_view::target() const
{
    return base_form_->target();
}
}