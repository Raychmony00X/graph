#include <Windows.h>

#include <iostream>
#include <sstream>
#include <fstream>

void DFS(int** graph, int size, int vertex, bool* visited, std::ostringstream& result)  {
	visited[vertex] = true;
	result << vertex + 1 << " ";
	
	for (int i = 0; i < size; ++i)  {
		if (graph[vertex][i] == 1 && !visited[i])  {
			DFS(graph, size, i, visited, result);
		}

	}

}

int main()  {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream graph_txt("graph.txt");
	if (!graph_txt.is_open()) return 1;
	
	int size;
	graph_txt >> size;

	int** graph = new int*[size];
	for (int i = 0; i < size; ++i)  {
		graph[i] = new int[size];
	}

	for (int i = 0; i < size; ++i)  {
		for (int j = 0; j < size; ++j)  {
			graph_txt >> graph[i][j];
		}

	}
	graph_txt.close();

	if (size <= 0) return 0;
	std::cout << size << std::endl;
	for (int i = 0; i < size; ++i)  {
		for (int j = 0; j < size; ++j)  {
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}

	bool* visited = new bool[size]();
	std::ostringstream result;
	DFS(graph, size, 0, visited, result);
	std::cout << "Порядок обхода вершин: " << result.str() << " " << std::endl;

	for (int i = 0; i < size; ++i)  {
		delete[] graph[i];
	}
	delete[] graph;
	delete[] visited;


	return 0;
}