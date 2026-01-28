

#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "stack.h"
#include "sorts.h"
#include <sys/time.h>

#define CUTOFF 10
#define SZ2 (sz + sz)
#define MIN(X, Y) ((X < Y) ? (X) : (Y))

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

int partition(Item *a, int lo, int hi)
{
    int i = lo, j = hi + 1;
    Item v = a[lo];
    while (1)
    {
        while (less(a[++i], v)) // Find item on left to swap.
            if (i == hi)
                break;
        while (less(v, a[--j])) // Find item on right to swap.
            if (j == lo)
                break;
        if (i >= j)
            break; // Check if pointers cross.
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]); // Swap with partitioning item.
    return j;          // Return index of item known to be in place.
}

void shuffle(Item *a, int N)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand48(tv.tv_usec);
    for (int i = N - 1; i > 0; i--)
    {
        int j = (unsigned int)(drand48() * (i + 1));
        exch(a[i], a[j]);
    }
}

int median_of_3(Item *a, int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;
    if (less(a[mid], a[lo]))
        exch(a[lo], a[mid]);
    if (less(a[hi], a[lo]))
        exch(a[lo], a[hi]);
    if (less(a[hi], a[mid]))
        exch(a[mid], a[hi]);
    return mid;
}

void quick_sort(Item *a, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j - 1);
    quick_sort(a, j + 1, hi);
}

void quick_sort_2(Item *a, int lo, int hi)
{
    if (hi <= lo + CUTOFF - 1)
    {
        insertion_sort(a, lo, hi);
        return;
    }
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j - 1);
    quick_sort(a, j + 1, hi);
}

void quick_sort_3(Item *a, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int median = median_of_3(a, lo, hi);
    exch(a[lo], a[median]);
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j - 1);
    quick_sort(a, j + 1, hi);
}

void quick_sort_4(Item *a, int lo, int hi)
{
    if (hi <= lo + CUTOFF - 1)
    {
        insertion_sort(a, lo, hi);
        return;
    }
    int median = median_of_3(a, lo, hi);
    exch(a[lo], a[median]);
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j - 1);
    quick_sort(a, j + 1, hi);
}

void quick_sort_5(Item *a, int lo, int hi)
{
    stack *s = stack_create();
    stack_push(lo, s);
    stack_push(hi, s);
    while (!stack_empty(s))
    {
        hi = stack_pop(s);
        lo = stack_pop(s);
        if (hi <= lo)
        {
            continue;
        }
        int j = partition(a, lo, hi);
        if (j - lo > hi - j)
        {
            stack_push(lo, s);
            stack_push(j - 1, s);
            stack_push(j + 1, s);
            stack_push(hi, s);
        }
        else
        {
            stack_push(j + 1, s);
            stack_push(hi, s);
            stack_push(lo, s);
            stack_push(j - 1, s);
        }
    }
    stack_destroy(s);
}

void quick_sort_6(Item *a, int lo, int hi)
{
    stack *s = stack_create();
    stack_push(lo, s);
    stack_push(hi, s);
    while (!stack_empty(s))
    {
        hi = stack_pop(s);
        lo = stack_pop(s);
        if (hi <= lo + CUTOFF - 1)
        {
            insertion_sort(a, lo, hi);
            continue;
        }
        int median = median_of_3(a, lo, hi);
        exch(a[lo], a[median]);
        int i = partition(a, lo, hi);
        if (i - lo > hi - i)
        {
            stack_push(lo, s);
            stack_push(i - 1, s);
            stack_push(i + 1, s);
            stack_push(hi, s);
        }
        else
        {
            stack_push(i + 1, s);
            stack_push(hi, s);
            stack_push(lo, s);
            stack_push(i - 1, s);
        }
    }
    stack_destroy(s);
}

void quick_sort_3_way(Item *a, int lo, int hi)
{
    if (hi <= lo)
        return;
    Item v = a[lo];
    int lt = lo, gt = hi, i = lo;
    while (i <= gt)
    {
        if (a[i] < v)
        {
            exch(a[lt], a[i]);
            lt++;
            i++;
        }
        else if (a[i] > v)
        {
            exch(a[i], a[gt]);
            gt--;
        }
        else
        {
            i++;
        }
    }
    quick_sort(a, lo, lt - 1);
    quick_sort(a, gt + 1, hi);
}

void sort(Item *a, int lo, int hi)
{
    shuffle(a, hi + 1);
    quick_sort(a, lo, hi);
    // quick_sort_2(a, lo, hi);
    // quick_sort_3(a, lo, hi);
    // quick_sort_4(a, lo, hi);
    // quick_sort_5(a, lo, hi);
    // quick_sort_6(a, lo, hi);
    // quick_sort_3_way(a, lo, hi);
}