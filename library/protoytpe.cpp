#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;
struct Book
{
	string name;
	bool isbro=0;
	int num=0;
};
Book book[101];
int lastbook=0,exsys=0;
void AddBook(string str)
{
	int i;
	for(i=1;i<=lastbook;i++)
	{
		if(str==book[i].name)
		{
			book[i].num++;
			break;
		}
	}
	if(i==lastbook+1)
	{
		book[i+1]=book[i];
		book[i].name=str;
		book[i].num++;
		lastbook++;
	}
}
void DelBook(string str)
{
	int i;
	for(i=1;i<=lastbook;i++)
	{
		if(str==book[i].name)
		{
			book[i].num--;
			break;
		}
	}
	if(book[i].num==0)
	{
		for(;i<lastbook;i++)
		{
			book[i]=book[i+1];
		}
		lastbook--;
		book[lastbook+1]=book[lastbook+2];
	}
}
void BroBook(string str)
{
	for(int i=1;i<=lastbook;i++)
	{
		if(str==book[i].name)
		{
			book[i].num--;
			book[i].isbro=1;
			break;
		}
	}
}
void RetBook(string str)
{
	for(int i=1;i<=lastbook;i++)
	{
		if(str==book[i].name)
		{
			book[i].num++;
			book[i].isbro=0;
			break;
		}
	}
}
void Check()
{
	cout<<"书名       状态      数目"<<endl; 
	for(int i=1;i<=lastbook;i++)
	{
		cout<<left<<setw(11)<<book[i].name;
		if(book[i].isbro==0)
		{
			cout<<left<<setw(10)<<"在书堆中";
		}
		else
		{
			cout<<left<<setw(10)<<"被借阅中";
		}
		cout<<book[i].num<<endl;
	}
	cout<<endl<<endl<<endl<<endl<<endl;
}
void CheckBook(string str)
{
	int i;
	for(i=1;i<=lastbook;i++)
	{
		if(str==book[i].name)
		{
			cout<<str<<"的状态是";
			if(book[i].isbro==0)
			{
				cout<<" 在书堆中"<<endl;
			}
			else
			{
				cout<<" 被借阅中"<<endl;
			} 
			break;
		}
	}
	if(i==lastbook+1)
	{
		cout<<"您所查找的书目不存在"<<endl; 
	}
	system("pause");
}
void ui()
{
	system("cls");
	cout<<"LRD图书管理系统"<<endl<<endl;
	Check();
	int x;
	cout<<"请输入对应标号选择功能"<<endl;
	cout<<"1.查找书目"<<endl;
	cout<<"2.添加/删除 书目"<<endl;
	cout<<"3.借阅/归还 书目"<<endl;
	cout<<"4.退出系统"<<endl;
	cin>>x;
	system("cls");
	cout<<"LRD图书管理系统"<<endl<<endl;
	if(x==1)
	{
		string str;
		cout<<"请输入想要查找的书名"<<endl;
		cin>>str;
		CheckBook(str);
	}
	if(x==2)
	{
		int x;
		string str;
		cout<<"请输入对应标号选择功能"<<endl;
		cout<<"1.添加书目"<<endl;
		cout<<"2.删除书目"<<endl;
		cin>>x;
		if(x==1)
		{
			cout<<"请输入想要添加的书名"<<endl;
			cin>>str; 
			AddBook(str);
		}
		else
		{
			cout<<"请输入想要删除的书名"<<endl;
			cin>>str;
			DelBook(str);
		}
		system("cls");
	}
	if(x==3)
	{
		int x;
		string str;
		cout<<"请输入对应标号选择功能"<<endl;
		cout<<"1.借阅书目"<<endl;
		cout<<"2.归还书目"<<endl;
		cin>>x;
		if(x==1)
		{
			cout<<"请输入想要借阅的书名"<<endl;
			cin>>str; 
			BroBook(str);
		}
		else
		{
			cout<<"请输入想要归还的书名"<<endl;
			cin>>str;
			RetBook(str);
		}
	}
	if(x==4)
	{
		exsys=1;
	}
}
int main(void)
{
	char in[200];
	int num=0,i;
	fstream booklist("booklist.txt");
	booklist.getline(in,100);
	while(!booklist.eof())
	{
		num++;
		booklist.getline(in,100);
		for(int j=0;j<100;j++)
		{
			book[num].name[j]=in[j];
		}
		booklist.getline(in,100);
		book[num].num=in[0]-48;
		booklist.getline(in,100);
		book[num].isbro=in[0]-48;
	}
	lastbook=num;
	while(exsys==0)
	{
		ui();
	}
	for(i=1;i<=lastbook;i++)
	{
		booklist<<book[i].name<<endl<<book[i].num<<endl<<book[i].isbro<<endl;
	}
	booklist.close();
	return 0;
}
