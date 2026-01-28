#include <stdio.h>
#include <stdlib.h>
#include "item.h"

void selection_sort(Item *a, int lo, int hi)
{
    for (int i = lo; i < hi; i++)
    {
        int min = i;
        for (int j = i + 1; j <= hi; j++)
        {
            if (less(a[j], a[min]))
            {
                min = j;
            }
        }
        exch(a[i], a[min]);
    }
}

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

void bubble_sort(Item *a, int lo, int hi)
{
    for (int i = lo; i < hi; i++)
    {
        for (int j = lo; j < hi - i; j++)
        {
            compexch(a[j], a[j + 1]);
        }
    }
}

void shaker_sort(Item *a, int lo, int hi)
{
    for (int i = lo; i < hi; i++)
    {

        for (int j = lo; j < hi - i; j++)
        {
            compexch(a[j], a[j + 1]);
        }

        for (int k = hi - i - 1; k > i; k--)
        {
            compexch(a[k - 1], a[k]);
        }
    }
}

void sort(Item *a, int lo, int hi)
{
    selection_sort(a, lo, hi);
    // insertion_sort(a, lo, hi);
    // bubble_sort(a, lo, hi);
    // shaker_sort(a, lo, hi);
}