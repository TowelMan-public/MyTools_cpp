#include "DataBase.h"

namespace MyTools {
	namespace Database {
		BasicDatabase::BasicDatabase(void) {
			sqlStr = "";
			columnType = "";
		}
		BasicDatabase::~BasicDatabase() {
			//何もしない
		}
#ifdef MyTools_Database_MySQL
		namespace StaticMysqlMember {
			static sql::mysql::MySQL_Driver* driver = nullptr;//データベースへのドライバー
			static sql::Statement* stmt = nullptr;
			static sql::ResultSet* res = nullptr;
			static sql::Connection* con = nullptr;
		}
		MySQL::MySQL(void) {
			//何もない
		}
		MySQL::MySQL(std::string name, std::string password, std::string dataBase) {
			//接続する
			this->Conect(name, password, dataBase);
		}
		MySQL::MySQL(std::string name, std::string password) {
			//接続する
			this->Conect(name, password);
		}
		MySQL::~MySQL() {
			//何もしない
		}
		void MySQL::Conect(std::string name, std::string password, std::string dataBase) {
			StaticMysqlMember::driver = sql::mysql::get_mysql_driver_instance();//ドライバーの生成
			StaticMysqlMember::con = StaticMysqlMember::driver->connect("localhost", "root", "root");//ルートアカウント（アカウントを登録するためのやつ）に接続
			StaticMysqlMember::stmt = StaticMysqlMember::con->createStatement();
			StaticMysqlMember::stmt->execute(("USE " + dataBase).c_str());//目的のデータベース
		}
		void MySQL::Conect(std::string name, std::string password) {
			StaticMysqlMember::driver = sql::mysql::get_mysql_driver_instance();//ドライバーの生成
			StaticMysqlMember::con = StaticMysqlMember::driver->connect("localhost", "root", "root");//ルートアカウント（アカウントを登録するためのやつ）に接続
			StaticMysqlMember::stmt = StaticMysqlMember::con->createStatement();
		}
		void MySQL::SelectDatabase(std::string dataBase) {
			StaticMysqlMember::stmt->execute(("USE " + dataBase).c_str());//目的のデータベース
		}
		void MySQL::CutEnd(void) {
			if (StaticMysqlMember::con != nullptr) {
				StaticMysqlMember::con->close();
				delete StaticMysqlMember::con;
				StaticMysqlMember::con = nullptr;
			}
			if (StaticMysqlMember::res != nullptr) {
				StaticMysqlMember::res->close();
				delete StaticMysqlMember::res;
				StaticMysqlMember::res = nullptr;
			}
			if (StaticMysqlMember::stmt != nullptr) {
				StaticMysqlMember::stmt->close();
				delete StaticMysqlMember::stmt;
				StaticMysqlMember::stmt = nullptr;
			}
			if (StaticMysqlMember::driver != nullptr) {
				StaticMysqlMember::driver->threadEnd();
				StaticMysqlMember::driver->threadInit();
				delete StaticMysqlMember::driver;
				StaticMysqlMember::driver = nullptr;
			}
		}
		sql::ResultSet* MySQL::GetResultCrude(void) {
			sql::ResultSet* copy = StaticMysqlMember::res;
			StaticMysqlMember::res = nullptr;
			return copy;
		}
		void MySQL::RunSql(void) {
			if (sqlStr.find("SELECT") != -1) {
				if (StaticMysqlMember::res != nullptr) {
					StaticMysqlMember::res->close();
					delete StaticMysqlMember::res;
					StaticMysqlMember::res = nullptr;
				}
				StaticMysqlMember::res = StaticMysqlMember::stmt->executeQuery(MyTools::Encode::ShiftJis::UTF8(sqlStr).c_str());
			}
			else
				StaticMysqlMember::stmt->execute(MyTools::Encode::ShiftJis::UTF8(sqlStr).c_str());

			sqlStr = "";//初期化
		}
		std::string MySQL::GetResultStr(void) {
			if (StaticMysqlMember::res == nullptr) {
				columnType = "";
				return "";
			}

			std::string outStr = "";
			for (int r = 0; r < StaticMysqlMember::res->rowsCount(); r++) {
				StaticMysqlMember::res->next();
				for (int i = 0; i < columnType.length(); i++) {
					if (columnType[i] == 's' || columnType[i] == 'd')
						outStr += MyTools::Encode::UTF8::ShiftJis(StaticMysqlMember::res->getString(i + 1)) + ",";
					else if (columnType[i] == 'i')
						outStr += std::to_string(StaticMysqlMember::res->getInt(i + 1)) + ",";
					else//i,s,d以外
						outStr += std::to_string(StaticMysqlMember::res->getDouble(i + 1)) + ",";
				}
				outStr = outStr.substr(0, outStr.length() - 1) + '\n';
			}
			columnType = "";
			return outStr;
		}
#endif//MyTools_Database_MySQL
	}
}