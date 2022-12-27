#include "sort_algorithms.h"
#include "graphics.h"
#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "stack.h"
using namespace std;
int random(int min, int max)
{
    return min + rand() % (max + 1 - min);
}
int main()
{
    initgraph();
    srand((int)time(0));
    int n = 5;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = random(1, 100);
    
    ShellSort(arr, n);
    
    _getch();
    return 0;
}

