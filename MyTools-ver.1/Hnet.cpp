#include "Hnet.h"
#include <vector>
#pragma comment(lib,"ws2_32.lib")

namespace MyTools {
	Hnet::Hnet(bool IsInit, int timeout, int portnum) {
		portNumber = portnum;
		timeOut = timeout;
		ret_code = 0;
		FD_accept = -1;//�ڑ��󂯗p��FD
		FD_GorS = -1;//���ۂɎ�M�E���M������FD
		//flag = 0;//�����g��Ȃ�
		HaveInit = false;
		if (IsInit)
			this->Init();
	}

	bool Hnet::Init() {
		if (HaveInit)return true;
		HaveInit = true;
		const char timeo[] = "1000";//�^�C���A�E�g�̒l�i�~���b�j
		//�\�P�b�g�A�h���X�\���̂�������
		memset(&ssin, 0, sizeof(ssin));
		memset(&sin_clim, 0, sizeof(sin_clim));
		//�T�C�Y�擾
		socklen = sizeof(sin_clim);
		//�\�P�b�g�X�g���[���̂��߂̏�����
		int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
		//TCP�\�P�b�g�̍쐬
		FD_accept = socket(AF_INET, SOCK_STREAM, 0);
		if (FD_accept == -1)return false;
		//�\�P�b�g�̐ݒ������
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = INADDR_ANY;
		ssin.sin_port = htons(portNumber);
		//FD_accept�\�P�b�g�̐ݒ������i���f�j
		ret_code = bind(FD_accept, (const sockaddr*)&ssin, sizeof(ssin));
		if (ret_code == -1) {
			closesocket(FD_accept);
			return false;
		}
		//�^�C���A�E�g�̐ݒ�
		setsockopt(FD_accept, SOL_SOCKET, SO_SNDTIMEO, timeo, sizeof(timeo));
		//�\�P�b�g�ɒʐM�҂���ݒ肷�� 5�̓o�b�N���O
		ret_code = listen(FD_accept, 5);
		if (ret_code == -1) {
			closesocket(FD_accept);
			return false;
		}

		return true;
	}

	bool Hnet::Accept(std::string& pass) {
		FD_GorS = accept(FD_accept, (sockaddr*)&sin_clim, &socklen);
		//�ʐM�v�����Ȃ���ΏI��
		if (FD_GorS == -1)
			return false;
		//IP�A�h���X�̎擾
#pragma warning(suppress : 4996) 
		pass = inet_ntoa(sin_clim.sin_addr);
		return true;
	}

	bool Hnet::Send(std::string str) {
		//�����R�[�h��ʐM�p��UTF-8�ɕύX
		std::string strUtf8 = MyTools::Encode::ShiftJis::UTF8(str);
		//�f�[�^�T�C�Y�̑��M
		this->m_Send(std::to_string(strUtf8.length()));
		this->m_Get();
		//�f�[�^�̑��M
		this->m_Send(strUtf8);
		this->m_Get();
		return true;
	}

	std::string Hnet::Get() {
		std::string num, date;
		int size;
		//�f�[�^�T�C�Y�̎擾
		num = this->m_Get(4);
		this->m_Send(NetMeg::ANS_SUCCESS);
		size = atoi(num.c_str());
		//�f�[�^�̎擾
		date = this->m_Get(size);
		this->m_Send(NetMeg::ANS_SUCCESS);
		return date;
	}

	std::string Hnet::m_Get(int size) {
		char* baf = new char[size];//��M�p�o�b�t�@�[	
		int s;
		//��M
		s = recv(FD_GorS, baf, size, NULL);
		int error = WSAGetLastError();
		std::string str = baf;
		delete[] baf;
		if (s == -1 || str.substr(0, s) == "")return NetMeg::ANS_ERROR;
		return MyTools::Encode::UTF8::ShiftJis(str.substr(0, s));
	}

	bool Hnet::m_Send(std::string date) {
		const int size = date.length();//���񑗂�f�[�^�̃T�C�Y
		std::string strCheck = (date).c_str();
		//���M
		if (send(FD_GorS, (date).c_str(), size, 0) >= size)
			return true;//����
		else return false;//���s
	}

	bool Hnet::CutEnd() {
		closesocket(FD_GorS);
		FD_GorS = -1;
		return true;
	}
}