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
		int FD_accept;//�ڑ��󂯗p��FD
		int FD_GorS;//���ۂɎ�M�E���M������FD
		//int flag = 0;//�����g��Ȃ�
		sockaddr_in ssin;//FD_accept�ɑΉ�����\�P�b�g�A�h���X�\����
		sockaddr_in sin_clim;//�\�P�b�g�A�h���X�\����
		int socklen;//sin_clim�̃T�C�Y
		WSADATA wsaData;//�\�P�b�g�X�g���[�����g�����߂ɕK�v�Ȃ��
		bool HaveInit;//����������Ă邩�ۂ�
	public:
		Hnet(bool IsInit = false,int timeout = DEFAULT_TIMEOUT,int portnum = DEFAULT_PORTNUMBER);//�N���X���̂̏�����
		bool Init();//����������
		bool Accept(std::string& pass);//�ڑ�
		std::string Get();//��M
		bool Send(std::string str);//���M
		bool CutEnd();//�ؒf	
	private:
		std::string m_Get(int size = 50);
		bool m_Send(std::string str);
	};
}