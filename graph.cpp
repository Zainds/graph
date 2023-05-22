#include <iostream>
#include <list>
using namespace std;

// Ориентированный граф с использованием матрицы смежности
struct Graph{
    // Количество вершин в графе
    int V;
    list<int>* adj;

    // рекурсивная функция
    // используется countPaths ()

    void countPathsUtil(int, int, bool[], int&);

    // Конструктор
    Graph(int V);

    void addEdge(int u, int v);
    int countPaths(int s, int d);
    void printGraph();

};

Graph::Graph(int V){

    this->V = V;
    adj = new list<int>[V];
}

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

        list<int>::iterator i;

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
    g.printGraph();
    cout <<"Количество путей из  "<<s<<"  в  "<< d <<"  = " << g.countPaths(s, d);
}