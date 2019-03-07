#include <bits/stdc++.h>
using namespace std;

set <string > terminals,non_terminals;
map <string, set<string> > production;
map <string, set<string> > First;

string rem_space(string s)
{
	int i=0;
	while(i<s.length() && s[i]==' ')
	{
		i++;
	}
	s = s.substr(i);
	i = 0;
	while(i<s.length() && s[s.length()-i-1]==' ')
	{
		i++;
	}
	s = s.substr(0,s.length()-i);
	return s;
}
int take_input()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		string s;
		cin>>s;
		terminals.insert(s);
	}

	string line;
	while(getline(cin,line))
	{
		line = rem_space(line);
		if(line.length()==0)
			continue;
		string left;
		for(int i=0;i<line.length()-1;i++)
		{
			if(line[i]=='-' && line[i+1]=='>')
			{
				left = line.substr(0,i);
				left = rem_space(left);
				line = line.substr(i+2);
				line = rem_space(line);
			}
		}
		non_terminals.insert(left);
		set <string> pr;
		while(line.length()!=0)
		{
			int i=0;
			while(i<line.length() && line[i]!='|')
			{
				i++;
			}
			string s;
			s = line.substr(0,i);
			s = rem_space(s);
			line = line.substr(min(i+1,(int)line.length()));
			line = rem_space(line);
			if(s.length() !=0)
			{
				pr.insert(s);
			}
		}
		if(production.find(left)==production.end())
			production[left]=pr;
		else
		{
			for(auto i:pr)
			{
				production[left].insert(i);
			}
		}
	}
	return 0;
}


int rem_left_rec()
{
	string s ="A";
	for(auto i:production)
	{
		string left = i.first;
		set <string > st1,st2;
		for(auto rt : i.second)
		{
			if(rt[0]==left[0])
			{
				st1.insert(rt);
			}
			else
			{
				st2.insert(rt);
			}
		}
		if(st1.size()==0)
			continue;

		set<string> st3;
		while(non_terminals.find(s)!=non_terminals.end() || terminals.find(s)!=terminals.end())
			s[0]++;
		non_terminals.insert(s);
		for(auto rt:st2)
		{
			st3.insert(rt+s);
		}
		production[i.first] = st3;
		set<string> st;
		for(auto rt:st1)
		{
			st.insert(rt.substr(1,rt.size()-1)+s);
		}
		production[s]=st;
	}
	return 0;
}

int main()
{

	take_input();

	cout<<"terminals :"<<endl;
	for(auto i:terminals)
	{
		cout<<i<<' ';
	}
	cout<<endl;
	cout<<endl;
	cout<<"Non terminals :"<<endl;
	for(auto i:non_terminals)
	{
		cout<<i<<' ';
	}
	cout<<endl;
	cout<<endl;
	cout<<"Original productions :"<<endl;
	for(auto i:production)
	{
		cout<<i.first<<"-> ";
		for(auto j:i.second)
		{
			cout<<j<<' ';
		}
		cout<<endl;
	}

	rem_left_rec();
	cout<<endl;
	cout<<"Right Recursive productions :"<<endl;
	for(auto i:production)
	{
		cout<<i.first<<"-> ";
		for(auto j:i.second)
		{
			cout<<j<<' ';
		}
		cout<<endl;
	}
    return 0;
}
