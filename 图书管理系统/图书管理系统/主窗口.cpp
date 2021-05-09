#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<cstdio>
#include<fstream>
#include "Book.h"
#define CMD_COLS 80
#define CMD_LINES 25
using namespace std;
void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
void ClearScreen()
{
	system("cls");
}
void SetSysCaption(const char* pText)
{
	system("title Sample");
}
void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "图书管理系统" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
void ShowRootMenu()
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}
void WaitView(int iCurpage)
{
	int inputPage = 0;
	cout << "enter 返回主菜单 q 退出 " << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q');
	system("exit");
}
void WaitUser()
{
	int inputPage = 0;
	cout << "enter 返回主菜单 q 退出 " << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q');
	system("exit");
}
void GuideInput()
{
	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入lSBN" << endl;
	cin >> inlsbn;
	cout << "输入价格" << endl;
	cin >> inPrice;
	cout << "输入作者" << endl;
	cin >> inAuthor;
	CBook book(inName, inlsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "Write Finsh" << endl;
	getchar();
	WaitUser();
}
int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}
long GetFileLength(istream& ifs)
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}
void ViewData(int iSelPage = 1)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];
	char inlsbn[NUM1];
	char price[NUM2];
	char inAuthor[NUM2];
	bool blndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
	{
		blndex = true;
	}
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "共有记录" << iDataCount << " ";
	cout << "共有页数" << iPage << " ";
	cout << "当前页数" << iCurPage << " ";
	cout << "n 显示下一页 m 返回" << endl;
	cout << setw(5) << "index";
	cout << setw(22) << "Name" << setw(22) << "lsbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2),ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);
				memset(inlsbn, 0, 128);
				memset(price, 0, 50);
				memset(inAuthor, 0, 50);
				if (blndex)
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inlsbn, NUM1);
				cout << setw(24) << inlsbn;
				ifile.read(price, NUM2);
				cout << setw(12) << price;
				ifile.read(inAuthor, NUM2);
				cout << setw(12) << inAuthor;
				cout << endl;
				if (ifile.tellg() < 0)
					blndex = false;
				else 
					blndex = true;
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if (iCurPage < iPage)
	{
		iCurPage++;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}
void DeleteBookFromFile()
{
	int iDelCount;
	cout << "input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finsh" << endl;
	WaitUser();
}
int main()
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		}
		
	}
}