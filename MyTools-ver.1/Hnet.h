#pragma once
#include "Encode.h"
#include "NetMeg.h"

#define DEFAULT_TIMEOUT 1000
#define DEFAULT_PORTNUMBER 5555

namespace MyTools {

	class Hnet {
	private:
		int portNumber;
		int timeOut;
		int ret_code;
		int FD_accept;//接続受け用のFD
		int FD_GorS;//実際に受信・送信をするFD
		//int flag = 0;//多分使わない
		sockaddr_in ssin;//FD_acceptに対応するソケットアドレス構造体
		sockaddr_in sin_clim;//ソケットアドレス構造体
		int socklen;//sin_climのサイズ
		WSADATA wsaData;//ソケットストリームを使うために必要なやつ
		bool HaveInit;//初期化されてるか否か
	public:
		Hnet(bool IsInit = false,int timeout = DEFAULT_TIMEOUT,int portnum = DEFAULT_PORTNUMBER);//クラス自体の初期化
		bool Init();//初期化処理
		bool Accept(std::string& pass);//接続
		std::string Get();//受信
		bool Send(std::string str);//送信
		bool CutEnd();//切断	
	private:
		std::string m_Get(int size = 50);
		bool m_Send(std::string str);
	};
}