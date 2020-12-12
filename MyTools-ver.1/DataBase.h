#pragma once
#include <string>
#include "Encode.h"
/*MySQLのインクルード*/
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
			std::string columnType;//i=整数型、s=文字列型、d=日付型、それ以外=少数
		protected:
			virtual void RunSql(void) = 0;
			virtual std::string GetResultStr(void) = 0;
		public://コンストラクタ・デストラクタ
			BasicDatabase(void);
			virtual ~BasicDatabase();
		public:
			virtual void Conect(std::string name, std::string password) = 0;//ルートアカウントのログイン（これをしないと失敗する）
			virtual void Conect(std::string name, std::string password, std::string dataBase) = 0;//ルートアカウントのログイン（これをしないと失敗する）
			virtual void SelectDatabase(std::string dataBase) = 0;//データベースの選択
			virtual void CutEnd(void) = 0;//ログアウト・本プログラムを終了するときに必ず呼び出すこと
		};

#ifdef MyTools_Database_MySQL
		class MySQL : public BasicDatabase {
		private:
			sql::ResultSet* GetResultCrude(void);
		protected:
			virtual void RunSql(void);
			virtual std::string GetResultStr(void);
		public://コンストラクタ・デストラクタ
			MySQL(void);//何もしない
			MySQL(std::string name, std::string password);//接続もする
			MySQL(std::string name, std::string password,std::string dataBase);//接続もする
			virtual ~MySQL();
		public:
			virtual void Conect(std::string name, std::string password);//ルートアカウントのログイン（これをしないと失敗する）
			virtual void Conect(std::string name, std::string password, std::string dataBase);//ルートアカウントのログイン（これをしないと失敗する）
			virtual void SelectDatabase(std::string dataBase);
			virtual void CutEnd(void);//ログアウト・本プログラムを終了するときに必ず呼び出すこと
		};
#endif//MyTools_Database_MySQL
	}
}