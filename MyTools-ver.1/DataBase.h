#pragma once
#include <string>
#include "Encode.h"
/*MySQL�̃C���N���[�h*/
#ifdef MyTools_Database_MySQL
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/Statement.h>
#include <cppconn/ResultSet.h>
#endif//MyTools_Database_MySQL

namespace MyTools {
	namespace Database {
		class BasicDatabase {
		protected:
			std::string sqlStr;
			std::string columnType;//i=�����^�As=������^�Ad=���t�^�A����ȊO=����
		protected:
			virtual void RunSql(void) = 0;
			virtual std::string GetResultStr(void) = 0;
		public://�R���X�g���N�^�E�f�X�g���N�^
			BasicDatabase(void);
			virtual ~BasicDatabase();
		public:
			virtual void Conect(std::string name, std::string password) = 0;//���[�g�A�J�E���g�̃��O�C���i��������Ȃ��Ǝ��s����j
			virtual void Conect(std::string name, std::string password, std::string dataBase) = 0;//���[�g�A�J�E���g�̃��O�C���i��������Ȃ��Ǝ��s����j
			virtual void SelectDatabase(std::string dataBase) = 0;//�f�[�^�x�[�X�̑I��
			virtual void CutEnd(void) = 0;//���O�A�E�g�E�{�v���O�������I������Ƃ��ɕK���Ăяo������
		};

#ifdef MyTools_Database_MySQL
		class MySQL : public BasicDatabase {
		private:
			sql::ResultSet* GetResultCrude(void);
		protected:
			virtual void RunSql(void);
			virtual std::string GetResultStr(void);
		public://�R���X�g���N�^�E�f�X�g���N�^
			MySQL(void);//�������Ȃ�
			MySQL(std::string name, std::string password);//�ڑ�������
			MySQL(std::string name, std::string password,std::string dataBase);//�ڑ�������
			virtual ~MySQL();
		public:
			virtual void Conect(std::string name, std::string password);//���[�g�A�J�E���g�̃��O�C���i��������Ȃ��Ǝ��s����j
			virtual void Conect(std::string name, std::string password, std::string dataBase);//���[�g�A�J�E���g�̃��O�C���i��������Ȃ��Ǝ��s����j
			virtual void SelectDatabase(std::string dataBase);
			virtual void CutEnd(void);//���O�A�E�g�E�{�v���O�������I������Ƃ��ɕK���Ăяo������
		};
#endif//MyTools_Database_MySQL
	}
}