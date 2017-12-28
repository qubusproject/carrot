//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/carrot.hpp>

#include <iostream>

carrot::block generate_partial_message()
{
    using namespace carrot;

    auto list = make_checkbox_list();

    list.add(true, text("Start App"));
    list.add(true, text("Init logging"));
    list.add(false, text("Init I/O"));

    return list;
}

carrot::block generate_full_message()
{
    using namespace carrot;

    auto partial_message = generate_partial_message();

    auto column = make_line(growth_direction::down);

    column.add(text("/home/christopher/git/work/carrot/examples/example1.cpp:31:"));
    column.add(text(""));
    column.add(indent(partial_message));

    return indent(column);
}

int main()
{
    using namespace carrot;

    auto target = get_stdout_target();

    plain_form form;

    auto message = generate_full_message();

    user_defined_style style(get_default_style());

    style.add_rule("checkbox-list")
            .add_attribute("symbol", u8"\u2714");

    render(message, form, style);

    std::cout << form.to_string(target) << std::endl;
}