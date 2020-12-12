#include "Hnet.h"
#include <vector>
#pragma comment(lib,"ws2_32.lib")

namespace MyTools {
	Hnet::Hnet(bool IsInit, int timeout, int portnum) {
		portNumber = portnum;
		timeOut = timeout;
		ret_code = 0;
		FD_accept = -1;//接続受け用のFD
		FD_GorS = -1;//実際に受信・送信をするFD
		//flag = 0;//多分使わない
		HaveInit = false;
		if (IsInit)
			this->Init();
	}

	bool Hnet::Init() {
		if (HaveInit)return true;
		HaveInit = true;
		const char timeo[] = "1000";//タイムアウトの値（ミリ秒）
		//ソケットアドレス構造体を初期化
		memset(&ssin, 0, sizeof(ssin));
		memset(&sin_clim, 0, sizeof(sin_clim));
		//サイズ取得
		socklen = sizeof(sin_clim);
		//ソケットストリームのための初期化
		int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
		//TCPソケットの作成
		FD_accept = socket(AF_INET, SOCK_STREAM, 0);
		if (FD_accept == -1)return false;
		//ソケットの設定をする
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = INADDR_ANY;
		ssin.sin_port = htons(portNumber);
		//FD_acceptソケットの設定をする（反映）
		ret_code = bind(FD_accept, (const sockaddr*)&ssin, sizeof(ssin));
		if (ret_code == -1) {
			closesocket(FD_accept);
			return false;
		}
		//タイムアウトの設定
		setsockopt(FD_accept, SOL_SOCKET, SO_SNDTIMEO, timeo, sizeof(timeo));
		//ソケットに通信待ちを設定する 5はバックログ
		ret_code = listen(FD_accept, 5);
		if (ret_code == -1) {
			closesocket(FD_accept);
			return false;
		}

		return true;
	}

	bool Hnet::Accept(std::string& pass) {
		FD_GorS = accept(FD_accept, (sockaddr*)&sin_clim, &socklen);
		//通信要求がなければ終了
		if (FD_GorS == -1)
			return false;
		//IPアドレスの取得
#pragma warning(suppress : 4996) 
		pass = inet_ntoa(sin_clim.sin_addr);
		return true;
	}

	bool Hnet::Send(std::string str) {
		//文字コードを通信用のUTF-8に変更
		std::string strUtf8 = MyTools::Encode::ShiftJis::UTF8(str);
		//データサイズの送信
		this->m_Send(std::to_string(strUtf8.length()));
		this->m_Get();
		//データの送信
		this->m_Send(strUtf8);
		this->m_Get();
		return true;
	}

	std::string Hnet::Get() {
		std::string num, date;
		int size;
		//データサイズの取得
		num = this->m_Get(4);
		this->m_Send(NetMeg::ANS_SUCCESS);
		size = atoi(num.c_str());
		//データの取得
		date = this->m_Get(size);
		this->m_Send(NetMeg::ANS_SUCCESS);
		return date;
	}

	std::string Hnet::m_Get(int size) {
		char* baf = new char[size];//受信用バッファー	
		int s;
		//受信
		s = recv(FD_GorS, baf, size, NULL);
		int error = WSAGetLastError();
		std::string str = baf;
		delete[] baf;
		if (s == -1 || str.substr(0, s) == "")return NetMeg::ANS_ERROR;
		return MyTools::Encode::UTF8::ShiftJis(str.substr(0, s));
	}

	bool Hnet::m_Send(std::string date) {
		const int size = date.length();//今回送るデータのサイズ
		std::string strCheck = (date).c_str();
		//送信
		if (send(FD_GorS, (date).c_str(), size, 0) >= size)
			return true;//成功
		else return false;//失敗
	}

	bool Hnet::CutEnd() {
		closesocket(FD_GorS);
		FD_GorS = -1;
		return true;
	}
}