#ifndef _CSV_ACCESS_H_
#define _CSV_ACCESS_H_

#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*CSV文件操作类数据结构*/ 
class CSVFileAccess 
{
private:
	ifstream file_read;
	ofstream file_write;
	
	bool bfile_read;
	bool bfile_modify;
	string file_path;
	vector<vector<string> > BlockLines;

public:	
	CSVFileAccess(void);
	~CSVFileAccess();
	int Open(const char *pfilename);
	int Close(bool bsave_file = true);
	int SaveFile(void);
	int WriteBlock(const char *pstr, int row, int column);
	int ClearBlock(int row, int column);
	int ReadBlock(char *pstr, int row, int column);
	void PrintFile(void);
	
	int InsertRow(int row, bool bpos_after = false);
	int InsertColumn(int column, bool bpos_after = false);
	
	int DeleteRow(int row);
	int DeleteColumn(int column);
	
	int GetRowNum(void);
	int GetColumnNum(void);
};


#endif

