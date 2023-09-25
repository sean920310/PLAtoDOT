#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

typedef struct Node
{
	string name;
	int layer;
	int thenNode;
	int elseNode;

	Node() {
		name = "";
		layer = 0;
		thenNode = 0;
		elseNode = 0;
	}
	Node(string _name, int _thenNode = 0, int _elseNode = 0, int _layer = 0) {
		name = _name;
		layer = _layer;
		thenNode = _thenNode;
		elseNode = _elseNode;
	}
	Node(const Node& node) {
		name = node.name;
		layer = node.layer;
		thenNode = node.thenNode;
		elseNode = node.elseNode;
	}
	bool operator==(const Node& rhs) {
		return name == rhs.name && name != "" && thenNode == rhs.thenNode && elseNode == rhs.elseNode;
	}
}Node;

void productInit(vector<Node>&, int, string, int);

int main(int argc, char* argv[])
{
	
	if (argc < 3){
		cout << "arg error";
		return 0;
	}
	char* inputFileName = argv[1];
	char* outputFileName = argv[2];

	fstream input(inputFileName);
	vector<Node> obdd;
	int inputNum = 0, outputNum = 0, productNum = 0;
	//read file and trasfer to obdd
	while (!input.eof())
	{
		string buf, op;
		getline(input, buf);
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
		else if (op == ".ilb")
		{
			//init tree
			obdd.push_back({ "0" });

			vector<string> nodeName;
			for (int i = 0; i < inputNum; i++)
			{
				ss >> buf;
				for (int j = 0; j < pow(2, i); j++)
				{
					nodeName.push_back(buf);
				}
			}
			queue<int> q;
			int layer = 0;
			string lastName = "";
			for (int i = 1; i <= nodeName.size(); i++)
			{
				Node newNode;
				newNode.name = nodeName[i - 1];
				if (lastName != newNode.name && lastName!="")
					layer++;
				newNode.layer = layer;
				obdd.push_back(newNode);
				if (!q.empty())
				{
					if (obdd[q.front()].elseNode == 0) {
						obdd[q.front()].elseNode = i;
					}
					else if (obdd[q.front()].thenNode == 0) {
						obdd[q.front()].thenNode = i;
						q.pop();
					}
				}
				q.push(i);
				lastName = newNode.name;
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
				int result;
				input >> result;
				productInit(obdd, 1, buf, result);
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

	//transfer to robdd
	bool needSimplify = true;
	while (needSimplify)
	{
		needSimplify = false;
		for (int i = 1; i < obdd.size() - 1; i++) {
			//two edge point to same
			if (obdd[i].thenNode == obdd[i].elseNode && obdd[i].name != "") {
				obdd[i].name = "";
				for (int j = 1; j < obdd.size() - 1; j++)
				{
					if (obdd[j].thenNode == i)
					{
						obdd[j].thenNode = obdd[i].thenNode;
					}
					else if (obdd[j].elseNode == i)
					{
						obdd[j].elseNode = obdd[i].thenNode;
					}
				}
				needSimplify = true;
			}

			//mutiple same node
			for (int j = i + 1; j < obdd.size() - 1; j++)
			{
				if (obdd[i] == obdd[j])
				{
					for (int m = 1; m < obdd.size() - 1; m++)
					{
						if (obdd[m].thenNode == j) {
							obdd[m].thenNode = i;
						}
						else if (obdd[m].elseNode == j)
						{
							obdd[m].elseNode = i;
						}
					}
					obdd[j].name = "";
					needSimplify = true;
				}
			}

		}


	}

	//output
	ofstream output(outputFileName, ios::out);
	output << "digraph ROBDD {\n";

	int layer = 0;
	for (int i = 1; i < obdd.size() - 1; i++) {
		if (layer == obdd[i].layer)
		{
			if (layer != 0)
				output << "}\n";
			output << "{rank=same";
			layer++;
		}
		if (obdd[i].name != "") {
			output << " " << i;
		}
	}
	output << "}\n";
	for (int i = 0; i < obdd.size(); i++) {
		if (obdd[i].name != "") {
			if(i == 0 || i == obdd.size()-1)
				output << i <<" [label=" << obdd[i].name<<", shape=box]\n";
			else
			{
				output << i << " [label=\"" << obdd[i].name << "\"]\n";
			}
		}
	}
	for (int i = 1; i < obdd.size()-1; i++) {
		if (obdd[i].name != "") {
			output << i << " -> " << obdd[i].elseNode<<" [label=\"0\", style=dotted]\n";
			output << i << " -> " << obdd[i].thenNode << " [label=\"1\", style=solid]\n";
		}
	}
	output << "}";
	output.close();
	input.close();


	/*for (auto node : obdd) {
		cout << node.name << " " <<node.layer << " " << node.elseNode << " " << node.thenNode << endl;
	}*/
}

void productInit(vector<Node>& tree, int nodeIndex, string input, int result) {
	if (input.length() > 1) {
		if (input[0] == '1') {
			productInit(tree, tree[nodeIndex].thenNode, input.substr(1), result);
		}
		else if (input[0] == '0')
		{
			productInit(tree, tree[nodeIndex].elseNode, input.substr(1), result);
		}
		else if (input[0] == '-')
		{
			productInit(tree, tree[nodeIndex].thenNode, input.substr(1), result);
			productInit(tree, tree[nodeIndex].elseNode, input.substr(1), result);
		}
	}
	else
	{
		if (input[0] == '1') {
			if (result)
				tree[nodeIndex].thenNode = tree.size() - 1;
			else
				tree[nodeIndex].thenNode = 0;
		}
		else if (input[0] == '0')
		{
			if (result)
				tree[nodeIndex].elseNode = tree.size() - 1;
			else
				tree[nodeIndex].elseNode = 0;
		}
		else if (input[0] == '-')
		{
			if (result)
			{
				tree[nodeIndex].elseNode = tree.size() - 1;
				tree[nodeIndex].thenNode = tree.size() - 1;
			}
			else
			{
				tree[nodeIndex].elseNode = 0;
				tree[nodeIndex].thenNode = 0;
			}
		}
	}
}