#include <fstream.h>
#include <iomanip.h>
#define HUGE_CAPACITY 30000
#define _INFINITY 32000
#define MAX 11
#define MAXNODES MAX * MAX * 2
#define DIM 2

const char Infile[] = "magic.in";
const char Outfile[] = "magic.out";

typedef struct node {
        int info;
        node *next;
} NODE, *PNODE;

PNODE head, tail;
int graph[MAX][MAX][DIM], type[MAX][MAX], m, n, number;
int c[MAXNODES][MAXNODES], f[MAXNODES][MAXNODES], source, sink, flowvalue;
int t[MAXNODES], seen[MAXNODES], r[MAXNODES];

void ReadData();
void BuildGraph();
void Add(int nr);
void Remove();
void Solve();
void BreadthFirstSearch();
void Print();
inline int Abs(int value);
inline int Good(int i, int j);
inline int NodeNumber(int i, int j);

int main()
{
        ReadData();
        BuildGraph();
        Solve();
        Print();

        return 0;
}

void ReadData()
{
        ifstream fin(Infile);

        int i = 0, j = 0;
        char ch = NULL;

        fin >> m >> n;

        for ( i = 1; i <= m; i++ )
            for ( j = 1; j <= n; j++ )
            {
                fin >> ch;
                if ( ch == '.' ) type[i][j] = 1;
                     else if ( ch == '*' ) type[i][j] = 2;
                          else if ( ch == 'M' ) type[i][j] = -1;
                               else if ( ch == 'T' ) type[i][j] = -2;
            }

        fin.close();
}

void Add(int nr)
{
        if ( !head )
        {
                head = new NODE;
                head->info = nr;
                head->next = NULL;
                tail = head;
        }
        else
        {
                PNODE p = new NODE;
                p->info = nr;
                p->next = NULL;
                tail->next = p;
                tail = p;
        }
}

void Remove()
{
        PNODE p = head;
        head = head->next;
        delete p;
}

void BuildGraph()
{
        int i = 0, j = 0, cnode = 0;

        for ( i = 1; i <= m; i++ )
            for ( j = 1; j <= n; j++ )
                if ( type[i][j] == 2 )
                {
                   graph[i][j][0] = ++number;
                   graph[i][j][1] = ++number;
				   c[graph[i][j][0]][graph[i][j][1]] = 1;
				   c[graph[i][j][1]][graph[i][j][0]] = 1;
                }
                else if ( type[i][j] )
                {
                        graph[i][j][0] = ++number;
                        if ( type[i][j] == -1 ) source = number;
                           else if ( type[i][j] == -2 ) sink = number;
                }

        for ( i = 1; i <= m; i++ )
            for ( j = 1; j <= n; j++ )
            {
                if ( type[i][j] == 2 )
                        cnode = graph[i][j][1];
                else cnode = graph[i][j][0];
                if ( Good(i - 1, j) )
                   c[cnode][NodeNumber(i - 1, j)] = HUGE_CAPACITY;
                if ( Good(i + 1, j) )
                   c[cnode][NodeNumber(i + 1, j)] = HUGE_CAPACITY;
                if ( Good(i, j - 1) )
                   c[cnode][NodeNumber(i, j - 1)] = HUGE_CAPACITY;
                if ( Good(i, j + 1) )
                   c[cnode][NodeNumber(i, j + 1)] = HUGE_CAPACITY;
			}

		for ( i = 1; i <= m; i++ )
			for ( j = 1; j <= n; j++ )
				if ( type[i][j] == 2 )
				{
					c[graph[i][j][0]][graph[i][j][1]] = 1;
					c[graph[i][j][1]][graph[i][j][0]] = 1;
				}
}

void Solve()
{
        int i = 0, j = 0;

        do
        {
                memset(seen, 0, sizeof(seen));
				r[source] = _INFINITY;
                head = tail = NULL;
                Add(source);
                seen[source] = 1;
				BreadthFirstSearch();
                if ( seen[sink] )
                {
						flowvalue += r[sink];
						i = sink;
						while ( i != source )
						{
								j = Abs(t[i]);
								if ( t[i] > 0 ) f[j][i] += r[sink];
                                   else f[i][j] -= r[sink];
                                i = j;
                        }
                }
		} while ( seen[sink] );
}

void BreadthFirstSearch()
{
		int i = 0, j = 0;
		PNODE x = head;

		while ( x && !seen[sink] )
		{
				j = x->info;
				for ( i = 1; i <= number && !seen[sink]; i++ )
					if ( !seen[i] )
                    {
                        if ( c[j][i] - f[j][i] > 0 )
                        {
								seen[i] = 1;
                                t[i] = j;
                                Add(i);
                                if ( c[j][i] - f[j][i] > r[j] ) r[i] = r[j];
                                   else r[i] = c[j][i] - f[j][i];
                        }
                        if ( f[i][j] )
                        {
                                seen[i] = 1;
                                t[i] = -j;
                                Add(i);
                                if ( f[i][j] > r[j] ) r[i] = r[j];
                                   else r[i] = f[i][j];
                        }
                    }
                x = x->next;
                Remove();
        }
}

void Print()
{
        ofstream fout(Outfile);

        int i = 0, j = 0;

        fout << flowvalue << endl;

        for ( i = 1; i <= m; i++ )
            for ( j = 1; j <= n; j++ )
                if ( type[i][j] == 2 )
                   if ( f[graph[i][j][0]][graph[i][j][1]] || f[graph[i][j][1]][graph[i][j][0]] )
                      fout << i << " " << j << endl;
                      
        fout.close();
}

inline int Good(int i, int j)
{
        if ( i < 1 || j < 1 || i > m || j > n ) return 0;
        if ( !type[i][j] ) return 0;
        return 1;
}

inline int NodeNumber(int i, int j)
{
        return graph[i][j][0];
}

inline int Abs(int value)
{
        if ( value < 0 ) return -value;
        return value;
}

