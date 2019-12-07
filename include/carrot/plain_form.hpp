//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_PLAIN_FORM_HPP
#define CARROT_PLAIN_FORM_HPP

#include <carrot/form.hpp>
#include <carrot/target_info.hpp>

#include "carrot_export.hpp"

#include <string>

/** @brief carrot's root namespace.
 */
namespace carrot
{
/** @brief A plain form which stores the entire glyph grid.
 */
class CARROT_EXPORT plain_form final : public form
{
public:
    /** @brief Constructs a new plain form.
     *
     * Optionally, the form is expanded to the specified extent.
     *
     * @param target_ The target which will be used to display the contents of the form.
     * @param rows_ The initial number of rows.
     * @param columns_ The initial number of columns.
     */
    plain_form(target_info target_, long int rows_ = 0, long int columns_ = 0) noexcept;

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
    void set(long int row, long int column, glyph value) final;

    /** @brief The backing target of the form.
     *
     * @return The backing target.
     */
    [[nodiscard]] const target_info& target() const noexcept final;

    /** @brief Converts the content of the form to a UTF-8 encoded string.
     *
     * @return The contents as a UTF-8 encoded string.
     * @throws runtime_error If the content of the form could not be converted.
     */
    [[nodiscard]] std::string to_string() const;

    /** @brief Clear the form.
     */
    void clear() noexcept;

    /** @brief Clear the form.
     *
     * To clear each slot, the specified glyph will be used.
     *
     * @param value The glyph used to clear each slot.
     */
    void clear(glyph value) noexcept;

private:
    void resize_if_outside_matrix(long int row, long int column) noexcept;

    target_info target_;
    boost::multi_array<glyph, 2> data_;
    glyph clear_glyph_;
};
} // namespace carrot

#endif
