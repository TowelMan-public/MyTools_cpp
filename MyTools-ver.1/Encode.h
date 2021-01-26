#pragma once
#include <string>
#include <atlstr.h>

namespace MyTools {
	namespace Encode {
		namespace UTF8 {
			std::string ShiftJis(std::string src);
			std::wstring Unicode(std::string src);
		};
		namespace ShiftJis {
			std::string UTF8(std::string src);
			std::wstring Unicode(std::string const& src);
		};
		namespace Unicode {
			std::string UTF8(std::wstring src);
			std::string ShiftJis(std::wstring const& src);
		};
	};
}