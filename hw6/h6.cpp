/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw6
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Nov. 17, 2014
 DESCRIPTION:			create graph of wrestlers, divide into teams, see if a partition exists
 NOTE:					N/A
 FILES:					h6.cpp description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h6 h6.cpp
=======================================================================================================*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

struct node{
	string color = "white";
	int start = 0;
	int finish = 0;
	string p = "nil";
};

unordered_map<string, node> key, key_T; // name, struct node
int time = 0;
vector<string> vect, vect_T;
vector<vector<string>> output;
bool first = true;

void DFSVisit(unordered_map<string, vector<string>> G, string u)
{
	time++;
	key.at(u).start = time;
	key.at(u).color = "grey";
	for(auto v: G.at(u))
		if(key.at(v).color == "white")
		{
			key.at(v).p = u;
			DFSVisit(G, v);
		}
	key.at(u).color = "black";
	vect.push_back(u);
	time++;
	key.at(u).finish = time;
	
}
void DFSVisit_T(unordered_map<string, vector<string>> G, string u)
{
	time++;
	key_T.at(u).start = time;
	key_T.at(u).color = "grey";
	
	for(auto v: G.at(u))
		if(key_T.at(v).color == "white")
		{
			key_T.at(v).p = u;
			DFSVisit_T(G, v);
		}
	key_T.at(u).color = "black";
	vect_T.push_back(u);
	time++;
	key_T.at(u).finish = time;
}

int main()
{
	string name1, name2, first;
	
	unordered_map<string, vector<string>> graph, transpose;// name, vector of edges
	
	while(cin >> name1 >> name2)
	{
		vector<string> vect; // vector of edges
		node empty;
		if(graph.find(name1) == graph.end()) // not found in graph
		{
			graph.emplace(name1, vect);
			key.emplace(name1, empty);
		}
		if(graph.find(name2) == graph.end()) // not found in graph
		{
			graph.emplace(name2, vect);
			key.emplace(name2, empty);
		}
		graph.at(name1).push_back(name2);
		if(transpose.find(name1) == transpose.end()) // not found in graph
		{
			transpose.emplace(name1, vect);
			key_T.emplace(name1, empty);
		}
		if(transpose.find(name2) == transpose.end()) // not found in graph
		{
			transpose.emplace(name2, vect);
			key_T.emplace(name2, empty);
		}
		transpose.at(name2).push_back(name1);
	}
	
	/////////////////// DFS ///////////////////
	for(auto x: graph)
		for(int i =0; i < x.second.size();++i)
			if(key.at(x.second.at(i)).color == "white")
				DFSVisit(graph, x.first);
	
	reverse(vect.begin(), vect.end());
	time = 0;
	for(int i =0; i < vect.size(); ++i)
		if(key_T.at(vect.at(i)).color == "white")
			DFSVisit_T(transpose, vect.at(i));

	vector<string> temp1, temp2;
	vector<vector<string>> output;
	for(int i =0; i < vect_T.size(); ++i)
	{
		if(key_T.at(vect_T.at(i)).p != "nil")
			temp1.push_back(vect_T.at(i));
		else
		{
			temp2.push_back(vect_T.at(i));
			temp2.insert(temp2.end(), temp1.begin(), temp1.end());
			output.push_back(temp2);
			temp1.clear();
			temp2.clear();
		}
	}
	sort(output.begin(), output.end());
	for(int i =0; i < output.size(); ++i)
	{
		sort(output.at(i).begin(), output.at(i).end());
		cout << output.at(i).at(0);
		for(int j =1; j < output.at(i).size(); ++j)
			cout << ' ' << output.at(i).at(j);
		cout << endl;
	}
	return 0;
}
	