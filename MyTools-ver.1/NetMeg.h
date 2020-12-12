#pragma once
#include <string>

namespace NetMeg {//通信時のメッセージ
	//応答メッセージ
	const std::string ANS_SUCCESS = "ANS_SUCCESS";
	const std::string ANS_DATE_ERROR = "ANS_DATE_ERROR";
	const std::string ANS_DATE_NOT_HIT = "ANS_DATE_NOT_HIT";
	const std::string ANS_DATE_VIOLATION = "ANS_DATE_VIOLATION";
	const std::string ANS_EXCEL_ERROR = "ANS_EXCEL_ERROR";
	const std::string ANS_ERROR = "ANS_ERROR";
	//要求メッセージ(1)
	const std::string RESEARCH = "RESEARCH";
	const std::string CHG = "CHG";
	const std::string DEL = "DEL";
	const std::string COMMIT = "COMMIT";
	const std::string LOGIN = "LOGIN";
	const std::string LOGOUT = "LOGOUT";
	const std::string INSORT = "INSORT";
	//要求メッセージ(2)
	const std::string REQ_KEIHI_KOU = "REQ_KEIHI_KOU";
	const std::string REQ_KEIHI = "REQ_KEIHI";
	const std::string REQ_KAKEURI = "REQ_KAKEURI";
	const std::string REQ_KAISYA = "REQ_KAISYA";
	const std::string REQ_PAYD = "REQ_PAYD";
	const std::string REQ_UNPAYD = "REQ_UNPAYD";
	const std::string REQ_SYOUHI_TAX = "REQ_SYOUHI_TAX";
	const std::string REQ_SYOTOKU_TAX = "REQ_SYOTOKU_TAX";
	const std::string REQ_SYOTOKU = "REQ_SYOTOKU";
	//要求メッセージ(3)
	const std::string WREQ_KOU = "WREQ_KOU";
	const std::string WREQ_MOOM = "WREQ_MOOM";
	const std::string WREQ_ALL = "WREQ_ALL";
	const std::string WREQ_YERA = "WREQ_YERA";
	const std::string WREQ_TRUE = "WREQ_TRUE";
	//const std::string MAKE_EXSEL = "MAKE_EXCEL";
}