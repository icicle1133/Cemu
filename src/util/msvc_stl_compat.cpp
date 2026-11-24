// VS 2022 17.11+ (MSVC 19.41+) generates calls to __std_find_first_not_of_trivial_pos_*
// but removed them from libcpmt.lib. Provide implementations here.
#include <cstddef>
#include <cstring>

extern "C" {

size_t __std_find_first_not_of_trivial_pos_1(
    const char* haystack, size_t haystack_len,
    const char* needle, size_t needle_len) noexcept
{
    for (size_t i = 0; i < haystack_len; ++i)
        if (!memchr(needle, static_cast<unsigned char>(haystack[i]), needle_len))
            return i;
    return static_cast<size_t>(-1);
}

size_t __std_find_first_not_of_trivial_pos_2(
    const wchar_t* haystack, size_t haystack_len,
    const wchar_t* needle, size_t needle_len) noexcept
{
    for (size_t i = 0; i < haystack_len; ++i) {
        bool in_needle = false;
        for (size_t j = 0; j < needle_len; ++j)
            if (haystack[i] == needle[j]) { in_needle = true; break; }
        if (!in_needle) return i;
    }
    return static_cast<size_t>(-1);
}

size_t __std_find_last_not_of_trivial_pos_1(
    const char* haystack, size_t haystack_len,
    const char* needle, size_t needle_len) noexcept
{
    for (size_t i = haystack_len; i-- > 0; )
        if (!memchr(needle, static_cast<unsigned char>(haystack[i]), needle_len))
            return i;
    return static_cast<size_t>(-1);
}

size_t __std_find_last_not_of_trivial_pos_2(
    const wchar_t* haystack, size_t haystack_len,
    const wchar_t* needle, size_t needle_len) noexcept
{
    for (size_t i = haystack_len; i-- > 0; ) {
        bool in_needle = false;
        for (size_t j = 0; j < needle_len; ++j)
            if (haystack[i] == needle[j]) { in_needle = true; break; }
        if (!in_needle) return i;
    }
    return static_cast<size_t>(-1);
}

} // extern "C"
