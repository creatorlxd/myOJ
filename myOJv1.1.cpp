/*
This program is create by LXD.
To test you Olympic programs with your data for the correct program.
It can help you to see if you program is right!!!
Thank for you use!!!
And except your's joining!!!
v1.1
*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<windows.h>
using namespace std;
struct data_file
{
	string in;
	string out;	
	data_file(string i,string o)
	{
		in=i;
		out=o;
	}
};
vector<data_file> sys_df;
fstream set;
void init()
{
	set.open("set.txt",ios::in);
	int size;
	set>>size;
	for(int i=1;i<=size;i++)
	{
		string in_str,out_str;
		set>>in_str>>out_str;
		data_file b_df(in_str,out_str);
		sys_df.push_back(b_df);
	}
}
int main()
{
	string exe;
	string in_exe;
	string out_exe;
	fstream in,out;
	init(); 
	cout<<"   PPPP     TTTTTTT"<<endl;	
	cout<<"   P  PP       TT  "<<endl;	
	cout<<"   PPPP        TT  "<<endl;	
	cout<<"   P           TT  "<<endl;	
	cout<<"   P           TT        by LXD in CREATORS!     Why not join us now???"<<endl;
	cout<<"v1.1 Can use!!!"<<endl;	
	cout<<"please input your exe's name and it's input/output files' name"<<endl;
	cin>>exe>>in_exe>>out_exe;
	
	bool same=true;
	for(int i=0;i<(int)sys_df.size();i++)
	{
		in.open(in_exe.c_str(),ios::out);
		fstream df_in(sys_df[i].in.c_str(),ios::in);
		fstream df_out(sys_df[i].out.c_str(),ios::in);
		string b_b;
		while(df_in>>b_b)
		{
			in<<b_b<<'\n'; 
		}
		df_in.close();
		in.close();
		system(exe.c_str());
		out.open(out_exe.c_str(),ios::in);
		string out_b;
		b_b.clear();
		while(df_out>>b_b&&out>>out_b)
		{
			if(out_b!=b_b)
				same=false;
			else
				continue;
		}
		out.close();
		df_out.close();
	}
	if(same)
		cout<<"AC"<<endl;
	else
		cout<<"NA"<<endl;
	
	set.close();
	system("pause");
	return 0;
	
}
