/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw4
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Oct. 20, 2014
 DESCRIPTION:			use dynamic programming to find the largest sum along a path
 NOTE:					N/A
 FILES:					h4.cpp description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h4 h4.cpp
								 
=======================================================================================================*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
	std::string line;
	std::vector<std::vector<int>> input;
	
	while(std::getline(std::cin, line))
	{
		std::vector<int> temp;
		for(int i=0; i < line.size(); ++i)
			temp.push_back(line[i] - '0');
		input.push_back(temp);
	}	
	// make path and sum size the same as input size
	
	std::vector<std::vector<int>> sum(input.size());
	std::vector<std::vector<char>> path(input.size());
	for(int i = 0; i < input.size(); ++i)
		for(int j = 0; j < input.at(i).size(); ++j)
		{
			sum.at(i).resize(input.at(i).size());
			path.at(i).resize(input.at(i).size());
		}
	// create path and sum
	for(int row = input.size()-1; row >= 0; row--)
		for(int col =0; col < input.at(row).size(); ++col)
		{
			if(row == input.size()-1)
				sum.at(row).at(col) = input.at(row).at(col);
			else
			{
				if( col == 0) // on the left edge
				{
					int b = sum.at(row+1).at(col);
					int c = sum.at(row+1).at(col+1);
					int max = std::max(b,c);
					
					if(max == b) 
					{
						sum.at(row).at(col) = input.at(row).at(col) + b;
						path.at(row).at(col) = '|';
					}
					else // max == c
					{
						sum.at(row).at(col) = input.at(row).at(col) + c;
						path.at(row).at(col) = '\\';
					}
				}
				else if ( col > 0 && col < input.at(row).size()-1) // in the middle
				{
					int a = sum.at(row+1).at(col-1);
					int b = sum.at(row+1).at(col);
					int c = sum.at(row+1).at(col+1);
					int max1 = std::max(a,b);
					int max2 = std::max(max1,c);
					
					if(max2 == a)
					{
						sum.at(row).at(col) = input.at(row).at(col) + a;
						path.at(row).at(col) = '/';
					}
					else if (max2 == b) // max == b
					{
						sum.at(row).at(col) = input.at(row).at(col) + b;
						path.at(row).at(col) = '|';
					}
					else // max == c
					{
						sum.at(row).at(col) = input.at(row).at(col) + c;
						path.at(row).at(col) = '\\';
					}
				}
				else // on the right edge
				{
					int b = sum.at(row+1).at(col);
					int c = sum.at(row+1).at(col-1);
					int max = std::max(b,c);
					
					if(max == b)
					{
						sum.at(row).at(col) = input.at(row).at(col) + b;
						path.at(row).at(col) = '|';
					}
					else // max == c
					{
						sum.at(row).at(col) = input.at(row).at(col) + c;
						path.at(row).at(col) = '/';
					}
				}
			}
		}

	// print output
	auto start = std::distance(begin(sum.at(0)),std::max_element(begin(sum.at(0)), end(sum.at(0))));
	
	for(int i =0; i < input.size(); ++i)
	{
		for(int j = 0; j < input.at(i).size(); ++j)
		{
			if ( j == start)
				std::cout << input.at(i).at(j);				
				if(j == input.at(i).size()-1)
					std::cout << " (" << sum.at(i).at(start) << ")" << std::endl;
			else
			{
				std::cout << '.';
				if(j == input.at(i).size()-1)
					std::cout << " (" << sum.at(i).at(start) << ")" << std::endl;
			}
		}
		if(path.at(i).at(start) == '/')
			start--;
		else if (path.at(i).at(start) == '\\')
			start++;
	}
}