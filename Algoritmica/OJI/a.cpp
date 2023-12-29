#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char a[] = "Ana, are, mere, !Io;nu,", sep[] = "!,;";
    char* p;
    p = strtok(a, sep);
    cout << p;
    while(p)
    {
        p = strtok(0, sep);
        cout << p;
    }
}
