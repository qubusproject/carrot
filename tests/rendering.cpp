//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <catch2/catch_test_macros.hpp>

#include <carrot/carrot.hpp>

TEST_CASE("Basic rendering", "[rendering]")
{
    using namespace carrot;

    auto target = get_stdout_target();

    plain_form form(target);

    auto grid = make_grid(2, 2);

    grid.set(0, 0, text("Test"));
    grid.set(0, 1, mark_with_caret(text("Test"), 2));
    grid.set(1, 0, underline(text("Test")));
    grid.set(1, 1, underline_with_caret(text("Test"), 2));

    auto message = frame(std::move(grid));

    render(message, form);

    form.to_string();
}

TEST_CASE("Colorized rendering", "[rendering]")
{
    using namespace carrot;

    auto target = get_colorized_target();

    plain_form form(target);

    auto grid = make_grid(2, 2);

    grid.set(0, 0, indent(text("Test"), 4));
    grid.set(0, 1, mark_with_caret(text("Test"), 2));
    grid.set(1, 0, underline(text("Test")));
    grid.set(1, 1, underline_with_caret(text("Test"), 2));

    auto message = frame(std::move(grid));

    render(message, form);

    form.to_string();
}

TEST_CASE("Changing the tabulator width", "[rendering]")
{
    using namespace carrot;

    auto target = get_colorized_target(6);

    REQUIRE(target.tab_width() == 6);
}
