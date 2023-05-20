#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<limits.h>
#include<algorithm>

using namespace std;
#define inf 9999999
//algoritmo de kruskal

struct aresta{
    int origem;
    int destino;
    int peso;
};

class grafo{
    private:
        //V = numero de vertices
        int V;
        //lista de adjacencia
        list<pair<int, int>> *adj;
        

    public:
    //construtor
        grafo(int V){
            this->V = V;
            //criar a lista de adjacencia (lista de listas) 
            //o pair = vertice, peso
            adj = new list<pair<int, int>>[V];    
        }
        void addAresta(int u, int v, int w){
            //vertice u vai para o vertice v com peso w
            adj[u].push_back(make_pair(v, w));
        }

        //union-find
        int find(int u, vector<int> &pai){
            if (pai[u] != u){
                return find(pai[u], pai);
            }
            else{
                return pai[u];
            }
        }
        //union
        void uniao(int u, int v, vector<int> &pai, vector<int> &rank){
            int origem = find(u, pai);
            int destino = find(v, pai);

            //faz a união por rank
            if(rank[origem] >= rank[destino]){
                pai[destino] = origem;
                if(rank[origem] == rank[destino]){
                    rank[origem]++;
                }
            }else{
                pai[origem] = destino;
            }
            
        }
        void make_set(int x, vector<int> &pai, vector<int> &rank)
        {
            pai[x] = x;
            rank[x] = 0;
        }
        static bool comparacao(const aresta& a, const aresta& b){
            return a.peso < b.peso;
        }

        //kruskall
        vector<aresta> kruskall(){   
            //vetor que guarda os vertices que fazem parte da arvore
            // T = {}
            vector<aresta> agm; // agm = T
            //vetor de arestas que serao ordenadas por peso
            vector<aresta> arestas; 
            //vetor que armazena o vertice pai de cada vertice
            vector<int> pai(V);
            //vetor que armazena o rank de cada vertice
            vector<int> rank(V,0);
            
            //criar vetor com todas as arestas e pesos
            for(int i = 0; i< V; i++){
                for(auto it = adj[i].begin(); it != adj[i].end(); it++){
                    int dst = (*it).first;
                    int pso = (*it).second;
                    //se o vertice destino for maior que o vertice origem
                    if(i < dst){
                        aresta a;
                        a.destino = dst;
                        a.peso = pso;
                        a.origem = i+1;
                        arestas.push_back(a);
                        cout << arestas[i].origem << " " << arestas[i].destino << " "
                        << arestas[i].peso << endl;
                    }
                }
            }
            //ordenar as arestas em ordem crescente em relaçao ao peso
            
            sort(arestas.begin(),arestas.end(), comparacao);
        
            //inicializa o vetor pai com -1 em todas as posiçoes
            //make_set
            for(int i=1; i<V; i++){
                make_set(i, pai, rank);
            }
        
            
            //arvore geradora minima
            //percorre todas as aresta com o peso sorteado (ordem crescente)
            for (int i = 0; i< arestas.size(); i++){
                int u = arestas[i].origem;
                int v = arestas[i].destino;
                //se os vertices u e v nao estao na mesma arvore
                if(find(u, pai) != find(v, pai)){
                    //adiciona a aresta na arvore
                    //T = T U {(u,v)}
                    agm.push_back(arestas[i]);
                    uniao(u, v, pai, rank);
                    
                }
            }
            cout << "cabou kruskall" << endl;
            return agm;

        }



};

int main(){
    int VERTEX, EDGES;
    cout << "--------KRUSKAL-BABYY-WOOOO---------" << endl;
    cout << "Digite o numero de vertices e arestas: " << endl;
    cin >> VERTEX >> EDGES;
    cout << "-------------------" << endl;
    grafo g(VERTEX);
    
    cout<< "insira os vertice u -> vertice v-> peso w" << endl;
    for(int i=0; i<EDGES; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addAresta(u, v, w);
        g.addAresta(v, u, w);
        cout << "-------------------" << endl;
    
    }
    cout << "-------------------" << endl;
    vector<aresta> agm = g.kruskall();

    cout<< "saida kruskall " << endl;
    for (int i=0; i< VERTEX ; i++){
        cout << "(" << agm[i].origem << " - " << agm[i].destino << ") ";
    }
    cout << endl;
}


