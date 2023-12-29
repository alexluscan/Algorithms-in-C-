#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <sstream>
#include <cstring>
#include <queue>

using namespace std;

ifstream fin("file.in");
ofstream fout("file.out");

char a[251][251];
int island[251][251], n;
bool vis[251][251];
bool viz[251][251];
int mii, mij, dmi, mai, maj;

int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
int dist[251][251];

inline bool valid(int x, int y)
{
  return (x >= 0 && y >= 0 && x < n && y < n && a[x][y] == 'L' && island[x][y] == 0);
}

typedef pair<int, int> p;

p parseCoordinate(string s)
{
  istringstream iss(s);
  string coord1, coord2;
  iss >> coord1;
  iss >> coord2;
  iss = istringstream(coord1);
  getline(iss, s, ',');
  int y = stoi(s);
  getline(iss, s, ',');
  int x = stoi(s);
  return p(x, y);
}

inline void fill(int x, int y, int val)
{
  island[x][y] = val;
  for (int i = 0; i < 4; ++i)
  {
    int nx = x + dx[i], ny = y + dy[i];
    if (valid(nx, ny))
      fill(nx, ny, val);
  }
}

set<pair<int, int>> ss;
    stack<p> stv;

bool isCorner(int x, int y)
{
  return (island[x - 1][y - 1] != island[x][y] && island[x - 1][y] != island[x][y] && island[x][y - 1] != island[x][y]) ||
         (island[x + 1][y - 1] != island[x][y] && island[x - 1][y] != island[x][y] && island[x][y + 1] != island[x][y]) ||
         (island[x + 1][y - 1] != island[x][y] && island[x + 1][y] != island[x][y] && island[x][y - 1] != island[x][y]) ||
         (island[x + 1][y + 1] != island[x][y] && island[x][y + 1] != island[x][y] && island[x + 1][y] != island[x][y]);
}

inline void fill2(int x, int y)
{
  vis[x][y] = true;
  mii = min(mii, x);
  mij = min(mij, y);
  mai = max(mai, x);
  maj = max(maj, y);
  if (isCorner(x, y))
    ss.insert({x, y});
  for (int i = 0; i < 4; ++i)
  {
    int nx = x + dx[i], ny = y + dy[i];
    if (island[x][y] == island[nx][ny] && !vis[nx][ny])
      fill2(nx, ny);
  }
}

inline bool validWater(int x, int y)
{
  return (x >= 0 && y >= 0 && x < n && y < n && a[x][y] == 'W' && dist[x][y] == 0);
}

void print(int x, int y)
{
  if (dist[x][y] == 1)
    return;
  for (int i = 0; i < 8; ++i)
  {
    int nx = x + dx[i], ny = y + dy[i];
    if (dist[nx][ny] == dist[x][y] - 1)
    {
      stv.push({nx, ny});
      viz[nx][ny] = 1;
      print(nx, ny);
      break;
    }
  }
}

void BFS(int x, int y, int destx, int desty)
{
    memset(dist, 0, sizeof(dist));
  dist[x][y] = 1;
  queue<p> q;
  q.push(p(x, y));
  while (!q.empty())
  {
    p p1 = q.front();
    q.pop();
    int x1 = p1.first, y1 = p1.second;
    if (x1 == destx && y1 == desty)
      break;
    for (int i = 0; i < 8; ++i)
    {
      int nx = x1 + dx[i], ny = y1 + dy[i];
      if (validWater(nx, ny))
      {
        dist[nx][ny] = dist[x1][y1] + 1;
        q.push(p(nx, ny));
      }
    }
  }
  print(destx, desty);
  while (!stv.empty())
  {
      auto it = stv.top();
      fout << it.first << ' ' << it.second << endl;
      stv.pop();
  }
}

int main()
{
  fin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      fin >> a[i][j];

  int x, y;

  int count = 1;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (a[i][j] == 'L' && island[i][j] == 0)
      {
        fill(i, j, count);
        ++count;
      }

  string s;
  int x1, y1, x2, y2, ic[5], jc[5];
  int total;
  fin >> total;
  fin.get();
  while (total--)
  {
    getline(fin, s);
    p p1 = parseCoordinate(s);
    x1 = p1.first;
    y1 = p1.second;
    mii = mij = dmi = 100000000;
    mai = maj = -1;
    ss.clear();
    fill2(x1, y1);
    int is, js;
    is = mii;
    js = mij;
    for (auto s : ss)
    {
      int st = s.first, nd = s.second;
      if (dmi > min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd)))
      {
        dmi = min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd));
        ic[0] = st - 1;
        jc[0] = nd - 1;
      }
    }
    is = mai;
    js = mij;
    dmi = 100000000;
    for (auto s : ss)
    {
      int st = s.first, nd = s.second;
      if (dmi > min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd)))
      {
        dmi = min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd));
        ic[1] = st + 1;
        jc[1] = nd - 1;
      }
    }
    is = mai;
    js = maj;
    dmi = 100000000;
    for (auto s : ss)
    {
      int st = s.first, nd = s.second;
      if (dmi > min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd)))
      {
        dmi = min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd));
        ic[2] = st + 1;
        jc[2] = nd + 1;
      }
    }
    is = mii;
    js = maj;
    dmi = 100000000;
    for (auto s : ss)
    {
      int st = s.first, nd = s.second;
      if (dmi > min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd)))
      {
        dmi = min(abs(is - st), abs(js - nd)) + abs(abs(is - st) - abs(js - nd));
        ic[3] = st - 1;
        jc[3] = nd + 1;
      }
    }
    cout << ic[3] << ' ' << jc[3] << '\n';
    BFS(ic[0], jc[0], ic[1], jc[1]);
    BFS(ic[1], jc[1], ic[2], jc[2]);
    BFS(ic[2], jc[2], ic[3], jc[3]);
    BFS(ic[3], jc[3], ic[0], jc[0]);
      fout << endl;
  }

  return 0;
}
