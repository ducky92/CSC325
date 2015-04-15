/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw5
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Nov. 3, 2014
 DESCRIPTION:			create graph of wrestlers, divide into teams, see if a partition exists
 NOTE:					N/A
 FILES:					h5.cpp description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h5 h5.cpp
=======================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

struct person{
	string team = "nil" ;
	string color = "white";
	int d = 0;
	string p = "nil";
};

int main()
{
	string name1, name2, first;
	unordered_map<string, person> key; // name, struct person
	unordered_map<string, vector<string>> graph;// name, vector of rivals
	vector<string> baby, heels;
	bool isFirst = true;
	bool impossible = false;
	queue<string> q;
	
	while (cin >> name1 >> name2)
	{
		if(isFirst) // nothing in the list	
			first = name1;
		if(graph.find(name1) == graph.end()) // not found in graph
		{
			vector<string> vect; // vector of rivals
			person empty;
			graph.emplace(name1, vect);
			key.emplace(name1, empty);
			isFirst = false;
		}
		if(graph.find(name2) == graph.end()) // not found in graph
		{
			vector<string> vect; // vector of rivals
			person empty;
			graph.emplace(name2, vect);
			key.emplace(name2, empty);
			isFirst = false;
		}
		graph.at(name1).push_back(name2);
		graph.at(name2).push_back(name1);
	}
	q.push(first);
	key.at(first).team = "BABYFACES";
	baby.push_back(first);
	while(!q.empty())
	{
		string parent = q.front();
		q.pop();
		for(int i =0; i < graph.at(parent).size(); ++i)
		{
			if(key.at(graph.at(parent).at(i)).color == "white")
			{
				key.at(graph.at(parent).at(i)).color = "grey";
				key.at(graph.at(parent).at(i)).d = key.at(parent).d + 1;
				if(key.at(graph.at(parent).at(i)).d % 2 ==0)
				{
					key.at(graph.at(parent).at(i)).team = "BABYFACES";
					baby.push_back(graph.at(parent).at(i));
				}
				else
				{
					key.at(graph.at(parent).at(i)).team = "HEELS";
					heels.push_back(graph.at(parent).at(i));
				}
				key.at(graph.at(parent).at(i)).p = parent;
				q.push(graph.at(parent).at(i));
			}
		}
		key.at(parent).color = "black";
	}
	for(auto x:graph)
		for(int i =0; i < x.second.size(); ++i)
			if(key.at(x.first).team == key.at(x.second.at(i)).team) // rivals are on the same team
				impossible = true;
	if (!impossible)
	{
		sort(baby.begin(), baby.end());
		sort(heels.begin(), heels.end());
		
		cout << "BABYFACES" << endl;
		for(int i =0; i < baby.size(); ++i)
			cout << baby.at(i) << endl;
			
		cout << "HEELS" << endl;
		for(auto x: heels)
			cout << x << endl;
	}
	else
		cout << "IMPOSSIBLE" << endl;
	return 0;
}