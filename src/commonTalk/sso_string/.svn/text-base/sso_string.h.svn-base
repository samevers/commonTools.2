#pragma once

#include <ext/vstring.h>
#include "sso_string/sso_string_fwd.h"
#include "sso_string/sso_string_base_ex.h"
#include "sso_string/sso_hash.inl"

#define SSO_STRING_EXTERN(LocalCaps, CharT, ShortName) \
	extern template class __gnu_cxx::__versa_string<CharT, std::char_traits<CharT>, \
		std::allocator<CharT>, platform::__sso_string_base_ex_helper<LocalCaps>::type>; \
	extern template class platform::__sso_string_base_ex<LocalCaps, CharT>

SSO_STRING_EXTERN(15, char, __sso16_string);
SSO_STRING_EXTERN(23, char, __sso24_string);
SSO_STRING_EXTERN(31, char, __sso32_string);
SSO_STRING_EXTERN(47, char, __sso48_string);
SSO_STRING_EXTERN(63, char, __sso64_string);

SSO_STRING_EXTERN(15, wchar_t, __wsso16_string);
SSO_STRING_EXTERN(23, wchar_t, __wsso24_string);
SSO_STRING_EXTERN(31, wchar_t, __wsso32_string);
SSO_STRING_EXTERN(47, wchar_t, __wsso48_string);
SSO_STRING_EXTERN(63, wchar_t, __wsso64_string);

SSO_STRING_EXTERN(15, char16_t, __u16sso16_string);
SSO_STRING_EXTERN(23, char16_t, __u16sso24_string);
SSO_STRING_EXTERN(31, char16_t, __u16sso32_string);
SSO_STRING_EXTERN(47, char16_t, __u16sso48_string);
SSO_STRING_EXTERN(63, char16_t, __u16sso64_string);

SSO_STRING_EXTERN(15, char32_t, __u32sso16_string);
SSO_STRING_EXTERN(23, char32_t, __u32sso24_string);
SSO_STRING_EXTERN(31, char32_t, __u32sso32_string);
SSO_STRING_EXTERN(47, char32_t, __u32sso48_string);
SSO_STRING_EXTERN(63, char32_t, __u32sso64_string);


typedef platform::__sso48_string my_sso_string;

