#include <iostream>
#include <vector>

using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
    Edge(int _src,int _dest) {
        src = _src;
        dest = _dest;
    }
};

// Класс для представления graphического объекта
class Graph
{
public:

    // вектор векторов для представления матрицы смежности
    vector<vector<int>> adjList;

    // Конструктор Graphа
    Graph(vector<Edge> const& edges, int n)
    {
        // изменить размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        adjList.resize(n);

        // добавляем ребра в ориентированный graph
        for (Edge edge : edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// Функция для обхода DFS - Поиск в ширину
void DFS(Graph const& graph, int v, vector<bool>& visited)
{
    // отметить текущий узел как посещенный
    visited[v] = true;

    // делаем для каждого ребра (v, u)
    for (int u : graph.adjList[v])
    {
        // `u` не посещается
        if (!visited[u]) {
            DFS(graph, u, visited);
        }
    }
}

// Функция для проверки, является ли graph сильно связным или нет
bool isStronglyConnected(Graph const& graph, int n)
{
    // делаем для каждой вершины
    for (int i = 0; i < n; i++)
    {
        // чтобы отслеживать, посещена ли вершина или нет
        vector<bool> visited(n);

        // запускаем DFS с первой вершины
        DFS(graph, i, visited);

        // Если обход DFS не посещает все вершины,
        // тогда graph не сильно связан
        if (find(visited.begin(), visited.end(), false) != visited.end()) {
            return false;
        }
    }

    return true;
}

void printGraph(Graph const& graph, int n)
{
    for (int i = 0; i < n; i++)
    {
        // вывести номер текущей вершины
        cout << i << " ——> ";

        // вывести все соседние вершины вершины `i`
        for (int v : graph.adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main()
{   
    setlocale(LC_ALL, "");
    // vector ребер Graph согласно схеме выше
    vector<Edge> edges = {
        {0, 4}, {1, 0}, {1, 2}, {2, 1}, {2, 4},
        {3, 1}, {3, 2}, {4, 3}
    };
    // общее количество узлов в Graph
    int n = 5;
    
    // строим graph из заданных ребер
    Graph graph(edges, n);

    printGraph(graph, n);
    // проверяем, не является ли graph сильно связным или нет
    if (isStronglyConnected(graph, n)) {
        cout << "The graph is strongly connected\n";
    }
    else {
        cout << "The graph is not strongly connected\n";
    }

}