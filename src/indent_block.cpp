//  Copyright (c) 2015-2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/indent_block.hpp>

#include <carrot/form_view.hpp>
#include <carrot/style.hpp>

#include <utility>

namespace carrot
{

indent_block::indent_block(block indented_block_, long int indent_levels_)
: indented_block_(indented_block_), indent_levels_(indent_levels_)
{
}

void indent_block::render(form& output_form, const style& s) const
{
    auto indent = s.get_attribute<style::integer>("indent", id(), tags(), "indent");

    auto extent = indented_block_.extent(s);

    form_view view(output_form, 0, indent * indent_levels_);

    indented_block_.render(view, s);
}

std::array<long int, 2> indent_block::extent(const style& s) const
{
    auto indent = s.get_attribute<style::integer>("indent", id(), tags(), "indent");

    auto extent = indented_block_.extent(s);

    return std::array<long int, 2>{extent[0], extent[1] + indent * indent_levels_};
}

indent_block indent(block indented_block, long int indent_levels)
{
    return indent_block(std::move(indented_block), indent_levels);
}
}