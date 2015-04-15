/*=======================================================================================================
 COURSE:				CSC 325, Assignment hw3
 PROGRAMMER:			Zachary Metcalf, Metcalf847
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Oct. 10 2014
 DESCRIPTION:			uses the next_permutation to prove height of randomly inserted BST is O(n lg n)
 NOTE:					N/A
 FILES:					h3.cpp, description.txt
 IDE/COMPILER:			Win 8.1 Command prompt && gcc 4.8.10
						command: g++ -std=c++11 -o h3 h3.cpp
								 h3
=======================================================================================================*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include "math.h"
#include <stdlib.h>
#include <vector>

unsigned const N = 10;

struct Node
{float  key;
 Node  *parent, *leftChild, *rightChild;
};

class BST 
{
	private:
		Node *root;

		void pop (Node *val)
		{
			if(val->leftChild)
				pop(val->leftChild);
			if(val->rightChild)
				pop(val->rightChild);
			delete val;
		}
		void push(float data, Node *val)
		{
			Node *temp = new Node();
			if(val == nullptr) // if nothing is passed in
			{
				Node *temp = new Node;
				temp->parent = nullptr;
				temp->leftChild = nullptr;
				temp->rightChild = nullptr;
				temp->key = data;
				root = temp;
			}
			else
			{
				if (data <= val->key) // if what is passed in is less than what is already there 
				{
					if (val->leftChild == nullptr) // create a left child
					{
						Node *temp = new Node;
						temp->parent = val;
						temp->leftChild = nullptr;
						temp->rightChild = nullptr;
						temp->key = data;
						val->leftChild = temp;
					}
					else
					{
						push(data, val->leftChild); // keep going through until there is no more left children
					}
				}
				else // if what is passed in is greater than what is already there 
				{
					if (val->rightChild == nullptr) // create a right child
					{
						Node *temp = new Node;
						temp->parent = val;
						temp->leftChild = nullptr;
						temp->rightChild = nullptr;
						temp->key = data;
						val->rightChild = temp;
					}
					else
					{
						push(data, val->rightChild); // keep going through until there is no more right children
					}
				}
			}
		}

		int height(Node *val)
		{
			
			if(val == nullptr)
				return -1;
			else
			{
				return 1 + std::max(height(val->leftChild), height(val->rightChild));
			}
		}
		float getFactorial(int num)
		{
			float fact = 1;
			
			if(num == 0)
				return 1;
			else
			{
				for(int i = 1; i<= num; ++i)
					fact *= i;
				return fact;
			}
		}
	public:
		BST()
		{
			root = nullptr;
		}
		void create()
		{
			std::vector<int> vect;
			vect.resize(N);
			std::vector<int> inTree;
			

			for(unsigned i =0; i < N; ++i)
				vect.at(i) = i;
			for (unsigned i =0; i < vect.size(); ++i)
			{
				inTree.push_back(vect.at(i));
				
				int sum = 0;
				do 	{
						for(unsigned j =0; j < inTree.size(); ++j)
							push(inTree.at(j),root);
						sum += height(root);
						pop(root);
						root = nullptr;
					}
				while (std::next_permutation(inTree.begin(), inTree.end()));
				
				std::cout << std::setfill('0') << std::setiosflags(std::ios::fixed) << std::setprecision(0) << std::setw(2) << i+1 << ' ' ;
				std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(5) <<  log2(i+1) << ' ' ;
				std::cout << std::setw(6) << sum/getFactorial(i+1) << std::endl;
			}
		}
};

int main()
{
	BST aBST;
	aBST.create();
}