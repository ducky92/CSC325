/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw2
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Sept. 18, 2014
 DESCRIPTION:			Create user id's according to when they were entered, implement counting sort
 NOTE:					N/A
 FILES:					h2.cpp description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h2 h2.cpp
								 h2 < 7_in.txt > 7_out.txt
=======================================================================================================*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <locale>
#include <iomanip>

std::vector<std::string> countingSort(std::vector<std::string>& A, std::vector<std::string>& B, int k) //pg 195
{
	std::vector<int> C(k, 0); // ( size, initial value)
	std::vector<std::string> initials(A.size());
	
	int key;
	char x,y;
	
	for(unsigned j = 0; j < A.size(); ++j) // counts all the numbers
	{
		x = A.at(j).at(0); // x = first initial of the name
		
		for(unsigned l =0; l < A[j].size(); ++l) // look for the last uppercase letter
			if(isupper(A[j][l]))
				y = A[j][l]; // store it in y
		key = 26*(x - 'A') + (y - 'A');
		C[key]++; // C[i] now contains the number of elements equal to i
	}
	for(unsigned i = 1; i <= k; ++i) // forms a running total
		C[i] += C[i-1];
	for(int j = A.size()-1; j >= 0; j--)
	{
		std::string temp;
		
		x = A[j][0];
		for(unsigned l =0; l < A[j].size(); ++l) // look for the last uppercase letter
			if(isupper(A[j][l]))
				y = A[j][l]; // store it in y
				
		temp = x; 
		temp += y;
		int key = 26*(x-'A') + (y - 'A');
		
		initials.at(C[key]-1) = temp; // sort initials the same as names
		B.at(C[key]-1) = A[j];
		C[key] = C[key] - 1;
	}
	return initials;
}
int main()
{
	std::string line;
	std::vector<std::string> names;
	std::vector<std::string> sortedNames;
	
	while(std::getline(std::cin,line)) // put the new line in a vector
		names.push_back(line); // add names to vector
	
	sortedNames.resize(names.size());
	auto initials = countingSort(names, sortedNames, 676);
	
	int prev = 0;
	int ctr = 1;
	for(unsigned i = 0; i < initials.size(); ++i)
	{
		if(i >= 1 && initials.at(i).at(0) == initials.at(i-1).at(0) && initials.at(i).at(1) == initials.at(i-1).at(1))
			ctr++;
		else
			ctr =1;
		std::cout << initials.at(i) << std::setw(6) << std::setfill('0') << ctr << ' ' << sortedNames.at(i) << std::endl;
	}
	
}