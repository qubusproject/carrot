//  Copyright (c) 2017 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>

#include <boost/range/adaptor/sliced.hpp>

#include <carrot/color.hpp>
#include <carrot/color_map.hpp>

TEST(color, rgb)
{
    carrot::rgb_color color1(255, 127, 42);

    EXPECT_EQ(color1.red(), 255);
    EXPECT_EQ(color1.green(), 127);
    EXPECT_EQ(color1.blue(), 42);

    auto color2 = rgb(color1);

    EXPECT_EQ(color1.red(), color2.red());
    EXPECT_EQ(color1.green(), color2.green());
    EXPECT_EQ(color1.blue(), color2.blue());

    auto color3 = rgb(carrot::color(color1));

    EXPECT_EQ(color1.red(), color3.red());
    EXPECT_EQ(color1.green(), color3.green());
    EXPECT_EQ(color1.blue(), color3.blue());
}

TEST(color, hsl)
{
    carrot::hsl_color color1(255, 0.5f, 0.42f);

    EXPECT_EQ(color1.hue(), 255);
    EXPECT_EQ(color1.saturation(), 0.5f);
    EXPECT_EQ(color1.lightness(), 0.42f);

    auto color2 = hsl(color1);

    EXPECT_EQ(color1.hue(), color2.hue());
    EXPECT_EQ(color1.saturation(), color2.saturation());
    EXPECT_EQ(color1.lightness(), color2.lightness());

    auto color3 = hsl(carrot::color(color1));

    EXPECT_EQ(color1.hue(), color3.hue());
    EXPECT_EQ(color1.saturation(), color3.saturation());
    EXPECT_EQ(color1.lightness(), color3.lightness());
}

TEST(color, rgb2hsl)
{
    carrot::rgb_color purple(128, 0, 128);

    auto purple_hsl = hsl(purple);

    EXPECT_NEAR(purple_hsl.hue(), 300, 1e-4);
    EXPECT_NEAR(purple_hsl.saturation(), 1.0f, 1e-2);
    EXPECT_NEAR(purple_hsl.lightness(), 0.25f, 1e-2);

    carrot::rgb_color yellow4(135, 135, 0);

    auto yellow4_hsl = hsl(yellow4);

    EXPECT_NEAR(yellow4_hsl.hue(), 60, 1e-4);
    EXPECT_NEAR(yellow4_hsl.saturation(), 1.0f, 1e-2);
    EXPECT_NEAR(yellow4_hsl.lightness(), 0.265f, 1e-2);
}

TEST(color, hsl2rgb)
{
    carrot::hsl_color purple(300, 1.0f, 0.25f);

    auto purple_rgb = rgb(purple);

    EXPECT_EQ(purple_rgb.red(), 128);
    EXPECT_EQ(purple_rgb.green(), 0);
    EXPECT_EQ(purple_rgb.blue(), 128);
}

TEST(color, empty_cmap)
{
    using namespace carrot;

    std::vector<hsl_color> colors;

    EXPECT_THROW(color_map cmap(colors);, invalid_color_map_error);
}

TEST(color, cmap)
{
    using namespace carrot;

    std::vector<hsl_color> colors = {
        {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.25f}, {120.0f, 1.0f, 0.25f}, {120.0f, 1.0f, 0.5f}};

    color_map cmap(colors);

    EXPECT_EQ(cmap.map_color(rgb_color(0, 150, 0)), 2);
    EXPECT_EQ(cmap.map_color(rgb_color(0, 200, 0)), 3);
}

TEST(color, xterm_std_cmap)
{
    using namespace carrot;

    color_map cmap(carrot::get_xterm_color_table() | boost::adaptors::sliced(0, 16));

    EXPECT_EQ(cmap.map_color(rgb_color(0, 150, 0)), 2);
    EXPECT_EQ(cmap.map_color(rgb_color(0, 200, 0)), 10);
}

TEST(color, xterm_cmap)
{
    using namespace carrot;

    color_map cmap(carrot::get_xterm_color_table());

    auto c = hsl(rgb_color(135, 135, 0));

    EXPECT_EQ(cmap.map_color(rgb_color(0, 150, 0)), 28);
    EXPECT_EQ(cmap.map_color(rgb_color(0, 200, 0)), 40);
    EXPECT_EQ(cmap.map_color(rgb_color(0, 215, 135)), 42);
    EXPECT_EQ(cmap.map_color(rgb_color(95, 0, 0)), 52);
    EXPECT_EQ(cmap.map_color(rgb_color(135, 135, 0)), 100);
    EXPECT_EQ(cmap.map_color(rgb_color(135, 135, 95)), 101);
    EXPECT_EQ(cmap.map_color(rgb_color(135, 135, 255)), 105);
    EXPECT_EQ(cmap.map_color(rgb_color(175, 95, 95)), 131);
    EXPECT_EQ(cmap.map_color(rgb_color(255, 135, 215)), 212);
    EXPECT_EQ(cmap.map_color(rgb_color(255, 135, 255)), 213);
    EXPECT_EQ(cmap.map_color(rgb_color(228, 228, 228)), 254);
    EXPECT_EQ(cmap.map_color(rgb_color(238, 238, 238)), 255);
    EXPECT_EQ(cmap.map_color(rgb_color(0, 0, 0)), 0);
    EXPECT_EQ(cmap.map_color(rgb_color(8, 8, 8)), 232);
    EXPECT_EQ(cmap.map_color(rgb_color(18, 18, 18)), 233);
    EXPECT_EQ(cmap.map_color(rgb_color(28, 28, 28)), 234);
}

TEST(color, named_colors)
{
    using namespace carrot;

    EXPECT_THROW(rgb(named_color("red")), invalid_color_error);
    EXPECT_THROW(hsl(named_color("red")), invalid_color_error);

    color_table ctable;

    EXPECT_THROW(rgb(named_color("red"), ctable), invalid_color_error);

    ctable = get_default_color_table();

    ctable.add_color("mycolor", rgb_color(42, 128, 70));

    auto mycolor = rgb(named_color("mycolor"), ctable);

    EXPECT_EQ(mycolor.red(), 42);
    EXPECT_EQ(mycolor.green(), 128);
    EXPECT_EQ(mycolor.blue(), 70);

    auto mycolor_hsl = hsl(named_color("mycolor"), ctable);

    EXPECT_NEAR(mycolor_hsl.hue(), 139.5, 1e-1);
    EXPECT_NEAR(mycolor_hsl.saturation(), 0.5059, 1e-3);
    EXPECT_NEAR(mycolor_hsl.lightness(), 0.3333, 1e-3);

    auto mycolor2 = rgb(canonicalize(named_color("mycolor"), ctable));

    EXPECT_EQ(mycolor2.red(), 42);
    EXPECT_EQ(mycolor2.green(), 128);
    EXPECT_EQ(mycolor2.blue(), 70);
}

TEST(color, default_color)
{
    using namespace carrot;

    auto ctable = get_default_color_table();

    EXPECT_THROW(rgb(get_default_color()), invalid_color_error);
    EXPECT_THROW(rgb(get_default_color(), ctable), invalid_color_error);
    EXPECT_THROW(hsl(get_default_color()), invalid_color_error);
    EXPECT_THROW(hsl(get_default_color(), ctable), invalid_color_error);

    EXPECT_THROW(canonicalize(get_default_color(), ctable), invalid_color_error);

    EXPECT_TRUE(is_default_color(get_default_color()));
}