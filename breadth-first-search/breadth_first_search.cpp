#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>

void QueuePush(int*& arr, int& size, int new_element) {
	int* new_arr = new int[size + 1];
	for (int i = 0; i < size; ++i) {
		new_arr[i] = arr[i];
	}

	new_arr[size] = new_element;
	size++;
	delete[] arr;
	arr = new_arr;

}

void QueuePop(int*& arr, int& size) {
	int* new_arr = new int[size - 1];
	for (int i = 1; i < size; ++i) {
		new_arr[i - 1] = arr[i];
	}

	size--;
	delete[] arr;
	arr = new_arr;
}

void BFS(int** graph, int size, int vertex, bool* visited, std::ostringstream& result) {
	int queue_size = 0;
	int* queue = nullptr;
	
	int start_vertex = vertex - 1;
	QueuePush(queue, queue_size, start_vertex);
	visited[start_vertex] = true;
	while (queue_size > 0)  {
		int current = queue[0];
		QueuePop(queue, queue_size);
		result << current + 1 << " ";
		
		for (int i = 0; i < size; ++i)  { 
			if (graph[current][i] == 1 && !visited[i])  { 
				visited[i] = true;
				QueuePush(queue, queue_size, i);
			}

		}

	}

	if (queue != nullptr) delete[] queue;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream graph_txt("graph.txt");
	if (!graph_txt.is_open()) return 1;

	int size;
	graph_txt >> size;

	int** graph = new int* [size];
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
	
	int vertex;
	std::cout << "В графе 7 вершин. Введите номер вершины, с которой начнётся"
		" обход: ";
	std::cin >> vertex;
	while (vertex <= 0 || vertex > 7)  {
		std::cout << "Введите индекс 1-7! ";
		std::cin >> vertex;
	}

	bool* visited = new bool[size]();
	std::ostringstream result;
	BFS(graph, size, vertex, visited, result);
	std::cout << "Порядок обхода вершин: " << result.str() << " " << std::endl;

	for (int i = 0; i < size; ++i) {
		delete[] graph[i];
	}
	delete[] graph;
	delete[] visited;

	return 0;
}