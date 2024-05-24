#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    vector<int> g = { 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 }; // порождающий многочлен
    int n = 31; // общее число элементов
    int m = 16; // число информационных элементов
    int length = g.size();

    // Дополняем порождающий многочлен нулями
    for (int i = 0; i < n - length; ++i) {
        g.push_back(0);
    }

    // Создаём временную матрицу G0
    vector<vector<int>> G0(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        rotate(g.rbegin(), g.rbegin() + 1, g.rend()); // Сдвигаем порождающий многочлен на i позиций
        G0[i] = g;
    }

    // Преобразуем G0 в матрицу G
    vector<vector<int>> G(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            G[i][j] = G0[i][j];
        }
    }

    // Создаём таблицу кодовых слов
    vector<pair<string, string>> codewords_table;
    int table_length = 1 << m; // Длина таблицы
    for (int i = 0; i < table_length; ++i) {
        bitset<16> d(i); // Получаем бинарное представление числа i
        string info_word = d.to_string().substr(16 - m); // Получаем информационное слово
        string codeword = ""; // Кодовое слово
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < m; ++k) {
                sum += (d[k] * G[k][j]) % 2; // Вычисляем сумму произведений информационного слова на столбец G
            }
            codeword += std::to_string(sum % 2); // Добавляем бит в кодовое слово
        }
        codewords_table.push_back(make_pair(info_word, codeword));
    }

    // Записываем таблицу в файл
    ofstream file("output1.txt");
    file << "Разрешённые кодовые комбинации: \n";
    for (auto& pair : codewords_table) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();

    return 0;
}