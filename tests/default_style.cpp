//  Copyright (c) 2017-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"

#include <carrot/carrot.hpp>

using namespace carrot;

TEST_CASE("Rendering", "[default_style]")
{
    plain_form form(get_stdout_target());

    SECTION(" a caret block")
    {
        auto msg = mark_with_caret(make_empty(), 2);

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a caret underline block", "[default_style]")
    {
        auto msg = underline_with_caret(text("Test"), 2);

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a check list block", "[default_style]")
    {
        auto msg = make_checkbox_list();

        msg.add(true, make_empty());
        msg.add(false, make_empty());

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" an empty block", "[default_style]")
    {
        auto msg = make_empty();

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a frame block", "[default_style]")
    {
        auto msg = frame(make_empty());

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a grid block", "[default_style]")
    {
        auto msg = make_grid(2, 2);

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" an indent block", "[default_style]")
    {
        auto msg = indent(make_empty());

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" an irregular grid block", "[default_style]")
    {
        auto msg = make_irregular_grid();

        msg.add_to_row(0, make_empty());

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a line block", "[default_style]")
    {
        auto msg = make_line(growth_direction::right);

        msg.add(make_empty());

        auto msg2 = make_line(growth_direction::down);

        msg2.add(make_empty());

        REQUIRE_NOTHROW(render(msg, form));
        REQUIRE_NOTHROW(render(msg2, form));
    }

    SECTION(" a list block", "[default_style]")
    {
        auto msg = make_list();

        msg.add(make_empty());

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a placeholder block", "[default_style]")
    {
        auto msg = placeholder({"test"});

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a progress bar block", "[default_style]")
    {
        auto msg = progress_bar(10);

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a test block", "[default_style]")
    {
        auto msg = text("Test");

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" an underline block", "[default_style]")
    {
        auto msg = underline(text("Test"));

        REQUIRE_NOTHROW(render(msg, form));
    }

    SECTION(" a table block", "[default_style]")
    {
        auto msg = make_table(4);

        std::vector<block> columns(4, make_empty());

        msg.add_row(std::move(columns));

        REQUIRE_NOTHROW(render(msg, form));
    }
}