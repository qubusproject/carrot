#include <carrot/carrot.hpp>

#include <iostream>

int main()
{
    using namespace carrot;

    simple_matrix mat;

    irregular_grid_block g;

    auto txt = std::make_shared<text_block>("Test\n Test\n  Test");

    g.add_to_row(0, std::make_shared<frame_block>(txt));
    g.add_to_row(0, std::make_shared<caret_underline_block>(txt, 4));

    g.add_to_row(1, std::make_shared<frame_block>(txt));

    g.render(mat);

    std::cout << mat.to_string() << std::endl;
}