//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FORM_HPP
#define CARROT_FORM_HPP

#include <carrot/glyph.hpp>
#include <carrot/target_info.hpp>

#include "carrot_export.hpp"

#include <boost/multi_array.hpp>

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A form which can be used to render a block.
 *
 * Formally, a form represents a rectangular grid of glyph slots.
 */
class CARROT_EXPORT form
{
public:
    form() noexcept = default;
    virtual ~form() noexcept = default;

    form(const form&) = delete;
    form& operator=(const form&) = delete;

    form(form&&) = delete;
    form& operator=(form&&) = delete;

    /** @brief Sets the specified form slot to the provided glyph.
     *
     * If necessary, this operation will expand the extent of the form
     * such that the specified slot is valid.
     *
     * @param row The row index of the slot.
     * @param column The column index of the slot.
     * @param value The new value of the slot.
     * @throws runtime_error If the slot could not be set.
     */
    virtual void set(long int row, long int column, glyph value) = 0;

    /** @brief The backing target of the form.
     *
     * @return The backing target.
     */
    [[nodiscard]] virtual const target_info& target() const noexcept = 0;
};
}

#endif
