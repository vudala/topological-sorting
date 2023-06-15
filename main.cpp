//#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include <bits/stdc++.h>

using namespace std;


map<int, string> toname;
map<string, int> toindex;
vector<vector<int>> graph;

// transforma o grafo em algo mais simples de processar
void init(Agraph_t * g)
{
	Agnode_s * n = NULL;
	Agedge_t *e;
	int index = 0;
	for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
		string uname(agnameof(n));
		if (toindex.find(uname) == toindex.end()) {
			toname[index] = uname;
			toindex[uname] = index;
			graph.push_back(vector<int>(0));

			index++;
		}

		for (e = agfstout(g,n); e; e = agnxtout(g,e)) {
			string vname(agnameof(e->node));
			if (toindex.find(vname) == toindex.end()) {
				toname[index] = vname;
				toindex[vname] = index;
				graph.push_back(vector<int>(0));

				index++;
			}
			graph[toindex[uname]].push_back(toindex[vname]);
		}
	}
}

vector<bool> visited;
stack<int> node_stack;

void toposort_core(int i)
{
	visited[i] = true;
	
	for(int x : graph[i])
		if (!visited[x])
			toposort_core(x);

	node_stack.push(i);
}

void toposort()
{
	visited = vector<bool> (graph.size(), false);

	for(int i = 0; i < graph.size(); i++)
		if (!visited[i])
			toposort_core(i);

	while(!node_stack.empty()) {
		cout << toname[node_stack.top()] << ' ';
		node_stack.pop();
	}
	cout << endl;
}
 

int main()
{
	Agraph_t * g = agread(stdin, NULL);

	graph = vector<vector<int>>(0);

	init(g);

	toposort();

	agclose(g);

  	return 0;
}