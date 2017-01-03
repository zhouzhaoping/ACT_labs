#include "Graph.h"
#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

Graph::Graph(int _vex_num) {
	vex_num = _vex_num;
	adjacents = new list<int>[vex_num];
}

Graph::~Graph() {
	delete[]adjacents;
}

void Graph::addEdge(int u, int v) {
	adjacents[u].push_back(v);
}

void Graph::fillOrder(int v, bool *visited, stack<int> &m_stack) {
	visited[v] = true;
	list<int>::iterator iter;
	for (iter = adjacents[v].begin(); iter != adjacents[v].end(); iter++) {
		if (false == visited[*iter])
			fillOrder(*iter, visited, m_stack);
	}
	m_stack.push(v);
}

void Graph::dfsUtil(int v, bool *visited) {
	visited[v] = true;
	result.rbegin()->push_back(v);
	//cout << v << " ";
	list<int>::iterator iter;
	for (iter = adjacents[v].begin(); iter != adjacents[v].end(); iter++) {
		if (false == visited[*iter])
			dfsUtil(*iter, visited);
	}
}

Graph Graph::transpose() {
	int v;
	Graph gt(vex_num);
	for (v = 0; v < vex_num; v++) {
		list<int>::iterator iter;
		for (iter = adjacents[v].begin(); iter != adjacents[v].end(); iter++) {
			gt.adjacents[*iter].push_back(v);
		}
	}
	return gt;
}

void Graph::getStrongConnected() {
	result.clear();
	stack<int> m_stack;
	bool *visited = new bool[vex_num];
	int v;
	for (v = 0; v < vex_num; v++)
		visited[v] = false;
	for (v = 0; v < vex_num; v++)
		if (false == visited[v])
			fillOrder(v, visited, m_stack);
	for (v = 0; v < vex_num; v++)
		visited[v] = false;
	Graph gt = Graph(vex_num);
	for (v = 0; v < vex_num; v++) {
		list<int>::iterator iter;
		for (iter = adjacents[v].begin(); iter != adjacents[v].end(); iter++) {
			gt.adjacents[*iter].push_back(v);
		}
	}
	while (!m_stack.empty()) {
		int u = m_stack.top();
		m_stack.pop();
		if (false == visited[u]) {
			result.push_back(vector<int>());
 			gt.dfsUtil(u, visited);
			//cout << endl;
		}
	}
	delete[]visited;
}