//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>

#include <carrot/carrot.hpp>

using namespace carrot;

TEST(default_style, caret_block)
{
    auto msg = mark_with_caret(make_empty(), 2);

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, caret_underline_block)
{
    auto msg = underline_with_caret(text("Test"), 2);

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, checkbox_list_block)
{
    auto msg = make_checkbox_list();

    msg.add(true, make_empty());
    msg.add(false, make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, empty_block)
{
    auto msg = make_empty();

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, frame_block)
{
    auto msg = frame(make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, grid_block)
{
    auto msg = make_grid(2, 2);

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, indent_block)
{
    auto msg = indent(make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, irregular_grid_block)
{
    auto msg = make_irregular_grid();

    msg.add_to_row(0, make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, line_block)
{
    auto msg = make_line(growth_direction::right);

    msg.add(make_empty());

    auto msg2 = make_line(growth_direction::down);

    msg2.add(make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
    EXPECT_NO_THROW(render(msg2, form));
}

TEST(default_style, list_block)
{
    auto msg = make_list();

    msg.add(make_empty());

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, placeholder_block)
{
    auto msg = placeholder({"test"});

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, progress_bar_block)
{
    auto msg = progress_bar(10);

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, text_block)
{
    auto msg = text("Test");

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, underline_block)
{
    auto msg = underline(text("Test"));

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}

TEST(default_style, table_block)
{
    auto msg = make_table(4);

    std::vector<block> columns(4, make_empty());

    msg.add_row(std::move(columns));

    plain_form form;

    EXPECT_NO_THROW(render(msg, form));
}