#include <iostream>
#include <array> 
#include <random>
#include <locale>
#include <string>



int width = 6, height = 6, max_length = 0;
int matrix[6][6] = {
    {0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0 },
};

int random1() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 5);
    int a = dist(gen);
    return a;
}

int string_length(int number) {
    if (number == 0) return 1;

    number = std::abs(number); 
    return static_cast<int>(std::log10(number)) + 1;
}

void print() 
{
    std::cout << "_______________" << std::string(max_length * 3, '_') << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 6; j++)
        {
            std::cout << std::string(max_length - string_length(matrix[i][j]), ' ') << matrix[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "_______________" << std::string(max_length * 3, '_') << std::endl;
}

void mixing(int vector)
{
    int i_,j_;
    switch (vector) {
    case 1:
        for (int a = 0; a < 6; a++)
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    i_ = i + 1;
                    if (matrix[i_][j] == matrix[i][j]) {
                        matrix[i_][j] = matrix[i_][j] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                    if (matrix[i_][j] == 0) {

                        matrix[i_][j] = matrix[i_][j] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                }
            }
        }
        break;
    case 2:
        for (int a = 0; a < 6; a++)
        {
            for (int i = 5; i > 0; i--)
            {
                for (int j = 0; j < 6; j++)
                {
                    i_ = i - 1;
                    if (matrix[i_][j] == matrix[i][j]) {
                        matrix[i_][j] = matrix[i_][j] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                    if (matrix[i_][j] == 0) {

                        matrix[i_][j] = matrix[i_][j] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                }
            }
        }
        break;
    case 3:
        for (int a = 0; a < 6; a++)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    j_ = j + 1;
                    if (matrix[i][j_] == matrix[i][j]) {
                        matrix[i][j_] = matrix[i][j_] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                    if (matrix[i][j_] == 0) {

                        matrix[i][j_] = matrix[i][j_] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                }
            }
        }
        break;
    case 4:
        for (int a = 0; a < 6; a++)
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 5; j > 0; j--)
                {
                    j_ = j - 1;
                    if (matrix[i][j_] == matrix[i][j]) {
                        matrix[i][j_] = matrix[i][j_] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                    if (matrix[i][j_] == 0) {

                        matrix[i][j_] = matrix[i][j_] + matrix[i][j];
                        matrix[i][j] = 0;
                    }
                }
            }
        }
        break;
    }        
}

void check() {
    int count = 0, max = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (matrix[i][j] == 0) { count++; }
            if (max < matrix[i][j]) { max = matrix[i][j]; }
        }
    }
    if (count == 0) {
        std::cout << "Конец игры, твой результат: " << max;
    }
    max_length = string_length(max);
}

void spawn(int n) {
    int a1, a2;
    for (int i = 0; i < n;)
    {
        a1 = random1(), a2 = random1();
        if (matrix[a1][a2] != 0)
        {
            a1 = random1(), a2 = random1();
            continue;
        }
        else
        {
            matrix[a1][a2] = 2;
            i++;
            check();
        }
    }
}

int main()
{
    int n, m;
    std::locale::global(std::locale("")); // исправляет проблемы с показом руского языка
    std::cout << "Сколько 2 спавнить за раунд: ";
    std::cin >> n;
    spawn(n);
    print();
    int end = 5;
    while (end != 0)
    {
        std::cout << "0 - конец игры, 1 - вниз, 2 - вверх, 3 - право, 4 - лево" << std::endl;
        std::cin >> m;
        mixing(m);
        spawn(n);
        print();
    }
}