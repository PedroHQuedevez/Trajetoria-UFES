#include <stdio.h>
#include <stdlib.h>
#include "item.h"

#define CUTOFF 10
#define SZ2 (sz + sz)
#define MIN(X, Y) ((X < Y) ? (X) : (Y))
// REVISAR 4 6 7;

void insertion_sort(Item *a, int lo, int hi)
{
    for (int i = lo + 1; i <= hi; i++)
    {
        for (int j = i; j > lo; j--)
        {
            compexch(a[j - 1], a[j]);
        }
    }
}

void merge(Item *a, Item *aux, int lo, int mid, int hi)
{
    for (int k = lo; k <= hi; k++)
        aux[k] = a[k]; // Copy array
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++)
    { // Merge
        if (i > mid)
            a[k] = aux[j++];
        else if (j > hi)
            a[k] = aux[i++];
        else if (less(aux[j], aux[i]))
            a[k] = aux[j++];
        else
            a[k] = aux[i++];
    }
}

// merge sort classico top-down recursivo sem nenhuma otimizacao.

void merge_sort_1(Item *a, Item *aux, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2; // Avoid overflow.
    merge_sort_1(a, aux, lo, mid);
    merge_sort_1(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

// merge sort top-down recursivo com cut-off para insertion sort.
void merge_sort_2(Item *a, Item *aux, int lo, int hi)
{

    if (hi <= lo + CUTOFF - 1)
    {
        insertion_sort(a, lo, hi);
        return;
    }
    int mid = lo + (hi - lo) / 2;
    merge_sort_2(a, aux, lo, mid);
    merge_sort_2(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

// merge sort top-down recursivo com merge skip.
void merge_sort_3(Item *a, Item *aux, int lo, int hi)
{
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    merge_sort_3(a, aux, lo, mid);
    merge_sort_3(a, aux, mid + 1, hi);
    if (!less(a[mid + 1], a[mid]))
        return;
    merge(a, aux, lo, mid, hi);
}

// fus ̃ao das Vers ̃oes 2 e 3, isto  ́e, usar as duas otimiza ̧c ̃oes: cut-off e merge skip.
void merge_sort_4(Item *a, Item *aux, int lo, int hi)
{
    if (hi <= lo + CUTOFF - 1)
    {
        insertion_sort(a, lo, hi);
        return;
    }
    int mid = lo + (hi - lo) / 2;
    merge_sort_4(a, aux, lo, mid);
    merge_sort_4(a, aux, mid + 1, hi);
    if (!less(a[mid + 1], a[mid]))
        return;
    merge(a, aux, lo, mid, hi);
}

// merge sort bottom-up sem nenhuma otimiza ̧c ̃ao.
void merge_sort_5(Item *a, int lo, int hi)
{
    int N = (hi - lo) + 1;
    int y = N - 1;
    Item *aux = malloc(N * sizeof(Item));
    for (int sz = 1; sz < N; sz = SZ2)
    {
        for (int lo = 0; lo < N - sz; lo += SZ2)
        {
            int x = lo + SZ2 - 1;
            merge(a, aux, lo, lo + sz - 1, MIN(x, y));
        }
    }
    free(aux);
}

// altere a Vers ̃ao 5 para implementar o que seria o “cut-off ” na vers ̃ao bottom-up.
void merge_sort_6(Item *a, int lo, int hi)
{
    int N = (hi - lo) + 1;
    int y = N - 1;
    Item *aux = malloc(N * sizeof(Item));
    for (int sz = 1; sz < N; sz = SZ2)
    {
        for (int lo = 0; lo < N - sz; lo += SZ2)
        {
            if (sz <= CUTOFF)
            {
                insertion_sort(a, lo, MIN(lo + sz + sz - 1, y));
            }
            else
            {
                int x = lo + SZ2 - 1;
                merge(a, aux, lo, lo + sz - 1, MIN(x, y));
            }
        }
    }
    free(aux);
}

// altere a Vers ̃ao 6 para implementar o merge skip na vers ̃ao bottom-up.
void merge_sort_7(Item *a, int lo, int hi)
{
    int N = (hi - lo) + 1;
    int y = N - 1;
    Item *aux = malloc(N * sizeof(Item));
    for (int sz = 1; sz < N; sz = SZ2)
    {
        for (int lo = 0; lo < N - sz; lo += SZ2)
        {
            if (sz <= CUTOFF)
            {
                insertion_sort(a, lo, MIN(lo + sz + sz - 1, y));
            }
            else
            {
                int x = lo + SZ2 - 1;
                if (!less(a[lo + sz], a[lo + sz - 1]))
                    continue;
                merge(a, aux, lo, lo + sz - 1, MIN(x, y));
            }
        }
    }
    free(aux);
}

void sort(Item *a, int lo, int hi)
{
    int n = (hi - lo) + 1;
    Item *aux = malloc(n * sizeof(Item));
    // merge_sort_1(a, aux, lo, hi);
    // merge_sort_2(a, aux, lo, hi);
    merge_sort_3(a, aux, lo, hi);
    // merge_sort_4(a, aux, lo, hi);
    // merge_sort_5(a, lo, hi);
    // merge_sort_6(a, lo, hi);
    // merge_sort_7(a, lo, hi);
    free(aux);
}
