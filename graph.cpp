﻿#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Ориентированный граф с использованием матрицы смежности
struct Graph{
    // Количество вершин в графе
    int V;
    // Матрица смежности
    vector<int>* adj;

    // рекурсивная функция
    // используется countPaths ()
    void countPathsUtil(int, int, bool[], int&);

    // Конструктор
    Graph(int V);
    void addEdge(int u, int v);
    int countPaths(int s, int d);
    void printGraph();
    void printMatrix();
};

Graph::Graph(int V){

    this->V = V;
    adj = new vector<int>[V];
}

// Добавить элемент в граф
void Graph::addEdge(int u, int v){
    // Добавить v в список u.
    adj[u].push_back(v);
}

// Возвращает количество путей от 's' до 'd'
int Graph::countPaths(int s, int d){
    // Отметим все вершины
    // как не посещенный

    bool* visited = new bool[V];

    memset(visited, false, sizeof(visited));

    // Вызов рекурсивного помощника

    // функция для печати всех путей

    int pathCount = 0;

    countPathsUtil(s, d, visited, pathCount);

    return pathCount;
}

// Рекурсивная функция для печати всех путей
// от 'u' до 'd'. посетил [] отслеживает
// вершины в текущем пути. путь [] магазины
// фактические вершины и path_index
// текущий индекс в пути []

void Graph::countPathsUtil(int u, int d, bool visited[],int& pathCount){

    visited[u] = true;
    // Если текущая вершина совпадает с пунктом назначения,
    // затем увеличиваем количество
    if (u == d) pathCount++;

    // Если текущая вершина не является пунктом назначения
    else{
        // Повторение для всех вершин, смежных с
        // текущая вершина

        vector<int>::iterator i;

        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            if (!visited[*i])countPathsUtil(*i, d, visited, pathCount);
        }
    }
    visited[u] = false;
}

void Graph::printGraph(){
    
    for (int i = 0; i < V; i++)
    {
        // вывести номер текущей вершины
        cout << i << " ——> ";

        // вывести все соседние вершины вершины `i`
        for (int v : adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

bool search(vector<int> a, int k) {
    bool flag = false;
    for (int x : a) {
        if (x == k) flag = true;
    }
    return flag;

}

// Вывод матрицы смежности
void Graph::printMatrix() {
    cout << "\n      ";
    for (int i = 0; i < V; i++) cout << i <<" ";
    cout << endl;
    for (int i = 0; i < V; i++)
    {   
        vector<int>paths;
        for (int v : adj[i]) {
            paths.push_back(v);
        }
        // вывести номер текущей вершины
        cout << i << " :   ";
        for (int j = 0; j < V; j++) {
            if (search(paths, j)) {
                cout << 1 << " ";
            }
            else {
                cout << 0 << " ";
            }
        }
        // вывести все соседние вершины вершины `i`
        
        cout << endl;
    }
}

// Код драйвера

int main(){
    setlocale(LC_ALL, "");
    // Создать график, приведенный на диаграмме выше
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 0);
    g.addEdge(2, 1);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(4, 3);
    int s = 2, d = 4;
    //g.printGraph();
    g.printMatrix();
    cout <<"\nКоличество путей из  "<<s<<"  в  "<< d <<"  = " << g.countPaths(s, d);
}