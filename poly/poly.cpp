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
	cout<<"��������Ӧ�����ѡ����"<<endl;
	cout<<"1. �������ʽ������"<<endl;
	cout<<"2. ����ʽ���"<<endl;
	cout<<"3. ����ʽ���"<<endl;
	cout<<"4. ����ʽ�볣���ĳ˷�����"<<endl;
	cout<<"5. �����ʽ����ĳ���ֵ"<<endl;
	cout<<"6. ��ʾ���д������ʽ"<<endl;
	cout<<"7. ����ʽ�����ʽ���"<<endl;
	cout<<"8. �ж���������ʽ�Ƿ����"<<endl;
	cout<<"9. ��ĳ����ʽ��"<<endl;
	cout<<"10. �������鿴�����б�"<<endl;
	cout<<"0. �˳�ϵͳ"<<endl;
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
				cout<<"�밴����˳������һ������ʽ��ʽ������ p=(x,y)(a,b) �������ո���pֻ��Ϊ��ĸ"<<endl;
				string str;
				cin>>str;
				for(j=0;j<str.size();j++)
				{
					if((str[j]-'a'>=0&&str[j]-'a'<=26)||(str[j]-'A'>=0&&str[j]-'A'<=26));
					else if(str[j]=='=') break;
					else
					{
						cout<<"�Ƿ����룬����������"<<endl;
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
						cout<<"��������ʽ "<<name<<" �ɹ�"<<endl;
						cout<<"�������˵�������0�������������ʽ������1"<<endl;
						cin>>x;
						if(x==0) f=0;
						else;
					}
					else
					{
						cout<<"����ʽ�Ѵ��ڻ������ʽ��������������"<<endl;
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
				cout<<"�������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������ڶ�������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
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
				cout<<"��ӽ��Ϊ"<<endl; 
				temp.show();
				cout<<"����1������������2����ʹ����ӹ��ܣ�����0�������˵�"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"��������Ҫ����Ķ���ʽ������"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"����ʽ�����Ѵ��ڣ�����������"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"����ɹ�"<<endl;
					cout<<"����1����ʹ����ӹ��ܣ�����0�������˵�"<<endl;
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
				cout<<"�������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������ڶ�������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
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
				cout<<"������Ϊ"<<endl; 
				temp.show();
				cout<<"����1������������2����ʹ��������ܣ�����0�������˵�"<<endl;
				cin>>x;
				if(x==1)
				{
					cout<<"��������Ҫ����Ķ���ʽ������"<<endl;
					cin>>str;
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"����ɹ�"<<endl;
					cout<<"����1����ʹ��������ܣ�����0�������˵�"<<endl;
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
				cout<<"������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������һ������"<<endl;
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
				cout<<"�˷����Ϊ"<<endl; 
				temp.show();
				cout<<"����1������������2����ʹ�ó˷����ܣ�����0�������˵�"<<endl;
				cin>>x;
				if(x==1)
				{
					cout<<"��������Ҫ����Ķ���ʽ������"<<endl;
					cin>>str;
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"����ɹ�"<<endl;
					cout<<"����1����ʹ�ó˷����ܣ�����0�������˵�"<<endl;
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
				cout<<"������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������һ��ʵ��"<<endl;
				cin>>x;
				if(isLegal(str))
				{
					cout<<"��ֵ���Ϊ��"<<q.assign(x)<<endl;
				}
				else
				{
					cout<<"��ֵ���Ϊ��"<<p[j].assign(x)<<endl;
				}
				cout<<"����1�������и�ֵ����������0�������˵�"<<endl;
				int u;
				cin>>u;
				if(u==0) f=0;
				else; 
			}
		}
		else if(i==6)
		{
			cout<<"����Ϊ�ѱ���Ķ���ʽ"<<endl;
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
				cout<<"�������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������ڶ�������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
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
				cout<<"��˽��Ϊ"<<endl; 
				temp.show();
				cout<<"����1������������2����ʹ����˹��ܣ�����0�������˵�"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"��������Ҫ����Ķ���ʽ������"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"����ʽ�����Ѵ��ڣ�����������"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"����ɹ�"<<endl;
					cout<<"����1����ʹ����˹��ܣ�����0�������˵�"<<endl;
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
				cout<<"�������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
						continue;
					}
					else;
				}
				cout<<"������ڶ�������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
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
					cout<<"������ʽ���"<<endl;
				}
				else
				{
					cout<<"������ʽ�����"<<endl; 
				}
				cout<<"����1�����Ƚ϶���ʽ������0�������˵�"<<endl;
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
				cout<<"������һ������ʽ���Ѵ��ڵĶ���ʽ���µĶ���ʽ"<<endl;
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
						cout<<"����ʽ�����ڻ��߸�ʽ��������������"<<endl;
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
				cout<<"�󵼽��Ϊ"<<endl;
				temp.show();
				cout<<"����1������������2����ʹ���󵼹��ܣ�����0�������˵�"<<endl;
				cin>>x;
				if(x==1)
				{
					while(1)
					{
						cout<<"��������Ҫ����Ķ���ʽ������"<<endl;
						cin>>str;
						if(check(str)) break;
						else
						{
							cout<<"����ʽ�����Ѵ��ڣ�����������"<<endl;
						}
					} 
					count++;
				//	cout<<count<<endl;
					p[count-1]=temp;
					p[count-1].name=str;
					cout<<"����ɹ�"<<endl;
					cout<<"����1����ʹ���󵼹��ܣ�����0�������˵�"<<endl;
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
			cout<<"������������"<<endl;
			{
				cout<<" �������ʽ������"<<endl;
				cout<<" ����ʽ���"<<endl;
				cout<<" ����ʽ���"<<endl;
				cout<<" ����ʽ�볣���ĳ˷�����"<<endl;
				cout<<" �����ʽ����ĳ���ֵ"<<endl;
				cout<<" ��ʾ���д������ʽ"<<endl;
				cout<<" ����ʽ�����ʽ���"<<endl;
				cout<<" �ж���������ʽ�Ƿ����"<<endl;
				cout<<" ��ĳ����ʽ��"<<endl;
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

