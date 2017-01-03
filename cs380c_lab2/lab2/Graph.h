#pragma once
#include <list>
#include <stack>
#include <vector>
using namespace std;

class Graph {
private:
	int vex_num;
	list<int> *adjacents;
	void fillOrder(int v, bool *visited, stack<int> &m_stack);
	void dfsUtil(int v, bool *visited);
public:
	Graph(int _vex_num);
	~Graph();
	void addEdge(int u, int v);
	void getStrongConnected();
	Graph transpose();
	static vector<vector<int> > result;
};

//vector<vector<int> > result = vector<vector<int> >();