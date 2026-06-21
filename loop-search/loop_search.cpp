#include <Windows.h>

#include <iostream>
#include <fstream>

bool DFS(int** graph, int size, int vertex, bool* visited, bool* stack, int parent )  {
	visited[vertex] = true;
	stack[vertex] = true;
	
	for (int i = 0; i < size; ++i)  {
		if (graph[vertex][i] == 1)  {
			if (stack[i] && i != parent)  {
				return true;
			} else if (!visited[i])  { 
				if (DFS(graph, size, i, visited, stack, vertex)) return true;
			}

		}

	}

	stack[vertex] = false;
	return false;
}

bool IsLoop(int** graph, int size)  { 
	bool* visited = new bool[size]();
	bool* stack = new bool[size]();
	bool result = false;
	
	for (int i = 0; i < size; ++i)  {
		if (!visited[i])  {
			if (DFS(graph, size, i, visited, stack, -1))  {
				result = true;
				break;
			}

		}

	}

	delete[] visited;
	delete[] stack;
	return result;
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
	if (IsLoop(graph, size)) {
		std::cout << "В графе ЕСТЬ цикл!" << std::endl;
	} else {
		std::cout << "В графе НЕТ цикла!" << std::endl;
	}

	for (int i = 0; i < size; ++i) {
		delete[] graph[i];
	}
	delete[] graph;

	return 0;
}