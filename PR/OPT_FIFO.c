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
            if (x % m)
            {
                pos = x % m;
                frame[pos] = p[i];
            }
            else
            {
                pos = predict(p[i], i + 1);
                frame[pos] = p[i];
            }
            printf("\t Frame[%d]=%d", pos, frame[pos]);
            x++;
        }
    }
    printf("\npage fault=%d", x);
}
int predict(int page, int index)
{
    int j, i, result = -1, farthest = index;
    for (i = 0; i < m; i++)
    {
        for (j = index; j < n; j++)
        {
            if (frame[i] == p[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    if (result == -1)
        return 0;
    else
        return result;
}