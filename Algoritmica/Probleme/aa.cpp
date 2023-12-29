#include <iostream>
#include <cstring>
using namespace std;

int n;
char x[255], s[255];

int main()
{
    cin.getline(s, 255);
    cin.getline(x, 255);

    n = strlen(s);
    char aux[255], nm[255];

    for (int i = 0; i < n; ++i)
    {
        int j = i;
        while (s[i] != ' ')
            ++i;
        strncpy(aux, s + j, i - j);
        aux[i - j] = NULL;
        j = ++i;
        while (s[i] != ';')
            ++i;
        if (strcmp(x, aux) == 0)
        {
            strncpy(nm, s + j, i - j);
            nm[i - j] = NULL;
            cout << nm << ' ';
        }
        ++i;
    }

    return 0;
}
