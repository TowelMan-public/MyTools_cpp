#include "TString.h"
#include <locale>
#include <vector>
#include "Encode.h"

namespace MyTools {
	/*������̕ϊ�(std::string�Astd::wstring ��)*/
	std::string TString::WStringToString(std::wstring src) {
		return Encode::Unicode::ShiftJis(src);
	}
	std::wstring TString::StringToWString(std::string src) {
		return Encode::ShiftJis::Unicode(src);
	}

	/*TString�̃R���X�g���N�^����*/

	TString::TString(void)	{
		//�������Ȃ�
	}

	TString::TString(std::MY_OTHER_STRING_0028 str) {
		this->operator=(str);
	}

	TString::TString(MY_OTHER_CHAR ch) {
		std::MY_OTHER_STRING_0028 str = &ch;
		this->operator=(str);
	}

	TString::TString(MY_OTHER_CHAR* str) {
		std::MY_OTHER_STRING_0028 str2 = str;
		this->operator=(str2);
	}

	TString::TString(std::MY_STRING_0028 str) {
		this->swap(str);
	}

	/*TString�̃L���X�g�ϊ�����*/

	TString::operator std::MY_OTHER_STRING_0028() const{
		std::MY_STRING_0028 str = this->c_str();
		std::MY_OTHER_STRING_0028 str2;
		//�t�ɂȂ�
#ifndef _UNICODE
		str2 = StringToWString(str);
#else
		str2 = WStringToString(str);
#endif
		return str2;
	}

	TString::operator CString() const{
		CString  str = this->c_str();
		return str;
	}

	/*TString�̉��Z�q=�̃I�[�o�[���[�h����*/

	TString TString::operator=(std::MY_STRING_0028 str) {
		this->swap(str);
		return *this;
	}
	TString TString::operator=(std::MY_OTHER_STRING_0028 str) {
		std::MY_STRING_0028 str2;
#ifdef _UNICODE
		str2 = StringToWString(str);
#else
		str2 = WStringToString(str);
#endif
		this->swap(str2);//���f
		return *this;
	}
	TString TString::operator=(CString str) {
		std::MY_STRING_0028 str2 = str.GetBuffer();
		this->swap(str2);
		return *this;
	}
	TString TString::operator=(MY_OTHER_CHAR ch) {
		std::MY_OTHER_STRING_0028 str = &ch;
		std::MY_STRING_0028 str2 = this->operator=(str);
		this->swap(str2);
		return *this;
	}
	TString TString::operator=(MY_OTHER_CHAR* str) {
		std::MY_OTHER_STRING_0028 str2 = str;
		std::MY_STRING_0028 str3 = this->operator=(str2);
		this->swap(str3);
		return *this;
	}

	template <typename ... Args>
	std::MY_STRING_0028 TString::format(const std::MY_STRING_0028 fmt, Args ... args) {
		CString rtn;
		rtn.Format(fmt.c_str(), args...);
		this->operator=((std::MY_STRING_0028)rtn.GetBuffer());
		return *this;
	}
}