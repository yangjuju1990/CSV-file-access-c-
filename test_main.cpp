#include <iostream>
#include "csv_access.hpp"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	class CSVFileAccess csv_file;
	char strbuff[100];
	int d;
	cout<<"#################csv access proj test######################"<<endl;
	
	//打开文件 
	csv_file.Open("test.csv");
	//获取表格行列数 
	cout<<"RowNum"<<csv_file.GetRowNum()<<"  ColumnNum:"<<csv_file.GetColumnNum()<<endl;
	//读取表格内容 
	csv_file.ReadBlock(strbuff, 0, 1);
	//修改表格内容 
	csv_file.WriteBlock("cm", 0, 0);
	csv_file.InsertRow(0, true);
	csv_file.InsertColumn(1, false);
	//保存修改表格到文件 
	csv_file.SaveFile();
	//关闭文件 
	csv_file.Close(); 
	
	cin >> d;
	return 0;
}
