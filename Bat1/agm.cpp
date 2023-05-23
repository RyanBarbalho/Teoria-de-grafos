#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 1)
		return 1;

	cout << "As arestas pertencem ao grafo? ";
	ifstream arquivo;
	arquivo.open(argv[1]);
	int n; // qnt vértices
	int m; // qnt arestas


	arquivo >> n >> m;

	/* cout << "Qnt vertices " << n << endl; */
	/* cout << "Qnt arestas " << m << endl; */
	vector<vector<int> > adj(n);

	for(int i =0; i<n; ++i)
		adj[i] = vector<int>();


	for(int i=0; i<m; ++i)
	{
		int v1, v2, p;
		arquivo >> v1 >> v2 >> p;
		adj[v1-1].push_back(v2-1);
		adj[v2-1].push_back(v1-1);
	}



	int custo = 0;
	for(int i=0; i<m; ++i)
	{
		int v1, v2, p;
		cin >> v1 >> v2;
		bool eh_aresta = false;
		for(auto i : adj[v1-1])
			if(i == (v2-1) )
			{
				eh_aresta = true;
				break;
			}


		if( not eh_aresta)
		{
			cout << "\nNão é aresta " << v1 << " " << v2<< "\n";
			return 1;
		}
	}


	return 0;

}
