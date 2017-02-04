#pragma once

#include <ext/vstring_fwd.h>

namespace platform
{

	template<size_t _LocalCaps, typename _CharT, typename _Traits, typename _Alloc>
		class __sso_string_base_ex;

	// For gcc >= 4.7
	// template<typename _CharT, typename _Traits, typename _Alloc>
	//	using __sso_string_base_ex48 = class __sso_string_base_ex<48, _CharT, _Traits, _Alloc>;
	
	// For gcc < 4.7
	template<size_t _LocalCaps>
		class __sso_string_base_ex_helper
	{
	public:
		template<typename _CharT, typename _Traits, typename _Alloc>
			class type: public __sso_string_base_ex<_LocalCaps, _CharT, _Traits, _Alloc>
		{
		public:
			typedef __sso_string_base_ex<_LocalCaps, _CharT, _Traits, _Alloc>  super;
			type() = default;

			type(const _Alloc& __a) : super(__a) {}

			type(const type& __rcs)
				: super(__rcs)
			{}

#if __cplusplus >= 201103L
			type(type&& __rcs)
				: super(std::forward(__rcs))
			{}
#endif

			type(typename super::size_type __n, _CharT __c, const _Alloc& __a)
				: super(__n, __c, __a)
			{}

			template<typename _InputIterator>
				type(_InputIterator __beg, _InputIterator __end,
						const _Alloc& __a)
				: super(__beg, __end, __a)
			{}
				
		};
	};

#define SSO_STRING_DECL(LocalCaps, CharT, ShortName) \
	typedef __gnu_cxx::__versa_string<CharT, std::char_traits<CharT>, \
		std::allocator<CharT>, platform::__sso_string_base_ex_helper<LocalCaps>::type> ShortName

	SSO_STRING_DECL(15, char, __sso16_string);
	SSO_STRING_DECL(23, char, __sso24_string);
	SSO_STRING_DECL(31, char, __sso32_string);
	SSO_STRING_DECL(47, char, __sso48_string);
	SSO_STRING_DECL(63, char, __sso64_string);

	SSO_STRING_DECL(15, wchar_t, __wsso16_string);
	SSO_STRING_DECL(23, wchar_t, __wsso24_string);
	SSO_STRING_DECL(31, wchar_t, __wsso32_string);
	SSO_STRING_DECL(47, wchar_t, __wsso48_string);
	SSO_STRING_DECL(63, wchar_t, __wsso64_string);

	SSO_STRING_DECL(15, char16_t, __u16sso16_string);
	SSO_STRING_DECL(23, char16_t, __u16sso24_string);
	SSO_STRING_DECL(31, char16_t, __u16sso32_string);
	SSO_STRING_DECL(47, char16_t, __u16sso48_string);
	SSO_STRING_DECL(63, char16_t, __u16sso64_string);

	SSO_STRING_DECL(15, char32_t, __u32sso16_string);
	SSO_STRING_DECL(23, char32_t, __u32sso24_string);
	SSO_STRING_DECL(31, char32_t, __u32sso32_string);
	SSO_STRING_DECL(47, char32_t, __u32sso48_string);
	SSO_STRING_DECL(63, char32_t, __u32sso64_string);

} // namespace


