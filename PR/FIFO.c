#include <stdio.h>
int frame[10], m, n;
int p[30] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 2, 1, 2, 0, 1, 7, 0, 1};
int search(int data)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (data == frame[i])
        {
            return (1);
        }
    }
    return 0;
}
void main()
{
    int i, x = 0, pos;
    m = 3;
    n = 20;
    for (i = 0; i < m; i++)
    {
        frame[i] = -1;
    }
    x = 0;
    printf("\n replacing page from frame=\n");
    for (i = 0; i < n; i++)
    {
        if (search(p[i]) == 0)
        {
            pos = x % m;
            frame[pos] = p[i];
            printf("\t frame[%d]=%d", pos, frame[pos]);
            x++;
        }
    }
    printf("\n page fault=%d\n", x);
}