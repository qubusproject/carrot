//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"

#include <carrot/carrot.hpp>

using namespace carrot;

TEST_CASE("Rendering a caret block", "[default_style]")
{
    auto msg = mark_with_caret(make_empty(), 2);

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a caret underline block", "[default_style]")
{
    auto msg = underline_with_caret(text("Test"), 2);

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a check list block", "[default_style]")
{
    auto msg = make_checkbox_list();

    msg.add(true, make_empty());
    msg.add(false, make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering an empty block", "[default_style]")
{
    auto msg = make_empty();

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a frame block", "[default_style]")
{
    auto msg = frame(make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a grid block", "[default_style]")
{
    auto msg = make_grid(2, 2);

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering an indent block", "[default_style]")
{
    auto msg = indent(make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering an irregular grid block", "[default_style]")
{
    auto msg = make_irregular_grid();

    msg.add_to_row(0, make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a line block", "[default_style]")
{
    auto msg = make_line(growth_direction::right);

    msg.add(make_empty());

    auto msg2 = make_line(growth_direction::down);

    msg2.add(make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
    REQUIRE_NOTHROW(render(msg2, form));
}

TEST_CASE("Rendering a list block", "[default_style]")
{
    auto msg = make_list();

    msg.add(make_empty());

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a placeholder block", "[default_style]")
{
    auto msg = placeholder({"test"});

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a progress bar block", "[default_style]")
{
    auto msg = progress_bar(10);

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a test block", "[default_style]")
{
    auto msg = text("Test");

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering an underline block", "[default_style]")
{
    auto msg = underline(text("Test"));

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}

TEST_CASE("Rendering a table block", "[default_style]")
{
    auto msg = make_table(4);

    std::vector<block> columns(4, make_empty());

    msg.add_row(std::move(columns));

    plain_form form;

    REQUIRE_NOTHROW(render(msg, form));
}