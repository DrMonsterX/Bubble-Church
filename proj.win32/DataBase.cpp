#include "DataBase.h"
#include "E:\temp1\proj.win32\sqlite3.h"


USING_NS_CC;


DataBase::DataBase()
{

	//=================DB========================[  
	pDB = NULL;//���ݿ�ָ��  
	sqlstr = "";//SQLָ��  
	errMsg = NULL;//������Ϣ  
	results = -1;//sqlite3_exec����ֵ  


}

DataBase::~DataBase()
{
}


DataBase *DataBase::sharedDB()
{
	static DataBase sharedDb;
	return &sharedDb;
}


/*
* //�����ݿ����ж���Ϊname�ı�ʾ����ڣ�����������򴴽����ű�
//@ʾ�����string sqls = "create table user(id integer,username text,password text)";
*
* //ɾ�����
//@ʾ�����sqlstr="drop table name";
*
* **/








//====================================================================  
//============================ ���ݿ� ====================================  
//====================================================================  

//��һ�����ݿ⣬��������ݿⲻ���ڣ��򴴽�һ�����ݿ��ļ�  
/*
* data.db
* */

bool  DataBase::OpenDBWithFileName(char *dbName)
{
	bool success = false;
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath()
		+ dbName;
	int result = sqlite3_open(path.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		log("SQLITE_OK:%d", SQLITE_OK);
		log("open db failed ��error :%d ��cause: %s ", result, errMsg);
		success = false;
	}
	else
	{
		log("open db success  ");
		success = true;
	}

	return success;
}



//����������IDΪ���������Զ�����  
//create table playerinfo( ID integer primary key autoincrement, playername nvarchar(32),playerscores int )  
bool  DataBase::CreateTableWithContent(char *dbExec)
{
	bool success = false;

	int result = sqlite3_exec(pDB, dbExec, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		//CCLog("create table failed ��error :%d ��cause: %s ", result, errMsg);
		success = false;
	}
	else
	{
		//CCLog("create table success  ");
		success = true;
	}

	return success;
}


//�жϱ��Ƿ����  

bool  DataBase::IsTableExistedWithTableName(std::string dbExec)
{
	bool success = false;

	std::string dbExecs = "";
	dbExecs.append("select count(type) from sqlite_master where type='table' and name='");
	dbExecs.append(dbExec);
	dbExecs.append("'");

	int result = sqlite3_exec(pDB, dbExecs.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		log("table not exist ");
		success = false;
	}
	else
	{
		log("table  is  existed ");
		success = true;
	}

	return success;
}
int isExisted(void * para, int n_column, char ** column_value, char ** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}


// ��ȡ����  
bool DataBase::GetTableDataWithContent(std::string dbExec)
{
	bool success = false;

	int result = sqlite3_exec(pDB, dbExec.c_str(), NULL, NULL, &errMsg); //   loadRecord  
	if (result != SQLITE_OK)
	{
		log("get GetTableDataWithContent failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("get GetTableDataWithContent success ");
		success = true;
	}

	return success;
}


//��������  
//insert into playerinfo( playername,playerscores  ) values ( '����֮ˮ', 683500 )  
bool DataBase::InsertTableDataWithContent(std::string dbExec)
{
	bool success = false;

	int result = sqlite3_exec(pDB, dbExec.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		log("insert failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("insert success  ");
		success = true;
	}

	return success;
}

//ɾ������  delete from playerinfo where playername = 'default2'  
bool DataBase::DeleteTableDataWithContent(std::string dbExec)
{
	bool success = false;

	int result = sqlite3_exec(pDB, dbExec.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		log("delete failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("delete success  ");
		success = true;
	}

	return success;
}



//��������   update gamepass set passisunlocked=1  where passindex = 2  
bool DataBase::UpdateTableDataWithContent(std::string dbExec)
{
	bool success = false;

	int result = sqlite3_exec(pDB, dbExec.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		log("update failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("update success ");
		success = true;
	}

	return success;
}

// �������  
bool DataBase::ClearTableData(std::string dbExec)
{
	bool success = false;

	std::string dbExecs = "";
	dbExecs.append("delete from  ");
	dbExecs.append(dbExec);
	dbExecs.append(" ");

	int result = sqlite3_exec(pDB, dbExecs.c_str(), NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
		log("clear failed��error:%d ��cause :%s ", result, errMsg);
		success = false;
	}
	else
	{
		log(" clear db success   ");
		success = true;
	}

	return success;
}

//�ر����ݿ�  
void DataBase::CloseDB()
{
	sqlite3_close(pDB);
}


//=================================================  
int DataBase::GetPlayerInfoScores(std::string dbExec)
{
	bool success = false;
	int scores = 0;

	sqlite3_stmt *statement = NULL;
	int result = sqlite3_prepare(pDB, dbExec.c_str(), dbExec.length(), &statement, 0);
	if (result != SQLITE_OK)
	{
		log("get GetPlayerInfo failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("get GetPlayerInfo success  ");
		success = true;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			scores = sqlite3_column_int(statement, 2);
		};

	}

	return scores;
}

bool DataBase::GetPassInfoIsUnlockedWithIndex(std::string dbExec)
{
	bool success = false;
	bool isUnlocked = false;

	sqlite3_stmt *statement = NULL;
	int result = sqlite3_prepare(pDB, dbExec.c_str(), dbExec.length(), &statement, 0);
	if (result != SQLITE_OK)
	{
		log("get GetPlayerInfo failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("get GetPlayerInfo success  ");
		success = true;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			(sqlite3_column_int(statement, 3) == 1) ? (isUnlocked = true) : (isUnlocked = false);
		};

	}

	return isUnlocked;
}

//select *  from  gamepass  where passindex =2  
int DataBase::GetPassInfoStartsWithIndex(std::string dbExec)
{
	bool success = false;
	int starts = 0;

	sqlite3_stmt *statement = NULL;
	int result = sqlite3_prepare(pDB, dbExec.c_str(), dbExec.length(), &statement, 0);
	if (result != SQLITE_OK)
	{
		log("get GetPlayerInfo failed��error :%d ��cause:%s ", result, errMsg);
		success = false;
	}
	else
	{
		log("get GetPlayerInfo success  ");
		success = true;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			starts = sqlite3_column_int(statement, 3);
		};

	}

	return starts;
}

//@ʾ�����sqlstr="drop table name";  
void DataBase::DeleteTable(string sql, string name) {

	if (IsTableExistedWithTableName(name))
	{
		int result = sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errMsg);
		if (result != SQLITE_OK)
			log("������ʧ�ܣ�������:%d ������ԭ��:%s\n", result, errMsg);
	}
}




