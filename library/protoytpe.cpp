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
	cout<<"����       ״̬      ��Ŀ"<<endl; 
	for(int i=1;i<=lastbook;i++)
	{
		cout<<left<<setw(11)<<book[i].name;
		if(book[i].isbro==0)
		{
			cout<<left<<setw(10)<<"�������";
		}
		else
		{
			cout<<left<<setw(10)<<"��������";
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
			cout<<str<<"��״̬��";
			if(book[i].isbro==0)
			{
				cout<<" �������"<<endl;
			}
			else
			{
				cout<<" ��������"<<endl;
			} 
			break;
		}
	}
	if(i==lastbook+1)
	{
		cout<<"�������ҵ���Ŀ������"<<endl; 
	}
	system("pause");
}
void ui()
{
	system("cls");
	cout<<"LRDͼ�����ϵͳ"<<endl<<endl;
	Check();
	int x;
	cout<<"�������Ӧ���ѡ����"<<endl;
	cout<<"1.������Ŀ"<<endl;
	cout<<"2.���/ɾ�� ��Ŀ"<<endl;
	cout<<"3.����/�黹 ��Ŀ"<<endl;
	cout<<"4.�˳�ϵͳ"<<endl;
	cin>>x;
	system("cls");
	cout<<"LRDͼ�����ϵͳ"<<endl<<endl;
	if(x==1)
	{
		string str;
		cout<<"��������Ҫ���ҵ�����"<<endl;
		cin>>str;
		CheckBook(str);
	}
	if(x==2)
	{
		int x;
		string str;
		cout<<"�������Ӧ���ѡ����"<<endl;
		cout<<"1.�����Ŀ"<<endl;
		cout<<"2.ɾ����Ŀ"<<endl;
		cin>>x;
		if(x==1)
		{
			cout<<"��������Ҫ��ӵ�����"<<endl;
			cin>>str; 
			AddBook(str);
		}
		else
		{
			cout<<"��������Ҫɾ��������"<<endl;
			cin>>str;
			DelBook(str);
		}
		system("cls");
	}
	if(x==3)
	{
		int x;
		string str;
		cout<<"�������Ӧ���ѡ����"<<endl;
		cout<<"1.������Ŀ"<<endl;
		cout<<"2.�黹��Ŀ"<<endl;
		cin>>x;
		if(x==1)
		{
			cout<<"��������Ҫ���ĵ�����"<<endl;
			cin>>str; 
			BroBook(str);
		}
		else
		{
			cout<<"��������Ҫ�黹������"<<endl;
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
