#include <carrot/carrot.hpp>

#include <iostream>

int main()
{
    using namespace carrot;

    auto target = get_stdout_target();

    simple_form mat;

    irregular_grid_block g;

    auto txt = text("Test\n Test\n  Test");
    auto txt2 = text("Test\n Test\n  Test", make_style(color_flag::green, formatting_flag::plain));

    g.add_to_row(0, frame(txt));
    g.add_to_row(0, underline_with_caret(txt, 4));

    g.add_to_row(1, indent(frame(txt2), 4));

    auto list = std::make_shared<list_block>();
    list->add(text("Hello"));
    list->add(text("world!"));
    g.add_to_row(1, list);

    g.render(mat);

    std::cout << mat.to_string(target) << std::endl;
}