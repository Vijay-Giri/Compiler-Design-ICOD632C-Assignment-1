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
string input;
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
	cin>>input;
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

set <string> firstA(string left)
{
	set <string> st;
	if(terminals.find(left)!=terminals.end())
	{
		st.insert(left);
		return st;
	}
	for(auto pr:production[left])
	{
		if(pr.substr(0,1)==left)
			continue;
		set <string> tmp = firstA(pr.substr(0,1));
		for(auto i:tmp)
		{
			st.insert(i);
		}
	}
	First[left] = st;
	return st;
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
		st.insert("#");
		production[s]=st;
	}
	return 0;
}

int peek=0;
int scan(string nt)
{
	if(terminals.find(nt)!=terminals.end())
	{
		peek++;
		return 1;
	}
	int tp = peek;
	for(auto rt : production[nt])
	{
		int res=1;
		if(terminals.find(rt.substr(0,1)) != terminals.end() && input[peek]==rt[0])
		{
			peek++;
			for(int i=1;i<rt.length();i++)
			{
				res = scan(rt.substr(i,1));
				if(res==0)
				{
					break;
				}
			}
			if(res==0)
			{
				peek=tp;
				continue;
			}
			else
			{
				return 1;
			}
		}
		else if(First[rt.substr(0,1)].find(input.substr(peek,1)) != First[rt.substr(0,1)].end())
		{
			for(int i=0;i<rt.length();i++)
			{
				res = scan(rt.substr(i,1));
				if(res==0)
					break;
			}
			if(res==0)
			{
				peek=tp;
				continue;
			}
			else
			{
				return 1;
			}
		}
	}
	if(production[nt].find("#")!=production[nt].end())
	{
		peek = tp;
		return 1;
	}
	return 0;
}

int main()
{
	take_input();
	rem_left_rec();

	cout<<"Right recursive productions :"<<endl;
	for(auto i:production)
	{
		cout<<i.first<<"-> ";
		for(auto j:i.second)
		{
			cout<<j<<' ';
		}
		cout<<endl;
	}
	for(auto nt : non_terminals)
	{
		firstA(nt);
	}
	
	cout<<endl;
	cout<<"First :"<<endl;
	for(auto i:First)
	{
		if(i.first[0]=='#') continue;
		cout<<i.first<<"-> ";
		for(auto j:i.second)
		{
			cout<<j<<' ';
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"Input: "<<input<<endl;
	if(scan("S")==1 && peek ==input.length())
	{
		cout<<"Yes "<<endl;
	}
	else
	 cout<<"No "<<endl;

    return 0;
}
