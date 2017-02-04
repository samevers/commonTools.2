#include <functional>
#include <tr1/functional>
#include <ext/vstring.h>
#include <ssmacros.h>

#pragma once

namespace platform
{
	size_t _Hash_bytes(const void* ptr, size_t len, size_t seed = 0xc70f6907UL);
}

#if __GCC_VERSION__ >= 40400 && __GCC_VERSION__ < 40500

namespace std
{

  template<typename _Result, typename _Arg>
    struct __hash_base
    {
      typedef _Result     result_type;
      typedef _Arg      argument_type;
    };

  /// std::hash specialization for __vstring.
  template<>
    struct hash<__gnu_cxx::__vstring>
    : public __hash_base<size_t, __gnu_cxx::__vstring>
    {
      size_t
      operator()(const __gnu_cxx::__vstring& __s) const
      { return platform::_Hash_bytes(__s.data(), __s.length()); }
    };

  /// std::hash specialization for __wvstring.
  template<>
    struct hash<__gnu_cxx::__wvstring>
    : public __hash_base<size_t, __gnu_cxx::__wvstring>
    {
      size_t
      operator()(const __gnu_cxx::__wvstring& __s) const
      { return platform::_Hash_bytes(__s.data(),
                                     __s.length() * sizeof(wchar_t)); }
    };

  /// std::hash specialization for __u16vstring.
  template<>
    struct hash<__gnu_cxx::__u16vstring>
    : public __hash_base<size_t, __gnu_cxx::__u16vstring>
    {
      size_t
      operator()(const __gnu_cxx::__u16vstring& __s) const
      { return platform::_Hash_bytes(__s.data(),
                                     __s.length() * sizeof(char16_t)); }
    };

  /// std::hash specialization for __u32vstring.
  template<>
    struct hash<__gnu_cxx::__u32vstring>
    : public __hash_base<size_t, __gnu_cxx::__u32vstring>
    {
      size_t
      operator()(const __gnu_cxx::__u32vstring& __s) const
      { return platform::_Hash_bytes(__s.data(),
                                     __s.length() * sizeof(char32_t)); }
    };
} // namespace

#endif
 
namespace std
{

  /// std::hash for __versa_string
  template<typename _CharT, typename _Traits, typename _Alloc,
	   template <typename, typename, typename> class _Base>
    struct hash< __gnu_cxx::__versa_string<_CharT, _Traits, _Alloc, _Base> >
    : public __hash_base<size_t, __gnu_cxx::__versa_string<_CharT, _Traits, _Alloc, _Base> >
  {
      size_t
      operator()(const __gnu_cxx::__versa_string<_CharT, _Traits, _Alloc, _Base> & __s) const
      { return platform::_Hash_bytes(__s.data(),
                                     __s.length() * sizeof(_CharT)); }
  };

} // namespace


