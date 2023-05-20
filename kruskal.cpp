#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<limits.h>
using namespace std;
#define inf 9999999
//algoritmo de kruskal
class grafo{
    private:
        //V = numero de vertices
        int V;
        //lista de adjacencia
        list<pair<int, int>> *adj;
        //vetor que armazena o vertice pai de cada vertice
        vector<int> pai;
        //vetor que armazena o rank de cada vertice
        vector<int> rank;

    public:
    //construtor
        grafo(int V){
            this->V = V+1;
            //criar a lista de adjacencia (lista de listas) 
            //o pair = vertice, peso
            adj = new list<pair<int, int>>[V+1];    
            //criar o vetor pai com -1 em todas as posiçoes
            pai.resize(V+1);
            rank.resize(V+1);
        }
        void addAresta(int u, int v, int w){
            //vertice u vai para o vertice v com peso w
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }

        //union-find
        int find(int u){
            if(pai[u] == -1){
                return u;
            }
            return find(pai[u]);
        }
        //union
        void uniao(int u, int v){
            int u_set = find(u);
            int v_set = find(v);
            pai[u_set] = v_set;
        }
        void make_set(int x)
        {
            pai[x] = x;
            rank[x] = 0;
        }
        bool comparacao(pair<int, pair<int,int>> a, pair<int, pair<int,int>> b){
            return (a.first < b.first);
        }

        //kruskall
        void kruskall(int origem){   
            //vetor que guarda os vertices que fazem parte da arvore
            // T = {}
            vector<pair<int, pair<int,int>>> arestas; // T

            //criar lista com todas as arestas e pesos
            for(int u = 1; u< V; u++){
                for(const auto& vizinho : adj[u]){
                    int v = vizinho.first;
                    int peso = vizinho.second;
                    arestas.push_back(make_pair(peso,make_pair(u ,v )));

                }
            }
            //ordenar as arestas em ordem crescente em relaçao ao peso
            sort(arestas.begin(),arestas.end(), comparacao(arestas. ));
            

            //inicializa o vetor pai com -1 em todas as posiçoes
            for(int i=1; i<V; i++){
                make_set(i);
            }
        
            int pesoTotal = 0;
            //arvore geradora minima
            vector<pair<int,int>> agm;
            
            //percorre todas as aresta com o peso sorteado
            for (auto it = arestas.begin(); it != arestas.end(); ++it){
                int u = it->second.first;
                int v = it->second.second;
                int peso = it->first;
                //se os vertices u e v nao estao na mesma arvore
                if(find(u) != find(v)){
                    //adiciona a aresta na arvore
                    //T = T U {(u,v)}
                    uniao(u, v);
                    pesoTotal += peso;
                }
            }

            




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
        g.addAresta(u, v, w, g.pai);

    }
    cout << "-------------------" << endl;
}


