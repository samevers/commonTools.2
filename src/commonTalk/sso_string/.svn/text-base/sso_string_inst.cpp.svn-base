#include "sso_string/sso_string.h"

using namespace platform;

#define SSO_STRING_IMPL(LocalCaps, CharT, ShortName) \
	template class __gnu_cxx::__versa_string<CharT, std::char_traits<CharT>, \
		std::allocator<CharT>, __sso_string_base_ex_helper<LocalCaps>::type>; \
	template class platform::__sso_string_base_ex<LocalCaps, CharT>; \
	template class std::hash<ShortName>; \
	SS_STATIC_ASSERT(sizeof(ShortName) == sizeof(void*)+sizeof(size_t)+(LocalCaps+1)*sizeof(CharT))

SSO_STRING_IMPL(15, char, __sso16_string);
SSO_STRING_IMPL(23, char, __sso24_string);
SSO_STRING_IMPL(31, char, __sso32_string);
SSO_STRING_IMPL(47, char, __sso48_string);
SSO_STRING_IMPL(63, char, __sso64_string);

SSO_STRING_IMPL(15, wchar_t, __wsso16_string);
SSO_STRING_IMPL(23, wchar_t, __wsso24_string);
SSO_STRING_IMPL(31, wchar_t, __wsso32_string);
SSO_STRING_IMPL(47, wchar_t, __wsso48_string);
SSO_STRING_IMPL(63, wchar_t, __wsso64_string);

SSO_STRING_IMPL(15, char16_t, __u16sso16_string);
SSO_STRING_IMPL(23, char16_t, __u16sso24_string);
SSO_STRING_IMPL(31, char16_t, __u16sso32_string);
SSO_STRING_IMPL(47, char16_t, __u16sso48_string);
SSO_STRING_IMPL(63, char16_t, __u16sso64_string);

SSO_STRING_IMPL(15, char32_t, __u32sso16_string);
SSO_STRING_IMPL(23, char32_t, __u32sso24_string);
SSO_STRING_IMPL(31, char32_t, __u32sso32_string);
SSO_STRING_IMPL(47, char32_t, __u32sso48_string);
SSO_STRING_IMPL(63, char32_t, __u32sso64_string);


