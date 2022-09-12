#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct Node
{
	string name;
	Node* thenNode;
	Node* elseNode;
	Node* parentNode;

	Node(string name,Node* thenNode=nullptr, Node* elseNode=nullptr, Node* parentNode=nullptr)
	{
		this->name = name;
		this->thenNode = thenNode;
		this->elseNode = elseNode;
		this->parentNode = parentNode;
	}
}Node;

int main()
{
    fstream input("input.pla");
	vector<Node*> obdd;
	int inputNum=0,outputNum=0, productNum=0;
	while (!input.eof())
	{
		string buf,op;
		getline(input,buf);
		stringstream ss(buf);
		ss >> op;

		if (op == ".i") 
		{
			ss >> inputNum;
		}
		else if (op == ".o")
		{
			ss >> outputNum;
		}
		else if (op == ".lib")
		{
			//init tree
			Node* newNode = new Node("0");
			obdd.push_back(newNode);

			vector<string> nodeName;
			for (int i = 1; i <= inputNum; i++)
			{
				ss >> buf;
				for (int j = 0; j < i; j++)
				{
					nodeName.push_back(buf);
				}
			}
			queue<Node*> q;
			Node* current = nullptr;
			for (auto name :nodeName)
			{
				if (current == nullptr)
				{

				}
			}
			obdd.push_back(newNode);
		}
		else if (op == ".ob")
		{
			for (int i = 0; i < outputNum; i++)
			{
				ss >> buf;
			}
		}
		else if (op == ".p")
		{
			ss >> productNum;
			for (int i = 0; i < productNum; i++)
			{
				input >> buf;
				
			}
		}
		else if (op == ".e")
		{
			break;
		}
		else
		{
			break;
		}
	}
}