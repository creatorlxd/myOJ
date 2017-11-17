#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	int n;
	double time_limit;
	string out_filenme;
	string filename;
	string in_back_name;
	string out_back_name;
	cout<<"please input out filename"<<endl;
	cin>>out_filenme;
	cout<<"please input time limit/n/filename/in&out file backname"<<endl;
	cin>>time_limit>>n>>filename>>in_back_name>>out_back_name;
	fstream out(out_filenme.c_str(),ios::out);
	out<<time_limit<<endl;
	for(int i=0;i<=n;i++)
		out<<filename+to_string(i)+in_back_name<<" "<<filename+to_string(i)+out_back_name<<endl;
	out.close();
	return 0;
}