//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FORM_VIEW_HPP
#define CARROT_FORM_VIEW_HPP

#include <carrot/form.hpp>

namespace carrot
{

class form_view final : public form
{
public:
    form_view(form & mat_, long int row_offset_, long int column_offset_);
    virtual ~form_view() = default;

    void set(long int row, long int column, glyph value) override;

private:
    form * mat_;
    long int row_offset_;
    long int column_offset_;
};
}

#endif
