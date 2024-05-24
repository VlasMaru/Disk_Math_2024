#include <iostream>
#include <vector>
#include <climits>
#include <Windows.h>

const int INF = INT_MAX; // Значение для недостижимых вершин

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INF) {
                std::cout << "INF ";
            }
            else {
                std::cout << val << " ";
            }
        }
        std::cout << std::endl;
    }
}

void printIncidenceMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> adjacencyToIncidence(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    int numEdges = 0;

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != INF) {
                numEdges++;
            }
        }
    }

    std::vector<std::vector<int>> incidenceMatrix(numVertices, std::vector<int>(numEdges, 0));
    int edgeIndex = 0;

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != INF) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = -1;
                edgeIndex++;
            }
        }
    }

    return incidenceMatrix;
}

bool isEulerianGraph(const std::vector<std::vector<int>>& incidenceMatrix) {
    for (const auto& row : incidenceMatrix) {
        int sum = 0;
        for (int val : row) {
            sum += val;
        }
        if (sum != 0) {
            return false;
        }
    }
    return true;
}

void floydWarshall(const std::vector<std::vector<int>>& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    std::vector<std::vector<int>> dist(numVertices, std::vector<int>(numVertices, INF));

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = adjacencyMatrix[i][j];
            }
        }
    }

    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    std::cout << "Матрица смежности:" << std::endl;
    printMatrix(adjacencyMatrix);

    std::cout << "Матрица инцидентности:" << std::endl;
    printIncidenceMatrix(adjacencyToIncidence(adjacencyMatrix));

    std::cout << "Матрица кратчайших путей:" << std::endl;
    printMatrix(dist);


}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");


    std::vector<std::vector<int>> adjacencyMatrix = {
        {0, INF, INF, INF, INF, INF, INF, INF},
        {INF, 0, INF, INF, 15, 12, INF, INF},
        {INF, INF, 0, INF, 10, INF, INF, INF},
        {INF, INF, INF, 0, INF, 18, 17, INF},
        {INF, INF, INF, INF, 0, 16, 18, INF},
        {INF, 12, INF, 14, INF, 0, 19, INF},
        {10, INF, INF, INF,13, INF, 0, INF},
        {INF, INF, 11, INF, INF, INF, INF, INF}
    };



    if (isEulerianGraph(adjacencyToIncidence(adjacencyMatrix))) {
        std::cout << "Граф является Эйлеровым" << std::endl;
    }
    else {
        std::cout << "Граф не является Эйлеровым" << std::endl;
    }

    //     Выводим информацию
    floydWarshall(adjacencyMatrix);
}