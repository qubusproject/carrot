//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_FORM_VIEW_HPP
#define CARROT_FORM_VIEW_HPP

#include <carrot/form.hpp>

#include "carrot_export.hpp"

/** @brief carrot's root namespace.
 */
namespace carrot
{

/** @brief A shifted view of an existing form.
 *
 * The view is a valid form itself.
 */
class CARROT_EXPORT form_view final : public form
{
public:
    /** @brief Constructs a new view.
     *
     * @param base_form_ The base form.
     * @param row_offset_ The row offset.
     * @param column_offset_ The column offset.
     */
    explicit form_view(form& base_form_, long int row_offset_, long int column_offset_);

    /** @brief Sets the specified form slot to the provided glyph.
     *
     * @param row The row index of the slot.
     * @param column The column index of the slot.
     * @param value The new value of the slot.
     */
    void set(long int row, long int column, glyph value) final;

    /** @brief The backing target of the form.
     *
     * The backing target of the view is the backing target of the base form.
     *
     * @return The backing target.
     */
    [[nodiscard]] const target_info& target() const final;

private:
    form* base_form_;
    long int row_offset_;
    long int column_offset_;
};
} // namespace carrot

#endif
