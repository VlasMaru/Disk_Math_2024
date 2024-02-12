#include <iostream>
#include <vector>
#include <string>
#include <set>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::vector <char> letters{ 'К','О','М','Б','И','Н','А','Т','О','Р','И','К','А' };
    std::set <std::string> words;
    for (int x = 0; x < 12; x++)
    {
        for (int y = 0; y < 13; y++)
        {
            for (int k = 0; k < 13; k++)
            {
                for (int z = 0; z < 13; z++)
                {
                    std::set <int> ind;
                    ind.insert(x);
                    ind.insert(y);
                    ind.insert(z);
                    ind.insert(k);
                    if (ind.size() == 4)
                    {
                        std::string word_o = "";
                        word_o += letters[x];
                        word_o += letters[y];
                        word_o += letters[k];
                        word_o += letters[z];
                        words.insert(word_o);
                        word_o = "";
                    }

                    ind.clear();
                }
            }
        }
    }

    std::cout << words.size();

}
