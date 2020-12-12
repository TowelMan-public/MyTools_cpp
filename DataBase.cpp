#include "DataBase.h"

namespace MyTools {
	namespace Database {
		BasicDatabase::BasicDatabase(void) {
			sqlStr = "";
			columnType = "";
		}
		BasicDatabase::~BasicDatabase() {
			//�������Ȃ�
		}
#ifdef MyTools_Database_MySQL
		namespace StaticMysqlMember {
			static sql::mysql::MySQL_Driver* driver = nullptr;//�f�[�^�x�[�X�ւ̃h���C�o�[
			static sql::Statement* stmt = nullptr;
			static sql::ResultSet* res = nullptr;
			static sql::Connection* con = nullptr;
		}
		MySQL::MySQL(void) {
			//�����Ȃ�
		}
		MySQL::MySQL(std::string name, std::string password, std::string dataBase) {
			//�ڑ�����
			this->Conect(name, password, dataBase);
		}
		MySQL::MySQL(std::string name, std::string password) {
			//�ڑ�����
			this->Conect(name, password);
		}
		MySQL::~MySQL() {
			//�������Ȃ�
		}
		void MySQL::Conect(std::string name, std::string password, std::string dataBase) {
			StaticMysqlMember::driver = sql::mysql::get_mysql_driver_instance();//�h���C�o�[�̐���
			StaticMysqlMember::con = StaticMysqlMember::driver->connect("localhost", "root", "root");//���[�g�A�J�E���g�i�A�J�E���g��o�^���邽�߂̂�j�ɐڑ�
			StaticMysqlMember::stmt = StaticMysqlMember::con->createStatement();
			StaticMysqlMember::stmt->execute(("USE " + dataBase).c_str());//�ړI�̃f�[�^�x�[�X
		}
		void MySQL::Conect(std::string name, std::string password) {
			StaticMysqlMember::driver = sql::mysql::get_mysql_driver_instance();//�h���C�o�[�̐���
			StaticMysqlMember::con = StaticMysqlMember::driver->connect("localhost", "root", "root");//���[�g�A�J�E���g�i�A�J�E���g��o�^���邽�߂̂�j�ɐڑ�
			StaticMysqlMember::stmt = StaticMysqlMember::con->createStatement();
		}
		void MySQL::SelectDatabase(std::string dataBase) {
			StaticMysqlMember::stmt->execute(("USE " + dataBase).c_str());//�ړI�̃f�[�^�x�[�X
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

			sqlStr = "";//������
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
					else//i,s,d�ȊO
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