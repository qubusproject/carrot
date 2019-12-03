//  Copyright (c) 2015-2018 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CARROT_TARGET_INFO_HPP
#define CARROT_TARGET_INFO_HPP

#include <carrot/exception.hpp>

#include "carrot_export.hpp"

#include <locale>
#include <stdexcept>

/** @brief carrot's root namespace.
 */
namespace carrot
{

class CARROT_EXPORT invalid_target_error : public virtual exception, public virtual std::logic_error
{
public:
    explicit invalid_target_error(const std::string& reason_);
};

/** @brief Information about a rendering target.
 */
class CARROT_EXPORT target_info
{
public:
    /** @brief Initializes the target information.
     *
     * @param locale_ The used locale.
     * @param supports_colorized_output_ True, if the target supports colorized output.
     * @param tab_width_ The tabulator width.
     */
    explicit target_info(const std::locale& locale_, bool supports_colorized_output_,
                         long int tab_width_);

    /** @brief Query if colorized output is supported.
     *
     * @return True, if colorized output is supported.
     */
    [[nodiscard]] bool supports_colorized_output() const;

    /** @brief Queries the tabulator width.
     *
     * @return The tabulator width.
     */
    [[nodiscard]] long int tab_width() const;

    /** @brief Queries the locale of the target.
     *
     * @return The locale.
     */
    [[nodiscard]] const std::locale& locale() const;

private:
    std::locale locale_;
    bool supports_colorized_output_;
    long int tab_width_;
};

/** @brief Queries the target information for the standard output.
 *
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_stdout_target(long int tab_width = 4);

/** @brief Queries the target information for the standard output.
 *
 * @param locale The locale used for the output.
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_stdout_target(const std::locale& locale,
                                                          long int tab_width = 4);

/** @brief Queries the target information for an arbitrary text file target.
 *
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_file_target(long int tab_width = 4);

/** @brief Queries the target information for an arbitrary text file target.
 *
 * @param locale The locale used for the output.
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_file_target(const std::locale& locale,
                                                        long int tab_width = 4);

/** @brief Queries the target information for a generic target with colorization support.
 *
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_colorized_target(long int tab_width = 4);

/** @brief Queries the target information for a generic target with colorization support.
 *
 * @param locale The locale used for the output.
 * @param tab_width The tabulator width.
 * @return The target information.
 */
[[nodiscard]] CARROT_EXPORT target_info get_colorized_target(const std::locale& locale,
                                                             long int tab_width = 4);

} // namespace carrot

#endif
