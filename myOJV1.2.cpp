#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void ThrowError(const string& str)
{
	cout<<str<<endl;
	abort();
}

using namespace std::chrono;

int GetClock()
{
	return clock()/CLOCKS_PER_SEC;
}

double GetDeltaTime()
{
	static steady_clock::time_point TimeNow=steady_clock::now();
	static steady_clock::time_point TimeBuffer;
	static duration<double> time_span;
	TimeBuffer = steady_clock::now();
	time_span = duration_cast<duration<double>>(TimeBuffer - TimeNow);
	TimeNow = steady_clock::now();
	return time_span.count();
}

struct TimeTest
{
	steady_clock::time_point m_BeginTime;
	steady_clock::time_point m_EndTime;
	bool m_IfEnd=false;
	double m_Content=0.00f;

	void Begin()
	{
		m_BeginTime=steady_clock::now();
	}
	void End()
	{
		m_EndTime=steady_clock::now();
		duration<double> time_span=duration_cast<duration<double>>(m_EndTime-m_BeginTime);
		m_Content=time_span.count();
		m_IfEnd=true;
	}
	double GetContent()
	{
		if(!m_IfEnd)
		{
			ThrowError("this timetest has not end yet");
		}
		else
		{
			return m_Content;
		}
	}
};
void kill_shit_space(string str)
{
	string buffer;
	for(string::iterator i=str.begin();i!=str.end();i+=1)
	{
		if(*i!=' ')
			buffer+=*i;
	}
	str=buffer;
}
struct test_node
{
	bool ok;
	string in;
	string out;
	double t_limit;
	test_node():ok(false),t_limit(0){}
};
vector<test_node> sys;
void load_set(string name)
{
	fstream file;
	string buf;
	string buf2;
	file.open(name.c_str(),ios::in);
	double tl=0;
	file>>tl;
	while(file>>buf>>buf2)
	{
		test_node tbuf;
		tbuf.t_limit=tl;
		tbuf.in=buf;
		tbuf.out=buf2;
		sys.push_back(tbuf);
	}
	file.close();
}
void test(string exe)
{
	string exein=exe+".in_file";
	string exeout=exe+".out_file";
	for(int i=0;i<(int)sys.size();i++)
	{
		cout<<i<<": ";
		double time_limit=sys[i].t_limit;
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
		TimeTest tt;
		tt.Begin();
		system(exe.c_str());
		tt.End();
		if(tt.GetContent()>time_limit)
		{
			cout<<"TLE"<<endl;
			continue;
		}
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
			cout<<"WA!!! except:"<<str_out<<" read:"<<str_cmp<<endl;
		}
	}
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
