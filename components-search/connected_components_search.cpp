#include <Windows.h>

#include <iostream>
#include <sstream>
#include <fstream>

void DFS(int** graph, int size, int vertex, int* cids, int cid)  {
	cids[vertex] = cid;

	for (int i = 0; i < size; ++i)  {
		if (graph[vertex][i] == 1 && cids[i] == 0)  {
			DFS(graph, size, i, cids, cid);
		}

	}

}

void FindComponents(int** graph, int size, std::ostringstream& result)  {
	int* cids = new int[size]();
	int cid = 1;

	for (int i = 0; i < size; ++i)  {
		if (cids[i] == 0)  {
			DFS(graph, size, i, cids, cid);
			cid += 1;
		}

	}

	for (int i = 0; i < size; ++i)  {
		result << i + 1 << " - " << cids[i] << std::endl;
	}
	result << "Количество компонентов связности в графе: " << cid - 1;

	delete[] cids;
}

int main()  {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream graph_txt("graph.txt");
	if (!graph_txt.is_open()) return 1;

	int size;
	graph_txt >> size;

	int** graph = new int* [size];
	for (int i = 0; i < size; ++i) {
		graph[i] = new int[size];
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			graph_txt >> graph[i][j];
		}

	}
	graph_txt.close();

	if (size <= 0) return 0;
	std::cout << size << std::endl;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::ostringstream result;
	FindComponents(graph, size, result);
	std::cout << "Принадлежность вершин компонентам связности:" << std::endl;
	std::cout << result.str() << std::endl;

	for (int i = 0; i < size; ++i) {
		delete[] graph[i];
	}
	delete[] graph;

	return 0;
}