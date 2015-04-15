/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw7
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Dec 1, 2014
 DESCRIPTION:			
 NOTE:					N/A
 FILES:					h7.cpp description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h7 h7.cpp
=======================================================================================================*/

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cctype>
#include <algorithm>

using namespace std;

const int NUM_BITS = 26;

int main()
{
	vector<string> input, output;
	vector<bitset<NUM_BITS>> sets;
	bitset<NUM_BITS> allLetters;
	string word;
	
	while(cin >> word)
	{
		input.push_back(word);
	}
	sort(input.begin(), input.end());
	for(int i =0; i < input.size(); ++i)
	{
		int b = 0;
		bitset<NUM_BITS> word;
		for(int j =0; j < input.at(i).size(); ++j)
		{
			b = input.at(i).at(j) - 'a';
			word.set(b,1);
			allLetters.set(b,1);
		}
		sets.push_back(word);
	}
	while(allLetters.count() != 0 )
	{
		bitset<NUM_BITS> maxBit, check;
		string maxWord;
		int count = 0;
		int index = 0;
		
		for(int i =0; i < input.size(); ++i) // finds the next word
		{
			check = allLetters;
			bitset<NUM_BITS> temp;
			temp = allLetters & sets.at(i);
			if(temp.count() > count)
			{
				count = temp.count();
				maxBit = sets.at(i);
				maxWord = input.at(i);
				index = i;
			}
			if(temp.count() == count && maxWord.size() > input.at(i).size()) // smallest word length
			{
				maxBit = sets.at(i);
				maxWord = input.at(i);
				index = i;
			}
		}
		
		allLetters &= ~maxBit;
		output.push_back(maxWord);
	}
	
	for(auto x: output)
		cout << x << endl;
	
	return 0;
}
