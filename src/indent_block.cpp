//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <carrot/indent_block.hpp>

#include <carrot/form_view.hpp>
#include <carrot/style.hpp>

#include <exception>
#include <utility>

namespace carrot
{

indent_block::indent_block(block indented_block_, long int indent_levels_) noexcept
: indent_block(std::move(indented_block_), indent_levels_, {})
{
}

indent_block::indent_block(block indented_block_, long int indent_levels_,
                           std::vector<std::string> tags_) noexcept
: block_base<indent_block>(std::move(tags_)),
  indented_block_(std::move(indented_block_)),
  indent_levels_(indent_levels_)
{
}

void indent_block::render(form& output_form, const style& s) const
{
    auto indent = s.get_attribute<style::integer>("indent", id(), tags(), "indent");

    form_view view(output_form, 0, indent * indent_levels_);

    indented_block_.render(view, s);
}

std::array<long int, 2> indent_block::extent(const target_info& output_target, const style& s) const
    noexcept
{
    try
    {
        auto indent = s.get_attribute<style::integer>("indent", id(), tags(), "indent");

        auto extent = indented_block_.extent(output_target, s);

        return std::array<long int, 2>{extent[0], extent[1] + indent * indent_levels_};
    }
    catch (const std::exception&)
    {
        std::terminate();
    }
}

indent_block indent(block indented_block, long int indent_levels) noexcept
{
    return indent_block(std::move(indented_block), indent_levels);
}

indent_block indent(block indented_block, std::vector<std::string> tags) noexcept
{
    return indent(std::move(indented_block), 1, std::move(tags));
}

indent_block indent(block indented_block, long int indent_levels,
                    std::vector<std::string> tags) noexcept
{
    return indent_block(std::move(indented_block), indent_levels, std::move(tags));
}
} // namespace carrot