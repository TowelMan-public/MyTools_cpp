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
			std::wstring Unicode(std::string const& src) {
				auto const dest_size = ::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, nullptr, 0U);
				std::vector<wchar_t> dest(dest_size, L'\0');
				if (::MultiByteToWideChar(CP_ACP, 0U, src.data(), -1, dest.data(), dest.size()) == 0) {
					throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
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
			std::string ShiftJis(std::wstring const& src) {
				auto const dest_size = ::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
				std::vector<char> dest(dest_size, '\0');
				if (::WideCharToMultiByte(CP_ACP, 0U, src.data(), -1, dest.data(), dest.size(), nullptr, nullptr) == 0) {
					throw std::system_error{ static_cast<int>(::GetLastError()), std::system_category() };
				}
				dest.resize(std::char_traits<char>::length(dest.data()));
				dest.shrink_to_fit();
				return std::string(dest.begin(), dest.end());
			}
		}
	}
}