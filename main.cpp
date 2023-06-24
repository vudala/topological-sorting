//#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include <bits/stdc++.h>

using namespace std;

map<int, string> toname;
map<string, int> toindex;
vector<vector<int>> graph;
vector<int> graph_t;

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

int t;

void toposort_core(int i)
{
	visited[i] = true;
	t++; // adding for pre
	for(int x : graph[i])
		if (!visited[x])
			toposort_core(x);
	
	// saving pos
	graph_t[i] = (++t);
	node_stack.push(i);
}

void toposort()
{
	visited = vector<bool> (graph.size(), false);

	t = 0;

	for(long unsigned int i = 0; i < graph.size(); i++)
		if (!visited[i])
			toposort_core(i);
}

void findCycle() {
	for(long unsigned int i = 0; i < graph.size(); i++){
		int u = i;

		for(int v : graph[i]){
			// (u, v), u.pos < v.pos = return arc -> has cycle -> not a DAG
			if(graph_t[u] < graph_t[v]){
				cerr << "err: cycle found: " << toname[u] << " -> " << toname[v] << endl;
				cerr << "err: not a DAG" << endl;
				exit(1);
			}
		}
	}
}

void printTopoSort()
{
	while(!node_stack.empty()) {
		cout << toname[node_stack.top()] << ' ';
		node_stack.pop();
	}
}

void checkInput(Agraph_t * g) {
	if(!g){
		cerr << "err: error reading graph. Invalid structure." << endl;
		exit(1);
	}

	if(!agisdirected(g)) {
		cerr << "err: not a digraph" << endl;
		exit(1);
	}
}

int main()
{	
	
	Agraph_t * g = agread(stdin, NULL);

	checkInput(g);

	graph = vector<vector<int>>(0);

	init(g);
	graph_t = vector<int>(graph.size());

	toposort();

	findCycle();

	printTopoSort();

	agclose(g);

	return 0;
}