#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

#define MAX 100

using namespace std;

struct Graph
{
	int num_vertices;
	int adjacency_matrix[MAX][MAX];
};

Graph createGraph(string file_name)
{
	Graph cur_graph;

	ifstream in(file_name);

	in >> cur_graph.num_vertices;

	for (int i = 0; i < cur_graph.num_vertices; i++)
	{
		for (int j = 0; j < cur_graph.num_vertices; j++)
		{
			in >> cur_graph.adjacency_matrix[i][j];
		}
	}
	in.close();

	return cur_graph;
}

bool isGraph(Graph g)
{
	for (int i = 0; i < g.num_vertices; i++)
	{
		if (g.adjacency_matrix[i][i] != 0)	return false;
	}
	return true;
}

bool isUndirectedGraph(Graph g)
{
	if (not isGraph(g))	return false;
	for (int i = 0; i < g.num_vertices; i++)
	{
		for (int j = 0; j < g.num_vertices; i++)
		{
			if (g.adjacency_matrix[i][j] != g.adjacency_matrix[j][i] && g.adjacency_matrix[i][j] * g.adjacency_matrix[j][i] <= 0)	return false;
		}
	}
	return true;
}

void display(Graph g)
{
	if (isGraph(g)) {
		for (int i = 0; i < g.num_vertices; i++)
		{
			for (int j = 0; j < g.num_vertices; j++)
			{
				cout << g.adjacency_matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
	else cout << "This is not a graph";
}

int countEdge(Graph g)
{
	if (not isGraph(g))	return 0;

	int edge = 0;

	for (int i = 0; i < g.num_vertices; i++)
	{
		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0)	edge++;
		}
	}

	for (int i = 0; i < g.num_vertices; i++)
	{
		for (int j = i; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0 && g.adjacency_matrix[j][i] > 0)	edge--;
		}
	}

	return edge;
}

int countEvenVertices(Graph g)
{
	if (not isGraph(g))	return 0;

	int count = 0;
	for (int i = 0; i < g.num_vertices; i++)
	{
		int order = 0;
		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0)	order++;
		}

		if (order % 2 == 0)	count++;
	}
	return count;
}

int countOddVertices(Graph g)
{
	if (not isGraph(g))	return 0;

	int count = 0;
	for (int i = 0; i < g.num_vertices; i++)
	{
		int order = 0;
		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0)	order++;
		}

		if (order % 2 == 1)	count++;
	}
	return count;
}

void BFS(Graph g, int start)
{
	queue<int> Queue;

	int* track = new int[g.num_vertices];
	Queue.push(start);
	track[start] = 1;

	while (!Queue.empty())
	{
		int i = Queue.front();
		Queue.pop();

		cout << i << "	";

		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0 and track[j] < 1)
			{
				Queue.push(j);
				track[j] = 1;
			}
		}
	}
								
	cout << endl;
	delete[] track;
}

void DFS(Graph g, int start)
{
	stack<int> Stack;

	int* track = new int[g.num_vertices];

	Stack.push(start);
	track[start] = 1;
	cout << start << "	";

	while (!Stack.empty())
	{
		bool isHaveUnvisitedChild = false;

		int i = Stack.top();

		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[i][j] > 0 && track[j] != 1)
			{
				Stack.push(j);
				track[j] = 1;

				cout << j << "\t";

				isHaveUnvisitedChild = true;
				break;
			}
		}

		if (not isHaveUnvisitedChild)
		{
			Stack.pop();
		}
	}
}


int countConnectedComponents(Graph g)
{
	int count = 0;
	int* track = new int[g.num_vertices];
	queue<int> Queue;

	for (int check = 0; check < g.num_vertices; check++)
	{
		if (track[check] < 1)
		{
			Queue.push(check);
			track[check] = 1;

			while (!Queue.empty())
			{
				int i = Queue.front();
				Queue.pop();

				for (int j = 0; j < g.num_vertices; j++)
				{
					if (g.adjacency_matrix[i][j] > 0 && track[j] < 1) 
					{
						Queue.push(j);
						track[j] = 1;
					}
				}
			}
			count++;
		}
	}
	delete[] track;
	return count;
}

int FindMinForPrim(int*& known, int*& cost, int size)
{
	int min;
	//Tim ra vi tri chua duoc known
	for (int i = 0; i < size; i++)
	{
		if (known[i] < 1)
		{
			min = i;
			break;
		}
	}

	//Tim vi tri co cost nho nhat
	for (int i = 0; i < size; i++)
	{
		if (known[i] < 1 && cost[i] < cost[min])	min = i;
	}
	return min;
}


void prim(Graph g, int& Cost)
{
	int count_vertices = 0;
	int* known = new int[g.num_vertices];
	int* cost = new int[g.num_vertices];
	cost[0] = 0;
	for (int i = 1; i < g.num_vertices; i++)
	{
		cost[i] = MAX;
	}

	int index;

	while (count_vertices < g.num_vertices - 1)
	{
		index = FindMinForPrim(known, cost, g.num_vertices);
		known[index] = 1;
		
		for (int j = 0; j < g.num_vertices; j++)
		{
			// update neighbor
			if (g.adjacency_matrix[index][j] < cost[j] && g.adjacency_matrix[index][j] > 0 && known[j] < 1)
			{
				cost[j] = g.adjacency_matrix[index][j];
				Cost += cost[j];
			}
		}
		count_vertices++;
	}
}


void Dijkstra(Graph g, int start, int des)
{
	if (start == des) {
		cout << "At destination already" << endl;
		return;
	}

	int* known = new int[g.num_vertices];
	int* cost = new int[g.num_vertices];
	int* path = new int[g.num_vertices];
	int count_matrix = 0;
	for (int i = 0; i < g.num_vertices; i++)
	{
		known[i] = 0;
		cost[i] = MAX;
		path[i] = -1;
	}

	cost[start] = 0;
	int index;
	while (count_matrix < g.num_vertices)
	{
		index = FindMinForPrim(known, cost, g.num_vertices);
		known[index] = 1;
		for (int j = 0; j < g.num_vertices; j++)
		{
			if (g.adjacency_matrix[index][j] > 0 && (cost[j] > g.adjacency_matrix[index][j] + cost[index]) && known[j] < 1)
			{
				cost[j] = g.adjacency_matrix[index][j] + cost[index];
				path[j] = index;
			}
		}
		count_matrix++;
	}



	while (true)
	{	
		cout << des; 
		des = path[des];
		if (des == -1)	break;
		else cout << " <- ";
	}

	delete[] known;
	delete[] cost;
	delete[] path;
}



int main()
{
	Graph g = createGraph("graph.txt");
	Dijkstra(g, 0, 7);

	return 0;
}