
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int i, m, val;

    Vector *v;

    v = vector_construct();

    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        scanf("%d", &val);
        vector_push_back(v, val);
    }

    vector_reverse(v);

    for (i = 0; i < vector_size(v); i++)
        printf("%d\n", vector_get(v, i));

    vector_destroy(v);

    return 0;
}
