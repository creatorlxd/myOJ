#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
using namespace std;
void wait()
{
	for(int i=0;i<100000000;i++)
	{
		//do nothing
	}
}
void kill_shit_space(string str)
{
	for(string::iterator i=str.begin();i!=str.end();i+=1)
	{
		if(*i==' ')
			str.erase(i);
	}
}
struct test_node
{
	bool ok;
	string in;
	string out;
	test_node():ok(false){}
};
vector<test_node> sys;
void load_set(string name)
{
	fstream file;
	string buf;
	string buf2;
	file.open(name.c_str(),ios::in);
	while(file>>buf>>buf2)
	{
		test_node tbuf;
		tbuf.in=buf;
		tbuf.out=buf2;
		sys.push_back(tbuf);
	}
	file.close();
}
void test(string exe)
{
	string exein=exe+".in";
	string exeout=exe+".out";
	for(int i=0;i<(int)sys.size();i++)
	{
		ifstream infile(sys[i].in.c_str());
		string str_in;
		string str_out;
		while(infile>>str_in)
		{
			str_out+=str_in+' ';
			str_in.clear();
		}
		infile.close();
		ofstream outfile(exein.c_str());
		outfile<<str_out;
		str_out.clear();
		outfile.close();
		system(exe.c_str());
//		wait();
		infile.open(sys[i].out.c_str());
		str_in.clear();
		while(infile>>str_in)
		{
			str_out+=str_in;
			str_in.clear();
		}
		string str_cmp;
		str_in.clear();
		infile.close();
		infile.open(exeout.c_str());
		while(infile>>str_in)
		{
			str_cmp+=str_in;
			str_in.clear();
		}
		infile.close();
		kill_shit_space(str_out);
		kill_shit_space(str_cmp);
		if(str_out==str_cmp)
		{
			cout<<"OK"<<endl;
			sys[i].ok=true;
		}	
		else
		{
			cout<<"except:"<<str_out<<" read:"<<str_cmp<<endl;
		}
	}
	for(int i=0;i<(int)sys.size();i++)
	{
		if(sys[i].ok==false)
		{
			cout<<"NA"<<endl;
			return ;
		}
	}
	cout<<"AC"<<endl;
}
int main()
{
	cout<<"input you test node 's file's name"<<endl;
	string str;
	cin>>str;
	load_set(str);
	cout<<"input your exe's name"<<endl;
	cin>>str;
	test(str);
	system("pause");
	return 0;
}
