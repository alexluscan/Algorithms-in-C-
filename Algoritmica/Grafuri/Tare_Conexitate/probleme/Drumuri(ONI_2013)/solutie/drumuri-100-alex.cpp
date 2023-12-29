#include<cstdio>
#include <fstream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

#define NMAX 150001

int N, M;
int used[NMAX];
vector<int> graph[NMAX], transpose[NMAX], dag[NMAX], transpose_dag[NMAX];
stack<int> Stack;

int num_of_scc;
int where[NMAX];
int num[NMAX];

int in[NMAX];
int out[NMAX], max_dist[NMAX];

vector<int> outer[NMAX];

void read_data(){

	ifstream fin ("drumuri.in");
	
	int x, y;

//	scanf("%d %d", &N, &M);
	fin >> N >> M;
	for(int i = 1; i <= M; i++){
//		scanf("%d %d", &x, &y);
		fin >> x >> y;
		graph[x].push_back(y);
		transpose[y].push_back(x);
	}
}

void dfs_scc(int node, int type, vector<int> *graph) {
	
	used[node] = type;
	if (type == 2) {
		where[node] = num_of_scc;
		num[num_of_scc]++;
	}

   for(vector<int>::iterator it = graph[node].begin(); it != graph[node].end(); it++) 
		if (used[*it] != type)
			dfs_scc(*it, type, graph);
	
	if (type == 1)
		Stack.push(node);
}

void compute_scc(){

	for(int i = 1; i <= N; i++)
		if (used[i] != 1) {
			dfs_scc(i, 1, graph);
		}

   for(;!Stack.empty(); Stack.pop()){
		if(used[Stack.top()] == 2) continue;
	   	num_of_scc++;
		dfs_scc(Stack.top(), 2, transpose);
	}
}

void make_dag(){
	
	compute_scc();
    
//	for(int i = 1; i <= N; i++)
//		printf("!%d %d\n", i, where[i]);

	for(int node = 1; node <= N; node++)
		for(vector<int>::iterator it = graph[node].begin(); it != graph[node].end(); it++)
			if (where[node] != where[*it]) {
				dag[ where[node] ].push_back ( where[*it] );
				in[ where[*it]  ]++;
				out[ where[node] ]++;
				transpose_dag[ where[*it] ].push_back ( where[node] );
//				printf("transpose_dag : %d %d\n", where[*it], where[node]);
   		}
}

int is_solution[NMAX];

void compute_max_dist(int N, vector<int> *graph) {
	
	int node;
	
	queue <int> Q;
	for (node = 1; node <= N; node++)
		if (out[node] == 0)
			Q.push(node);

	for(;!Q.empty(); Q.pop()) {
		node = Q.front();
		//printf("node %d\n", node);
		for(vector<int>::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
			out[*it]--;
			if (out[*it] == 0)
				Q.push(*it);
			max_dist[*it] = max(max_dist[*it], 1 + max_dist[node]);
		}
	}
}

void solve() {
	
	vector<int> solutions;
	int num = 0, dmax = -1;

	compute_max_dist(num_of_scc, transpose_dag);
	//for(int i = 1; i <= num_of_scc; i++)
		//printf("dist max : %d %d\n", i, max_dist[i]);

	for(int i = 1; i <= num_of_scc; i++)
		if (in[i] == 0){
			outer[ max_dist[i] ].push_back (i);
			num++;
			dmax = max(dmax, max_dist[i]);
		}

	for (; dmax >= 0; ) {
		//printf("num : %d dmax : %d\n", num, dmax);
	
		if (num == 1) {
			//printf("is sol %d\n", outer[dmax][0]);
			is_solution[ outer[dmax][0] ] = 1;
		}

		for(int i = 0; i < (int)outer[dmax].size(); i++) {

			int node = outer[dmax][i];
			//printf("%d ", node);
			for(vector<int>::iterator it = dag[node].begin(); it != dag[node].end(); it++) {
				//printf ("(%d) ", *it);
				in[*it]--;
				if (in[*it] == 0) {
					outer[ max_dist[*it] ].push_back(*it);
					num++;
				}
			}
			//printf("final");
		}

		num-= outer[dmax].size();
		//printf("#%d\n", dmax);
		outer[dmax].clear();
		
		while (dmax >= 0 && outer[dmax].size() == 0)
			dmax--;  
                          
	}

	for(int i = 1; i <= N; i++) {
//		printf("#%d %d\n", i, where[i]);
		if(is_solution[where[i]]) {
			solutions.push_back(i);
		}
	}

	ofstream fout ("drumuri.out"); 
/*
	for (int i = 1; i <= num_of_scc; i++)
		fout << ::num[i] << ' ';
	fout << '\n';
*/
//	printf("%d\n", solutions.size());
	fout << solutions.size() << '\n';
	for(int i = 0; i < (int)solutions.size(); i++)
//		printf("%d ", solutions[i]);
		fout << solutions[i] << ' ';
}

int main() {
	
	freopen("drumuri.in", "r", stdin);
	freopen("drumuri.out", "w", stdout);

	read_data();
	make_dag();
	solve();

	return 0;
}
