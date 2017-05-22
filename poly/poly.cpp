#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#define MAX 99999999
using namespace std;
int count=0;
int trans(string x)
{
	int ans=0;
	int p=1;
	for(int i=x.size()-1;i>=0;i--)
	{
		ans+=(x.at(i)-'0')*p;
		p*=10;
	}
	return ans;
}

bool isLegal(string str)
{
	int len=str.size();
	int maxexpo=MAX;
	int j;
	int l;
	int k;
	{
		for(j=0;j<len;j++)
		{
			if(str[j]=='(')
			{
				//cout<<str[j]<<endl;
				if(str[j+1]=='-') j++;
				for(k=j+1;k<len;k++)
				{
					if(str[k]=='0'||str[k]=='1'||str[k]=='2'||str[k]=='3'||str[k]=='4'||str[k]=='5'||str[k]=='6'||str[k]=='7'||str[k]=='8'||str[k]=='9');
			 		else break;
				}
				if(k==j+1||str[k]!=','||k==len) return false;
				else
				{
				//	cout<<str[k]<<endl;
					l=k;
					for(k=l+1;k<len;k++)
					{
						if(str[k]=='0'||str[k]=='1'||str[k]=='2'||str[k]=='3'||str[k]=='4'||str[k]=='5'||str[k]=='6'||str[k]=='7'||str[k]=='8'||str[k]=='9');
			 			else break;
					}
				}
				if(k==l+1||str[k]!=')'||k==len) return false;
				else
				{
				//	cout<<str[k]<<endl;
					string temp=str.substr(l+1,k-l-1);
				//	cout<<trans(temp)<<endl;
					int x=trans(temp);
					if(x>=maxexpo) return false;
					else maxexpo=x;
					j=k;
				}
			}
			else return false;
		}
	}
	if(j==len)	return true;
	else return false;
}
class poly
{
	public:
		poly()
		{
			name="default";
		}
		poly(poly &x)
		{
			this->c=x.c;
			this->n=x.n;
			this->name=x.name;
		}
		string name;
		vector<int>c;
		vector<int>n;
		void initial(string str)
		{
			int len=str.size();
			int flag;
			int j;
			int l;
			int k;
			{
				for(j=0;j<len;j++)
				{
					if(str[j]=='(')
					{
						flag=1;
						//cout<<str[j]<<endl;
						if(str[j+1]=='-')
						{
							flag=-1;
							j++;
						}
						for(k=j+1;k<len;k++)
						{
							if(str[k]=='0'||str[k]=='1'||str[k]=='2'||str[k]=='3'||str[k]=='4'||str[k]=='5'||str[k]=='6'||str[k]=='7'||str[k]=='8'||str[k]=='9');
				 			else break;
						}
						//	cout<<str[k]<<endl;
						string temp=str.substr(j+1,k-j-1);
						//	cout<<trans(temp)<<endl;
						int x=trans(temp)*flag;
						c.push_back(x);
						l=k;
						for(k=l+1;k<len;k++)
						{
							if(str[k]=='0'||str[k]=='1'||str[k]=='2'||str[k]=='3'||str[k]=='4'||str[k]=='5'||str[k]=='6'||str[k]=='7'||str[k]=='8'||str[k]=='9');
				 			else break;
						}
						//	cout<<str[k]<<endl;
						temp=str.substr(l+1,k-l-1);
						//	cout<<trans(temp)<<endl;
						x=trans(temp);
						n.push_back(x);
						j=k;
					}
				}
			}
		}
		bool isEqual(poly x)
		{
			int i,j=0,k=0;
			int max=this->c.size()>x.c.size()?this->c.size():x.c.size();
			for(i=0;i<x.c.size()+this->c.size();i++)
			{
				if(j>=this->c.size()&&k>=x.c.size())
				{
					return true;
				}
				else if(j<this->c.size()&&k>=x.c.size())
				{
					if(this->c[j]==0)
					{
						j++;
					}
					else return false;
				}
				else if(j>=this->c.size()&&k<x.c.size())
				{
					if(x.c[k]==0)
					{
						k++;
					}
					else return false;
				}
				else
				{
					if(this->n[j]==x.n[k])
					{
						if(this->c[j]==x.c[k])
						{
							j++;
							k++;
						}
						else return false;
					}
				}
			}
		}
		poly& operator =(const poly &x)
		{
			this->c=x.c;
			this->n=x.n;
			this->name=x.name;
		}
		poly multx(int x)
		{
			poly temp;
			temp=*this;
			for(int i=0;i<c.size();i++)
			{
				temp.c[i]*=x;
			}
			return temp;
		}
		poly add(poly x)
		{
			poly temp;
			int i,j=0,k=0;
			int max=this->c.size()>x.c.size()?this->c.size():x.c.size();
			for(i=0;i<x.c.size()+this->c.size();i++)
			{
				if(j>=this->c.size()&&k>=x.c.size()) break;
				else if(j<this->c.size()&&k>=x.c.size())
				{
					temp.c.push_back(this->c[j]);
					temp.n.push_back(this->n[j]);
					j++;
				}
				else if(j>=this->c.size()&&k<x.c.size())
				{
					temp.c.push_back(x.c[k]);
					temp.n.push_back(x.n[k]);
					k++;
				}
				else
				{
					if(this->n[j]>x.n[k])
					{
						temp.c.push_back(this->c[j]);
						temp.n.push_back(this->n[j]);
						j++;
					}
					else if(this->n[j]==x.n[k])
					{
						temp.c.push_back(this->c[j]+x.c[k]);
						temp.n.push_back(this->n[j]);
						j++;
						k++;
					}
					else
					{
						temp.c.push_back(x.c[j]);
						temp.n.push_back(x.n[j]);
						k++;
					}
				}
			}
			return temp;
		}
		poly minus(poly x)
		{
			poly temp;
			int i,j=0,k=0;
			int max=this->c.size()>x.c.size()?this->c.size():x.c.size();
			for(i=0;i<x.c.size()+this->c.size();i++)
			{
				if(j>=this->c.size()&&k>=x.c.size()) break;
				else if(j<this->c.size()&&k>=x.c.size())
				{
					temp.c.push_back(this->c[j]);
					temp.n.push_back(this->n[j]);
					j++;
				}
				else if(j>=this->c.size()&&k<x.c.size())
				{
					temp.c.push_back(-x.c[k]);
					temp.n.push_back(x.n[k]);
					k++;
				}
				else
				{
					if(this->n[j]>x.n[k])
					{
						temp.c.push_back(this->c[j]);
						temp.n.push_back(this->n[j]);
						j++;
					}
					else if(this->n[j]==x.n[k])
					{
						temp.c.push_back(this->c[j]-x.c[k]);
						temp.n.push_back(this->n[j]);
						j++;
						k++;
					}
					else
					{
						temp.c.push_back(-x.c[j]);
						temp.n.push_back(x.n[j]);
						k++;
					}
				}
			}
			return temp;
		}
		poly mult(poly x)
		{
			int i,j,k;
			poly temp[this->c.size()];
			poly ans;
			for(i=0;i<this->c.size();i++)
			{
				for(j=0;j<x.c.size();j++)
				{
					temp[i].c.push_back(this->c[i]*x.c[j]);
					temp[i].n.push_back(this->n[i]+x.n[j]);
				}
			}
			for(i=0;i<this->c.size();i++)
			{
				ans=ans.add(temp[i]);
			}
			return ans;
		}
		double assign(double x)
		{
			double ans=0;
			for(int i=0;i<c.size();i++)
			{
				ans+=c[i]*pow(x,n[i]);
			}
			return ans;
		}
		poly deri()
		{
			poly temp;
			for(int i=0;i<c.size();i++)
			{
				if(n[i]==0)
				{
					temp.c.push_back(0);
					temp.n.push_back(0);
				}
				else
				{
					temp.c.push_back(n[i]*c[i]);
					temp.n.push_back(n[i]-1);
				}
			}
			return temp;
		}
		void show()
		{
			int flag=0;
			for(int i=0;i<c.size();i++)
			{
				if(n[i]==0)
				{
					if(c[i]==1) cout<<"1";
					else if(c[i]==-1) cout<<"-1";
					else if(c[i]==0)
					{
						flag++;
					}
					else
					{
						cout<<c[i];
					}
				}
				else if(n[i]==1)
				{
					if(c[i]==1) cout<<'x';
					else if(c[i]==-1) cout<<"-x";
					else if(c[i]==0)
					{
						flag++;
					}
					else
					{
						cout<<c[i]<<'x';
					}
				}
				else
				{
					if(c[i]==1) cout<<'x'<<'^'<<n[i];
					else if(c[i]==-1) cout<<"-x"<<'^'<<n[i];
					else if(c[i]==0)
					{
						flag++;
					}
					else
					{
						cout<<c[i]<<"x^"<<n[i];
					}
				}
				if(i==c.size()-1||c[i+1]<=0);
				else cout<<'+';
			}
			if(flag==c.size()) cout<<'0';
			else;
			cout<<endl;
		}
};
poly p[100];
bool check(string x)
{
	for(int i=0;i<count;i++)
	{
		if(x==p[i].name) return false;
		else;
	}
	return true;
}
void initialize()
{
	cout<<"MENU"<<endl;
	cout<<"请输入相应标号以选择功能"<<endl;
	cout<<"1. 输入多项式并保存"<<endl;
	cout<<"2. 多项式相加"<<endl;
	cout<<"3. 多项式相减"<<endl;
	cout<<"4. 多项式与常数的乘法运算"<<endl;
	cout<<"5. 求多项式代入某点的值"<<endl;
	cout<<"6. 显示所有储存多项式"<<endl;
	cout<<"7. 多项式与多项式相乘"<<endl;
	cout<<"8. 判断两个多项式是否相等"<<endl;
	cout<<"9. 对某多项式求导"<<endl;
	cout<<"10. 帮助（查看功能列表）"<<endl;
	cout<<"0. 退出系统"<<endl;
}
void UI()
{
	
	while(1)
	{
		initialize();
		int i;
		cin>>i;
		if(i==1)
		{
			int f=1;
			while(f!=0)
			{
				int j,flag=1;
				cout<<"请按降幂顺序输入一个多项式等式，形如 p=(x,y)(a,b) ，不含空格且p只能为字母"<<endl;
				string str;
				cin>>str;
				for(j=0;j<str.size();j++)
				{
					if((str[j]-'a'>=0&&str[j]-'a'<=26)||(str[j]-'A'>=0&&str[j]-'A'<=26));
					else if(str[j]=='=') break;
					else
					{
						cout<<"非法输入，请重新输入"<<endl;
						system("pause");
						flag=0;
						break;
					}
				}
				if(flag==0) continue;
				else
				{
					string temp=str.substr(j+1,str.size()-j-1);
					string name=str.substr(0,j);
					if(isLegal(temp)&&check(name))
					{
						int x;
						count++;
					//	cout<<count<<endl;
						p[count-1].initial(temp);
						p[count-1].name=name;
						cout<<"创建多项式 "<<name<<" 成功"<<endl;
						cout<<"返回主菜单请输入0，继续输入多项式请输入1"<<endl;
						cin>>x;
						if(x==0) f=0;
						else;
					}
					else
					{
						cout<<"多项式已存在或输入格式错误，请重新输入"<<endl;
					}
				}
			}
		}
		else if(i==2)
		{
			int f=1;
			while(f!=0)
			{
				int j=-1,k=-1;
				cout<<"请输入第一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入第二个多项式，已存在的多项式或新的多项式"<<endl;
				cin>>str;
				poly o;
				if(isLegal(str))
				{
					o.initial(str);
				}
				else
				{
					for(k=0;k<count;k++)
					{
						if(p[k].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				poly temp;
				if(j==-1&&k==-1)
				{
					temp=o.add(q);
				}
				else if(j==-1&&k!=-1)
				{
					temp=q.add(p[k]);
				}
				else if(j!=-1&&k==-1)
				{
					temp=o.add(p[j]);
				}
				else
				{
					temp=p[j].add(p[k]);
				}
				int x;
				cout<<"相加结果为"<<endl; 
				temp.show();
				cout<<"输入1保存结果，输入2继续使用相加功能，输入0返回主菜单"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"请输入需要保存的多项式的名字"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"多项式名字已存在，请重新输入"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"保存成功"<<endl;
					cout<<"输入1继续使用相加功能，输入0返回主菜单"<<endl;
					int u;
					cin>>u;
					if(u==1); 
					else f=0; 
				}
				else if(x==2);
				else f=0;
			}
		}
		else if(i==3)
		{
			int f=1;
			while(f!=0)
			{
				int j=-1,k=-1;
				cout<<"请输入第一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入第二个多项式，已存在的多项式或新的多项式"<<endl;
				cin>>str;
				poly o;
				if(isLegal(str))
				{
					o.initial(str);
				}
				else
				{
					for(k=0;k<count;k++)
					{
						if(p[k].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				poly temp;
				if(j==-1&&k==-1)
				{
					temp=o.minus(q);
				}
				else if(j==-1&&k!=-1)
				{
					temp=q.minus(p[k]);
				}
				else if(j!=-1&&k==-1)
				{
					temp=o.minus(p[j]);
				}
				else
				{
					temp=p[j].minus(p[k]);
				}
				int x;
				cout<<"相减结果为"<<endl; 
				temp.show();
				cout<<"输入1保存结果，输入2继续使用相减功能，输入0返回主菜单"<<endl;
				cin>>x;
				if(x==1)
				{
					cout<<"请输入需要保存的多项式的名字"<<endl;
					cin>>str;
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"保存成功"<<endl;
					cout<<"输入1继续使用相减功能，输入0返回主菜单"<<endl;
					int u;
					cin>>u;
					if(u==1); 
					else f=0; 
				}
				else if(x==2);
				else f=0;
			}
		}
		else if(i==4)
		{
			int f=1;
			while(f!=0)
			{
				int x;
				int j=-1;
				cout<<"请输入一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入一个整数"<<endl;
				cin>>x;
				poly temp;
				if(j==-1)
				{
					temp=q.multx(x);
				}
				else
				{
					temp=p[j].multx(x);
				}
				cout<<"乘法结果为"<<endl; 
				temp.show();
				cout<<"输入1保存结果，输入2继续使用乘法功能，输入0返回主菜单"<<endl;
				cin>>x;
				if(x==1)
				{
					cout<<"请输入需要保存的多项式的名字"<<endl;
					cin>>str;
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"保存成功"<<endl;
					cout<<"输入1继续使用乘法功能，输入0返回主菜单"<<endl;
					int u;
					cin>>u;
					if(u==1); 
					else f=0; 
				}
				else if(x==2);
				else f=0;
			}
		}
		else if(i==5)
		{
			int f=1;
			while(f!=0)
			{
				double x;
				int j=-1;
				cout<<"请输入一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入一个实数"<<endl;
				cin>>x;
				if(isLegal(str))
				{
					cout<<"赋值结果为："<<q.assign(x)<<endl;
				}
				else
				{
					cout<<"赋值结果为："<<p[j].assign(x)<<endl;
				}
				cout<<"输入1继续进行赋值操作，输入0返回主菜单"<<endl;
				int u;
				cin>>u;
				if(u==0) f=0;
				else; 
			}
		}
		else if(i==6)
		{
			cout<<"以下为已保存的多项式"<<endl;
			for(int i=0;i<count;i++)
			{
				cout<<p[i].name<<"=";
				p[i].show();
			}
			system("pause");
		}
		else if(i==7)
		{
			int f=1;
			while(f!=0)
			{
				int j=-1,k=-1;
				cout<<"请输入第一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入第二个多项式，已存在的多项式或新的多项式"<<endl;
				cin>>str;
				poly o;
				if(isLegal(str))
				{
					o.initial(str);
				}
				else
				{
					for(k=0;k<count;k++)
					{
						if(p[k].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				poly temp;
				if(j==-1&&k==-1)
				{
					temp=o.mult(q);
				}
				else if(j==-1&&k!=-1)
				{
					temp=q.mult(p[k]);
				}
				else if(j!=-1&&k==-1)
				{
					temp=o.mult(p[j]);
				}
				else
				{
					temp=p[j].mult(p[k]);
				}
				int x;
				cout<<"相乘结果为"<<endl; 
				temp.show();
				cout<<"输入1保存结果，输入2继续使用相乘功能，输入0返回主菜单"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"请输入需要保存的多项式的名字"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"多项式名字已存在，请重新输入"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"保存成功"<<endl;
					cout<<"输入1继续使用相乘功能，输入0返回主菜单"<<endl;
					int u;
					cin>>u;
					if(u==1); 
					else f=0; 
				}
				else if(x==2);
				else f=0;
			}
		}
		else if(i==8)
		{
			int f=1,flag=0;
			while(f!=0)
			{
				int j=-1,k=-1;
				cout<<"请输入第一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				cout<<"请输入第二个多项式，已存在的多项式或新的多项式"<<endl;
				cin>>str;
				poly o;
				if(isLegal(str))
				{
					o.initial(str);
				}
				else
				{
					for(k=0;k<count;k++)
					{
						if(p[k].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				if(j==-1&&k==-1)
				{
					if(q.isEqual(o)) flag=1;
					else;
				}
				else if(j==-1&&k!=-1)
				{
					if(q.isEqual(p[k])) flag=1;
					else;
				}
				else if(j!=-1&&k==-1)
				{
					if(o.isEqual(p[j])) flag=1;
					else;
				}
				else
				{
					if(p[k].isEqual(p[j])) flag=1;
					else;
				}
				if(flag==1)
				{
					cout<<"两多项式相等"<<endl;
				}
				else
				{
					cout<<"两多项式不相等"<<endl; 
				}
				cout<<"输入1继续比较多项式，输入0返回主菜单"<<endl;
				int u;
				cin>>u; 
				if(u==1);
				else f=0;	
			}
		}
		else if(i==9)
		{
			int f=1;
			while(f!=0)
			{
				double x;
				int j=-1;
				cout<<"请输入一个多项式，已存在的多项式或新的多项式"<<endl;
				string str;
				cin>>str;
				poly q;
				if(isLegal(str))
				{
					q.initial(str);
				}
				else
				{
					for(j=0;j<count;j++)
					{
						if(p[j].name==str) break;
						else;	
					}
					if(j==count)
					{
						cout<<"多项式不存在或者格式错误，请重新输入"<<endl;
						continue;
					}
					else;
				}
				poly temp;
				if(j==-1)
				{
					temp=q.deri();
				}
				else
				{
					temp=p[j].deri();
				}
				cout<<"求导结果为"<<endl;
				temp.show();
				cout<<"输入1保存结果，输入2继续使用求导功能，输入0返回主菜单"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"请输入需要保存的多项式的名字"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"多项式名字已存在，请重新输入"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"保存成功"<<endl;
					cout<<"输入1继续使用求导功能，输入0返回主菜单"<<endl;
					int u;
					cin>>u;
					if(u==1); 
					else f=0; 
				}
				else if(x==2);
				else f=0;
			}
		}
		else if(i==10)
		{
			cout<<"本程序功能如下"<<endl;
			{
				cout<<" 输入多项式并保存"<<endl;
				cout<<" 多项式相加"<<endl;
				cout<<" 多项式相减"<<endl;
				cout<<" 多项式与常数的乘法运算"<<endl;
				cout<<" 求多项式代入某点的值"<<endl;
				cout<<" 显示所有储存多项式"<<endl;
				cout<<" 多项式与多项式相乘"<<endl;
				cout<<" 判断两个多项式是否相等"<<endl;
				cout<<" 对某多项式求导"<<endl;
			}
			system("pause");
		}
		else break;
		system("cls");
	}
}

int main(void)
{
	UI();
}

