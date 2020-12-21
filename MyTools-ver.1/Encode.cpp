#include "Encode.h"
#include <vector>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#define CP_SJIS 932

namespace MyTools {

	namespace Encode {

		namespace ShiftJis {
			std::wstring Unicode(std::string src) {
				std::size_t converted{};
				std::vector<wchar_t> dest(src.capacity() + 1, L'\0');
				if (::_mbstowcs_s_l(&converted, dest.data(), dest.size(), src.data(), dest.size(), ::_create_locale(LC_ALL, "jpn")) != 0) {
					throw std::system_error{ errno, std::system_category() };
				}
				dest.resize(std::char_traits<wchar_t>::length(dest.data()));
				dest.shrink_to_fit();
				return std::wstring(dest.begin(), dest.end());
			}
			std::string UTF8(std::string src) {
				auto const wide = ::MyTools::Encode::ShiftJis::Unicode(src);
				return ::MyTools::Encode::Unicode::UTF8(wide);
			}
		}

		namespace UTF8 {
			std::string ShiftJis(std::string src) {
				auto const wide = ::MyTools::Encode::UTF8::Unicode(src);
				return ::MyTools::Encode::Unicode::ShiftJis(wide);
			}
			std::wstring Unicode(std::string src) {
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.from_bytes(src);
			}
		}

		namespace Unicode {
			std::string UTF8(std::wstring src) {
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
				return converter.to_bytes(src);
			}
			std::string ShiftJis(std::wstring src) {
				int error;
				std::size_t converted{};
				std::vector<char> dest((src.capacity() * 2) +1, '\0');
				if (error = ::_wcstombs_s_l(&converted, dest.data(), dest.size(), src.data(), dest.size(), ::_create_locale(LC_ALL, "jpn")) != 0) {
					throw std::system_error{ errno, std::system_category() };
				}
				dest.resize(std::char_traits<char>::length(dest.data()));
				dest.shrink_to_fit();
				return std::string(dest.begin(), dest.end());
			}
		}
	}
}