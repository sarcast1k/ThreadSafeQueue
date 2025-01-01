#ifndef SAFESTRING_H
#define SAFESTRING_H

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <format> // for C++20 formatting

namespace SafeString {

    /**
     * concatenates two strings efficiently.
     *
     * @param a The first string.
     * @param b The second string.
     * @return The concatenated string.
     */
    std::string concatenate(const std::string& a, const std::string& b);

    /**
     * extracts a substring from a string safely, handling potential out-of-bounds access.
     *
     * @param str The source string.
     * @param start The starting index of the substring.
     * @param length The length of the substring.
     * @return the extracted substring.
     * @throws std::out_of_range If the substring would exceed the string bounds.
     */
    std::string safeSubstring(const std::string& str, size_t start, size_t length);

    /**
     * splits a string into a vector of substrings based on a delimiter.
     *
     * @param str The string to split.
     * @param delimiter The delimiter character.
     * @return a vector of substrings.
     */
    std::vector<std::string> split(const std::string& str, char delimiter);

    /**
     * replaces all occurrences of a substring within a string.
     *
     * @param str The source string.
     * @param from The substring to be replaced.
     * @param to The replacement substring.
     * @return the string with replaced substrings.
     */
    std::string replace(const std::string& str, const std::string& from, const std::string& to);

    /**
     * formats a string using a format string and arguments.
     *
     * @param formatStr The format string.
     * @param args The arguments to be formatted.
     * @return the formatted string.
     */
    template<typename... Args>
    std::string format(const std::string& formatStr, Args... args) {
        #if __cpp_lib_format >= 201911L // Check for C++20 formatting support
            return std::vformat(formatStr, std::make_format_args(args...));
        #else
            // Fallback for older compilers (less efficient)
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2); // e.g. Set precision for floating-point numbers
            ss << std::format(formatStr, args...); 
            return ss.str();
        #endif
    }

} // namespace SafeString

#endif // SAFESTRING_H
