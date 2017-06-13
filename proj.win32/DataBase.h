#pragma once
#ifndef  _DATABASE_H
#define _DATABASE_H
#include<cocos2d.h>
#include "SimpleAudioEngine.h"
#include "E:\temp1\proj.win32\sqlite3.h"



using namespace std;

class DataBase
{
public:
	DataBase();
	~DataBase();
	static DataBase* sharedDB();

	sqlite3 *pDB;//���ݿ�ָ��  
	std::string sqlstr;//SQLָ��  
	char * errMsg;//������Ϣ  
	int results;//sqlite3_exec����ֵ  

	bool OpenDBWithFileName(char *dbName);
	bool CreateTableWithContent(char *dbExec);
	bool IsTableExistedWithTableName(std::string dbExec);
	bool GetTableDataWithContent(std::string dbExec);
	bool InsertTableDataWithContent(std::string dbExec);
	bool DeleteTableDataWithContent(std::string dbExec);
	bool UpdateTableDataWithContent(std::string dbExec);
	bool ClearTableData(std::string dbExec);
	void CloseDB();

	void DeleteTable(string sql, string name);



	int GetPlayerInfoScores(std::string dbExec);
	bool GetPassInfoIsUnlockedWithIndex(std::string dbExec);
	int GetPassInfoStartsWithIndex(std::string dbExec);
};
#endif // ! _DATABASE_H

