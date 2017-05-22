#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
int campus_size=500;
int deposit_size=500;
int binding_size=0;
int trans(char* x)
{
	int l=strlen(x);
	int p=1;
	int ans=0;
	for(int i=l-1;i>=0;i--)
	{
		if(x[i]=='-')
		{
			ans*=-1;
		}
		else
		{
			ans+=p*(x[i]-'0');
			p*=10;
		}
	}
	return ans;
} 
class record{
	public:
		int y;
		int mon;
		int d;
		int h;
		int m;
		int cons;
		void show()
		{
			cout<<y<<"/"<<mon<<"/"<<d<<"/"<<h<<"/"<<m<<"/ "<<cons<<endl;
		}
};
class card{
	public:
		virtual void paying()=0;
		virtual void checking()=0;
		string num;
		string name;
		int money;
		record r[1000];
		int record_size;
		string code;
};
class campus_card:public card{
	public:
		campus_card()
		{
			card::code="000000";
			card::money=5000;
			card::name="Nobody";
			card::num="00000000";
			card::record_size=0;
			this->school="school";
		}
		void show()
		{
			while(1)
			{
				system("cls");
				int x;
				cout<<"功能选择"<<endl;
				cout<<"1.支付"<<endl;
				cout<<"2.查询信息"<<endl;
				cout<<"0.退卡"<<endl;
				cin>>x;
				if(x==1)
				{
					this->paying();
				}
				else if(x==2)
				{
					this->checking();
				}
				else
				{
					break;
				}
				system("pause");
			}
		}
		void checking()
		{
			while(1)
			{
				system("cls");
				int x;
				cout<<"请输入需要查询的信息类型"<<endl;
				cout<<"1.账户流水记录 2.本卡信息"<<endl;
				cin>>x;
				if(x==1)
				{
					for(int i=0;i<this->record_size;i++)
					{
						r[i].show();
					}
				}
				else
				{
					cout<<"本卡持有人："<<this->name<<endl;
					cout<<"持有人学院："<<this->school<<endl;
					cout<<"持有人学号："<<this->num<<endl;
				}
				cout<<"0.返回主界面 1.继续查询"<<endl;
				cin>>x;
				if(x==0) break;
				else;
			}
		}
		void paying()
		{
			system("cls");
			int mon;
			string c;
			cout<<"请输入支付数额"<<endl;
			cin>>mon;
			cout<<"请输入校园卡密码"<<endl;
			cin>>c;
			if(c==code)
			{
				if(mon>money)
				{
					cout<<"支付失败，用户余额不足"<<endl;
				}
				else
				{
					money-=mon;
					this->add_record(-mon); 
					cout<<"支付成功"<<endl;
					cout<<"用户余额为 "<<money<<endl; 
				} 	
			}
			else
			{
				cout<<"支付失败，密码错误"<<endl;
			}
		}
		void add_record(int y)
		{
			SYSTEMTIME sys_time;
			GetLocalTime( &sys_time );
			r[record_size].cons=y;
			this->r[record_size].y=sys_time.wYear;
			this->r[record_size].mon=sys_time.wMonth;
			this->r[record_size].d=sys_time.wDay;
			this->r[record_size].h=sys_time.wHour;
			this->r[record_size].m=sys_time.wMinute;
			record_size++;
		}
		string school;
};
class deposit_card:public card{
	public:
		deposit_card()
		{
			card::code="000000";
			card::money=5000;
			card::name="Nobody";
			card::num="00000000";
			card::record_size=0;
			this->limit=5000;
		}
		void show()
		{
			while(1)
			{
				system("cls");
				int x;
				cout<<"功能选择"<<endl;
				cout<<"1.支付"<<endl;
				cout<<"2.转账"<<endl;
				cout<<"3.存款"<<endl;
				cout<<"4.查询信息"<<endl;
				cout<<"0.退卡"<<endl;
				cin>>x;
				if(x==1)
				{
					this->paying();
				}
				else if(x==2)
				{
					this->transfer();
				}
				else if(x==3)
				{
					this->storing();
				}
				else if(x==4)
				{
					this->checking();
				}
				else
				{
					break;
				}
				system("pause");
			}
		}
		void storing()
		{
			while(1)
			{
				system("cls");
				int x;
				int mon;
				cout<<"请输入现金数目"<<endl;
				cin>>mon;
				this->money+=mon;
				this->add_record(mon);
				cout<<"存款成功"<<endl;
				cout<<"0.返回主界面 1.继续存款"<<endl;
				cin>>x;
				if(x==0) break;
				else;
			}
		}
		void checking()
		{
			system("cls");
			int x;
			cout<<"请输入需要查询的信息类型"<<endl;
			cout<<"1.账户流水记录 2.本卡信息"<<endl;
			cin>>x;
			if(x==1)
			{
				for(int i=0;i<this->record_size;i++)
				{
					r[i].show();
				}
			}
			else
			{
				cout<<"本卡卡号："<<this->num<<endl;
				cout<<"本卡持有人："<<this->name<<endl;
				cout<<"本卡透支额度"<<limit<<endl;
			}
		}
		void paying()
		{
			system("cls");
			int mon;
			string c;
			cout<<"请输入支付数额"<<endl;
			cin>>mon;
			cout<<"请输入储蓄卡密码"<<endl;
			cin>>c;
			if(c==code)
			{
				if(mon>money+limit)
				{
					cout<<"支付失败，用户余额不足"<<endl;
				}
				else
				{
					if(mon>money)
					{
						cout<<"透支 "<<(mon-money)<<" 元"<<endl;
						limit-=(mon-money);
						mon=0;
					}
					else
					{
						money-=mon;
					}
					this->add_record(-mon); 
					cout<<"支付成功"<<endl;
					cout<<"用户余额："<<money<<endl; 
					cout<<"用户透支额："<<limit<<endl;
				} 	
			}
			else
			{
				cout<<"支付失败，密码错误"<<endl;
			}
		}
		void add_record(int y)
		{
			SYSTEMTIME sys_time;
			GetLocalTime( &sys_time );
			this->r[record_size].y=sys_time.wYear;
			this->r[record_size].mon=sys_time.wMonth;
			this->r[record_size].d=sys_time.wDay;
			this->r[record_size].h=sys_time.wHour;
			this->r[record_size].m=sys_time.wMinute;
			this->r[record_size].cons=y;
			record_size++;
		}
		void transfer();
		int limit;	
};
class binding_card:public campus_card,public deposit_card{
	public:
		int card_num[1000];
		int num_size;
		/*void binding()
		{
			while(1)
			{
				int x,y;
				cout<<"请输入需要绑定的储蓄卡号"<<endl;
				cin>>y;
				int i=find_deposit(y);
				if(i!=-1)
				{
					cout<<"请输入储蓄卡密码"<<endl;
					card_num[num_size]=y;
					num_size++;
				}
				else
				{
					pos[deposit_size].num=y;
					deposit_size++;
					card_num[num_size]=y;
					num_size++;
				}
				cout<<"绑定成功"<<endl;
				cout<<"0.返回主界面 1.继续绑定储蓄卡"<<endl;
				cin>>x;
				if(x==0) break;
				else;
			}
		}*/
};
campus_card cam[1000];
deposit_card pos[1000];
int find_campus(string x)
{
	for(int i=0;i<campus_size;i++)
	{
		if(x==cam[i].num)
		{
			return i;
		}
	}
	return -1;
}
int find_deposit(string x)
{
	for(int i=0;i<deposit_size;i++)
	{
		if(x==pos[i].num)
		{
			return i;
		}
	}
	return -1;
}
void deposit_card::transfer()
		{
			while(1)
			{
				int mon,x;
				string y; 
				string c;
				cout<<"请选择待转账卡类型"<<endl;
				cout<<"1.储蓄卡 2.校园卡"<<endl;
				cin>>x;
				cout<<"请输入待转账卡号"<<endl;
				cin>>y;
				cout<<"请输入转账数额"<<endl;
				cin>>mon;
				cout<<"请输入储蓄卡密码"<<endl;
				cin>>c;
				if(c==code)
				{
					if(mon>money+limit)
					{
						cout<<"转账失败，用户余额不足"<<endl;
					}
					else
					{
						this->add_record(-mon);
						if(mon>money)
						{
							cout<<"透支 "<<(mon-money)<<" 元"<<endl;
							limit-=(mon-money);
							mon=0;
						}
						else
						{
							money-=mon;
						}
						cout<<"转账成功"<<endl;
						if(x==1)
						{
							int i=find_deposit(y);
							if(i!=-1)
							{
								pos[i].add_record(mon);
								pos[i].money+=mon;
							}
							else
							{
								pos[deposit_size].num=y;
								pos[deposit_size].money+=mon;
								pos[deposit_size].add_record(mon);
								deposit_size++;
							}
						}
						else
						{
							int i=find_campus(y);
							if(i!=-1)
							{
								cam[i].add_record(mon);
								cam[i].money+=mon;
							}
							else
							{
								cam[campus_size].num=y;
								cam[campus_size].money+=mon;
								cam[campus_size].add_record(mon);
								campus_size++;
							}
						}
						cout<<"用户余额："<<this->money<<endl;
					}
				}
				else
				{
					cout<<"密码错误"<<endl;
				}
				cout<<"0.返回主界面 1.继续转账"<<endl;
				cin>>x;
				if(x==0) break;
				else;
			}
		}
void UI()
{
	while(1)
	{
		cout<<"card manage system"<<endl;
		string y;
		cout<<"请输入储蓄卡或校园卡号,或输入0退出系统"<<endl;
		cin>>y;
		if(y=="0") break;
		else
		{
			int x;
			if(find_deposit(y)!=-1)
			{
				x=find_deposit(y);
				pos[x].show();
			}
			else if(find_campus(y)!=-1)
			{
				x=find_campus(y);
				cam[x].show();
			}
			else
			{
				cout<<"此卡不存在，是否创建新卡?"<<endl;
				cout<<"0.返回主界面 1.创建新卡"<<endl;
				cin>>x;
				if(x==1)
				{
					cout<<"0.创建校园卡 1.创建储蓄卡"<<endl;
					cin>>x;
					if(x==0)
					{
						campus_size++;
						cout<<"创建成功"<<endl;
						cout<<"本卡卡号："<<cam[campus_size-1].num<<endl;
						cout<<"本卡密码：000000，请牢记密码"<<endl;
					}
					else
					{
						deposit_size++;
						cout<<"创建成功"<<endl;
						cout<<"本卡卡号："<<pos[deposit_size-1].num<<endl;
						cout<<"本卡密码：000000，请牢记密码"<<endl;
					}
				}
				else;
			}
		}
		system("cls");
	}
}
void Initialize()
{
	char in[200];
	ifstream cardlist("card_information.txt");
	cardlist.getline(in,100);
	campus_size=trans(in);
	{
		for(int i=0;i<campus_size;i++)
		{
			cardlist.getline(in,100);;
			cam[i].num=in;
			cardlist.getline(in,100);
			cam[i].name=in;
			cardlist.getline(in,100);
			cam[i].code=in;
			cardlist.getline(in,100);
			cam[i].money=trans(in);
			cardlist.getline(in,100);
			cam[i].school=in;
			cardlist.getline(in,100);
			cam[i].record_size=trans(in);
			for(int j=0;j<cam[i].record_size;j++)
			{
				cardlist.getline(in,100);
				cam[i].r[j].y=trans(in);
				cardlist.getline(in,100);
				cam[i].r[j].mon=trans(in);
				cardlist.getline(in,100);
				cam[i].r[j].d=trans(in);
				cardlist.getline(in,100);
				cam[i].r[j].h=trans(in);
				cardlist.getline(in,100);
				cam[i].r[j].m=trans(in);
				cardlist.getline(in,100);
				cam[i].r[j].cons=trans(in);
			}
		}
	}
	cardlist.getline(in,100);
	deposit_size=trans(in);
	{
		for(int i=0;i<deposit_size;i++)
		{
			cardlist.getline(in,100);;
			pos[i].num=in;
			cardlist.getline(in,100);
			pos[i].name=in;
			cardlist.getline(in,100);
			pos[i].code=in;
			cardlist.getline(in,100);
			pos[i].money=trans(in);
			cardlist.getline(in,100);
			pos[i].limit=trans(in);
			cardlist.getline(in,100);
			pos[i].record_size=trans(in);
			for(int j=0;j<pos[i].record_size;j++)
			{
				cardlist.getline(in,100);
				pos[i].r[j].y=trans(in);
				cardlist.getline(in,100);
				pos[i].r[j].mon=trans(in);
				cardlist.getline(in,100);
				pos[i].r[j].d=trans(in);
				cardlist.getline(in,100);
				pos[i].r[j].h=trans(in);
				cardlist.getline(in,100);
				pos[i].r[j].m=trans(in);
				cardlist.getline(in,100);
				pos[i].r[j].cons=trans(in);
			}
		}
	}
	cardlist.close();
}
void Save()
{
	ofstream cardlist("card_information.txt",ios::out);
	cardlist<<campus_size<<endl;
	for(int i=0;i<campus_size;i++)
	{
		cardlist<<cam[i].num<<endl;
		cardlist<<cam[i].name<<endl;
		cardlist<<cam[i].code<<endl;
		cardlist<<cam[i].money<<endl;
		cardlist<<cam[i].school<<endl;
		cardlist<<cam[i].record_size<<endl;
		for(int j=0;j<cam[i].record_size;j++)
		{
			cardlist<<cam[i].r[j].y<<endl;
			cardlist<<cam[i].r[j].mon<<endl;
			cardlist<<cam[i].r[j].d<<endl;
			cardlist<<cam[i].r[j].h<<endl;
			cardlist<<cam[i].r[j].m<<endl;
			cardlist<<cam[i].r[j].cons<<endl;
		}
	}
	cardlist<<campus_size<<endl;
	for(int i=0;i<campus_size;i++)
	{
		cardlist<<pos[i].num<<endl;
		cardlist<<pos[i].name<<endl;
		cardlist<<pos[i].code<<endl;
		cardlist<<pos[i].money<<endl;
		cardlist<<pos[i].limit<<endl;
		cardlist<<pos[i].record_size<<endl;
		for(int j=0;j<pos[i].record_size;j++)
		{
			cardlist<<pos[i].r[j].y<<endl;
			cardlist<<pos[i].r[j].mon<<endl;
			cardlist<<pos[i].r[j].d<<endl;
			cardlist<<pos[i].r[j].h<<endl;
			cardlist<<pos[i].r[j].m<<endl;
			cardlist<<pos[i].r[j].cons<<endl;
		}
	}
	cardlist.close();
} 
int main()
{
	/*for(int i=0;i<5;i++)
	{
		for(int j=0;j<10;j++)
		{
			for(int k=0;k<10;k++)
			{
				if(i==0&&j==0&&k==0);
				else
				{
					cam[i*100+j*10+k].num[3]=k+'0';
					cam[i*100+j*10+k].num[2]=j+'0';
					cam[i*100+j*10+k].num[1]=i+'0';
					pos[i*100+j*10+k].num[7]=k+'0';
					pos[i*100+j*10+k].num[6]=j+'0';
					pos[i*100+j*10+k].num[5]=i+'0';
				}
			}
		}
	}*/
	Initialize();
	UI();
	Save();
} 
