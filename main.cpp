#include "basic_f.hpp"
#include "calculus.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void push (vector<double> vec, string path)
{
    FILE* fd = fopen (path.c_str(), "w");
    int   m  = static_cast<int> (vec.size());

    for (int i = 0; i < m; ++i) { fprintf (fd, "%60.30e\n", vec[i]); }

    fclose (fd);
}        //Запись в файлы

void running_main (int N)
{

    auto func = [] (double x) -> double
    { return x; };        // Определим функцию справа
    cout << "Поехали!!!" << endl;

    // Ac=b
    auto diags = gen_diag (N);        // Вычисляем матрицу для метода прогонки
    auto f     = gen_f (N, func);        // Вычисляем вектор b для метода прогонки

    auto matr = matr_initial (diags, f);        // Подготовим для питона

    // Запись в файл
    push (matr[0], "tmp/a.txt");
    push (matr[1], "tmp/b.txt");
    push (matr[2], "tmp/c.txt");
    push (matr[3], "tmp/d.txt");
    push (matr[4], "tmp/e.txt");
    push (matr[5], "tmp/f.txt");

    cout << "Ура, товарищи!" << endl;
}

int main (int argc, char* argv[])
{
    if (argc > 1)
    {
        running_main (stoi (argv[1]));
        return 0;
    }
    else cout << "Некорректные входные аргументы :С" << endl;
    return -1;
}