#include <sstream>
#include <iostream>
#include <string.h>
#include "csv_access.hpp"

CSVFileAccess::CSVFileAccess(void) 
	:bfile_read(false),
	 bfile_modify(false)
{
	
}

CSVFileAccess::~CSVFileAccess()
{
	
}

/*打开文件，在调用其他方法操作csv文件前请先调用此方法打开文件
 *文件存在则打开并读取文件内容，文件不存在则新建一个 
 */
int CSVFileAccess::Open(const char *pfilename)
{
	string strline;
	string blockstr;
	stringstream ss;
	vector<string> BlockLine;
	
	file_read.open(pfilename, ios::in);
	
	if (!file_read.is_open()) 
	{
		file_write.open(pfilename, ios::out);
		
		if (!file_write.is_open())
			return -1;
	}
		
	while (getline(file_read, strline))
	{
//		cout<<strline<<endl;
		ss.str(strline);
		while (getline(ss, blockstr, ',')) 
		{
			BlockLine.push_back(blockstr);
		}
		
		BlockLines.push_back(BlockLine);
		BlockLine.clear();
		ss.clear();
	}
	
	if (file_read.is_open()) 
		file_read.close();
	file_path.assign(pfilename);
	bfile_read = true;
		
	return 0;
}

/*关闭文件，在文件操作完成后调用此方法关闭打开的文件 
 *默认关闭文件同时会保存文件修改，参数 bsave_file为false时将不保存修改 
 */
int CSVFileAccess::Close(bool bsave_file)
{
	SaveFile();
	if (file_read.is_open()) 
		file_read.close();
	if (file_write.is_open()) 
		file_write.close();
}

/*保存文件，调用此方法保存文件修改 
 *
 */
int CSVFileAccess::SaveFile(void)
{
	int i, j;
	
	if (!bfile_read)
		return -3;
	if (!bfile_modify)
		return 0;
	
	if (!file_write.is_open()) 
	{
		file_write.open(file_path.c_str(), ios::out | ios::trunc);
		
		if (!file_write.is_open())
			return -1;
	}
	
	for (i = 0; i < BlockLines.size(); i++) 
	{
		for(j = 0; j < BlockLines[0].size(); j++)
		{
			file_write << BlockLines[i][j] << ",";
		}
		file_write << endl;
	}
}

/*输出文件内容到控制台
 *
 */
void CSVFileAccess::PrintFile(void) 
{
	int i, j;
	
	for (i = 0; i < BlockLines.size(); i++) 
	{
		for(j = 0; j < BlockLines[0].size(); j++)
		{
			cout<<BlockLines[i][j] << ",";
		}
		cout << endl;
	}
}

/*将内容写入指定行列表格内 
 *csv文件是文本格式文件，因而写入的内容只能是文本字符串 
 */
int CSVFileAccess::WriteBlock(const char *pstr, int row, int column)
{
	string blockstr;
	vector<string> BlockLine;
	int i = 0;
	
	if (!bfile_read)
		return -3;
	
	while(BlockLines.size() <= row)
	{
		BlockLines.push_back(BlockLine);
		
	}
	
	for (i = 0; i < BlockLines.size(); i++)
	{
		while (BlockLines[i].size() <= column)
		{
			BlockLines[i].push_back(blockstr);
		}
	}
	
	BlockLines[row][column].assign(pstr);
	
	bfile_modify = true;

	return 0;
}

/*清空指定行列表格的内容 
 *
 */
int CSVFileAccess::ClearBlock(int row, int column)
{
	if (!bfile_read)
		return -1;
	
	if (BlockLines.size() <= row)
		return -2;
	
	if (BlockLines[0].size() <= column)
		return -3;
		
	BlockLines[row][column].assign("");
}

/*读取指定行列的表格内容 
 * 读取的内容是文本字符串 
 */
int CSVFileAccess::ReadBlock(char *pstr, int row, int column)
{
	string blockstr;
	
	if (!bfile_read)
		return -1;
	
	if (BlockLines.size() <= row)
		return -2;
	
	if (BlockLines[0].size() <= column)
		return -3;
	
	blockstr = BlockLines[row][column];
	strcpy(pstr, blockstr.c_str());
	
	return 0;
}

/*在指定行前/后插入一个空行 
 *
 */	
int CSVFileAccess::InsertRow(int row, bool bpos_after)
{
	vector<string> BlockLine;
	string blockstr;
	int column_num;
	
	if (!bfile_read)
		return -1;
		
	if (BlockLines.size() == 0 && row == 0) 
	{
		BlockLines.push_back(BlockLine);
		return 0;
	}
	
	if (BlockLines.size() <= row)
		return -2;
	
	if (bpos_after)
		row++;
	column_num = BlockLines[0].size();
	
	BlockLines.insert(BlockLines.begin() + row, BlockLine);
	
	while (BlockLines[row].size() < column_num)
	{
		BlockLines[row].push_back(blockstr);
	}
	
	bfile_modify = true;
	
	return 0;
}	

/*在指定列前/后插入一个空列 
 *
 */	
int CSVFileAccess::InsertColumn(int column, bool bpos_after)
{
	vector<string> BlockLine;
	string blockstr;
	int i;
	
	if (!bfile_read)
		return -1;
	
	if (BlockLines.size() == 0) 
		return -2;
	
//	if (column == 0 && BlockLines[0].size() == 0) 
//	{
//		BlockLines[0].push_back(blockstr);
//		return 0;
//	}
	
	if (BlockLines[0].size() <= column && column != 0)
		return -3;
	
	if (bpos_after && BlockLines[0].size() != 0)
		column++;
	
	for (i=0; i<BlockLines.size(); i++)
		BlockLines[i].insert(BlockLines[i].begin() + column, blockstr);
		
	bfile_modify = true;
	return 0;
}

/*删除CSV表格的指定一行 
*
*/	
int CSVFileAccess::DeleteRow(int row)
{
	
}

/*删除CSV表格的指定一列 
*
*/
int CSVFileAccess::DeleteColumn(int column)
{
	
}

/*获取CSV表格总行数 
*
*/
int CSVFileAccess::GetRowNum(void)
{
	int ret;
	
	ret = BlockLines.size();
	return ret;
}

/*获取CSV表格总列数 
*
*/
int CSVFileAccess::GetColumnNum(void)
{
	int ret;
	
	if (BlockLines.size() < 1)
		return 0;
		
	ret = BlockLines[0].size();
	return ret;
}


