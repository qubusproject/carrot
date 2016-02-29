//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/form_view.hpp>

namespace carrot
{

form_view::form_view(form & mat_, long int row_offset_, long int column_offset_)
: mat_(&mat_), row_offset_(row_offset_), column_offset_(column_offset_)
{
}

void form_view::set(long int row, long int column, glyph value)
{
    mat_->set(row_offset_ + row, column_offset_ + column, value);
}
}