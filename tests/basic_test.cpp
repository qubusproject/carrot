//  Copyright (c) 2015-2016 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/carrot.hpp>

#include <iostream>

int main()
{
    using namespace carrot;

    auto target = get_stdout_target();

    plain_form form;

    irregular_grid_block g;

    auto txt = text("Test\n Test\n  Test");
    auto txt2 = text("Test\n Test\n  Test", make_style(color_flag::green, formatting_flag::plain));

    g.add_to_row(0, frame(txt));
    g.add_to_row(0, underline_with_caret(txt, 4));

    g.add_to_row(1, indent(frame(txt2), 4));

    auto list = list_block();
    list.add(text("Hello"));
    list.add(mark_with_caret(text("world!"), 2));
    g.add_to_row(1, list);

    auto task_list = make_checkbox_list(make_style(color_flag::green, formatting_flag::plain));

    task_list.add(true, text("Task1"));
    task_list.add(false, text("Task2"));

    g.add_to_row(2, task_list);

    g.render(form);

    std::cout << form.to_string(target) << std::endl;
}