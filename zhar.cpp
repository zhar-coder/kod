#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
//#include "timer.h"
#include <omp.h>
#include<ctime>
#include<sys/times.h>
#include<unistd.h>
using std::vector;
double dtime()

{
    int tics_per_second;
    tics_per_second = sysconf(_SC_CLK_TCK);
    clock_t dub;
    struct tms t;
    dub=times(&t);
    return (double)dub/tics_per_second;
}


int main()
{
    srand(time(0));
//    Timer t;
    int SIZE;
    printf("Введите количество вершин: ");
    scanf("%d", &SIZE);
    double time_begin=dtime();
    vector< vector<int> > a(SIZE, vector<int>(SIZE));			// матрица связей
    vector<int> d(SIZE);				// минимальное расстояние
    vector<int> v(SIZE);				// посещенные вершины
    int temp, minindex, min;
    int begin_index = 0;
   // t.reset();
    // Инициализация матрицы связей
    for (int i = 0; i < SIZE; i++)
    {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++)
        {
            temp = rand()%9+1;
            a[i][j] = temp;
            a[j][i] = temp;
        }
    }
    // Вывод матрицы связей
//d    for (int i = 0; i < SIZE; i++)
//d    {
//d        for (int j = 0; j < SIZE; j++)
    //       printf("%3d ", a[i][j]);
    // DPROF<===   printf("\n");
//d    }
    // Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    
    // Шаг алгоритма
    do
    {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        {						// Если вершину ещё не
                                // обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            {					// Переприсваиваем
                                // значения
                min = d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным
        // весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 10000);



    // Вывод кратчайших расстояний до вершин
// d   printf("\nКратчайшие расстояния до вершин: \n");
//d    for (int i = 0; i < SIZE; i++)
//d        printf("%3d ", d[i]);

    // Восстановление пути
    int ver[SIZE];				// массив посещенных
                                // вершин
    int end = SIZE-1;				// индекс конечной
                                // вершины
    ver[0] = end + 1;			// начальный элемент -
                                // конечная вершина
    int k = 1;					// индекс предыдущей
                                // вершины
    int weight = d[end];		// вес конечной вершины

    while (end != begin_index)	// пока не дошли до
                                // начальной вершины
    {
        for (int i = 0; i < SIZE; i++)	// просматриваем все
                                        // вершины
            if (a[end][i] != 0)	// если связь есть
            {
                int temp = weight - a[end][i];	// определяем вес
                                                // пути из
                                                // предыдущей
                                                // вершины
                if (temp == d[i])	// если вес совпал с
                                    // рассчитанным
                {				// значит из этой вершины
                                // и был переход
                    weight = temp;	// сохраняем новый вес
                    end = i;	// сохраняем предыдущую
                                // вершину
                    ver[k] = i + 1;	// и записываем ее в
                                    // массив
                    k++;
                }
            }
    }
    // Вывод пути (начальная вершина
    // оказалась в конце массива из k
    // элементов)
// DPROF   <===  printf("\nВывод кратчайшего пути\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);
    double time_end=dtime();
    double time=time_end-time_begin;
    printf("Время выполнения программы: %d" ,time);
    getchar();
    getchar();
    return 0;
}
