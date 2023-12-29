#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define md (l+r)/2

//ifstream fin("horq.in");
//ofstream fout("horq.out");

const int Dim = 100003, Inf = 0x3f3f3f3f;


int n, m, t, L, R, op;
long long S[4 * Dim], cnt[4 * Dim], val;


void Update(int x, int l, int r);
long long Query(int x, int l, int r);

int main()
{
    cin >> t;
    //scanf("%d", &t);

    while ( t-- )
    {

        //scanf("%d%d", &n, &m);
        cin >> n >> m;
        memset(S, 0, sizeof(S));
        memset(cnt, 0, sizeof(cnt));
        while ( m--)
        {
            cin >> op >> L >> R;
           // scanf("%d%d%d", &op, &L, &R);
            if ( op == 0 )
            {
                cin >> val;
                //scanf("%d", &val);
                Update(1, 1, n);
            }
            else
                //printf("%ll\n", Query(1, 1, n));
                cout << Query(1, 1, n) << '\n';
        }
    }
//    fin.close();
//    fout.close();
    return 0;
}


void Update(int x, int l, int r)
{

    if ( cnt[x] != 0 )
    {
        S[x] += cnt[x] * (r - l + 1);
        if (l != r)
        {
            cnt[2 * x]     += cnt[x];
            cnt[2 * x + 1] += cnt[x];
        }
        cnt[x] = 0;
    }
    if ( l > r || l > R || r < L )
        return;

    if ( L <= l && r <= R )
    {
        S[x] += val * (r - l + 1);
		if (l != r)
		{
			cnt[2 * x]     += val;
			cnt[2 * x + 1] += val;
		}
    	return;
    }

    Update(2 * x, l, md);
    Update(2 * x + 1, md + 1, r);

    S[x] = S[2 * x] + S[2 * x + 1];
}

long long Query(int x, int l, int r)
{


    if ( cnt[x] != 0 )
    {
        S[x] += cnt[x] * (r - l + 1);
        if (l != r)
        {
            cnt[2 * x]     += cnt[x];
            cnt[2 * x + 1] += cnt[x];
        }
        cnt[x] = 0;
    }

    if (L > r || l > R || l > r)
        return 0;
    if (L <= l && r <= R)
        return S[x];
    long long s1 = 0, s2 = 0;
    s1 = Query(2 * x, l, md);
    s2 = Query(2 * x + 1, md + 1, r);

    return s1 + s2;
}
