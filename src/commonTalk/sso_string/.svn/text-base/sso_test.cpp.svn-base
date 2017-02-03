#include <string>
#include <iostream>
#include <unordered_set>

#include <Platform/sso_string.h>

#if defined(USE_SSO)
typedef platform::__sso24_string my_string;
#elif defined(USE_STD)
typedef platform::__sso24_string my_string;
#else
# error fuck
#endif

int main()
{
	my_string s;
	std::unordered_set<my_string> myset;
	while (std::cin >> s) {
		myset.insert(s);
	}
	int c = 0;
	std::unordered_set<my_string> myset1;
	for (int i = 0; i < 1000; ++i) {
		if (myset1.size() < myset.size() / 100 )
			myset1 = myset;
		std::unordered_set<my_string> myset2;
		for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
			c += myset1.find(*iter) != myset1.end();
		}
		for (auto iter = myset1.begin(); iter != myset1.end(); ++iter) {
			int l = iter->length();
			if (l > 100)
				l = 100;
			else if (l > 10)
				l = l / 2;
			else
				l = l - 1;
			myset2.insert(my_string(*iter, l));
		}
		myset1 = std::move(myset2);
	}
	return c;
}

