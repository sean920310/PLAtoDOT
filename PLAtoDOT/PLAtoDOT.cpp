#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef struct
{
	string name;
	int thenNode;
	int elseNode;
} Node;

int main()
{
    fstream input("input.pla");
	vector<Node> obdd,SoP;
	int inputNum,outputNum, productNum;
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
			obdd.push_back({ "0" });
			for (int i = 1; i <= inputNum; i++)
			{
				Node node;
				ss >> node.name;
				for (int j = 0; j < i; j++)
				{
					obdd.push_back(node);
				}
			}
			obdd.push_back({ "1" });
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