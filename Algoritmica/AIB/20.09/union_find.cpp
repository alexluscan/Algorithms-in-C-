
int Find(int x) // cautare cu compresie
{
    int r, y = x;
    while (y != t[y])
        y = t[y];
    r = y;

    // compresia drumului

    y = x;
    while (x != t[x])
    {
        x = t[x];
        t[y] = r;
        y = x;
    }

    return r;
}

int Find(int x)
{
    if (x = t[x])
        return x;
    return t[x] = Find(t[x]);
}

void Union(int x, int y)
{
    int r1 = Find(x);
    int r2 = Find(y);
    if (r1 != r2)
        t[r1] = r2;
}

