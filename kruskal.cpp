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
            for(const auto& edge: adj[u]){
                if(edge.first == v){
                    return;
                }
            }
            adj[u].push_back(make_pair(v, w));
        }

        //union-find
        int find(int u, vector<int> &pai){
        if (pai[u] != u){
            return find(pai[u], pai);
        }
        else{
            return u;
        }
        }
        //possivel conserto de find
        // int find(int u, vector<int> &pai){
        //     if (pai[u] != u){
        //         return find(pai[u], pai);
        //     }
        //     else{
        //         return u;
        //     }
        // }
        
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
            //(make_set)
            //vetor que armazena o vertice pai de cada vertice
            vector<int> pai(V);
            //vetor que armazena o rank de cada vertice
            vector<int> rank(V,0);
            
            //criar vetor com todas as arestas e pesos
            // i representa cada vertice
            cout<< "arestas: " << endl;
            for(int i = 0; i< V; i++){
                for(auto it = adj[i].begin(); it != adj[i].end(); it++){
                    int dst = (*it).first;
                    int pso = (*it).second;
                    //evitar que duplique as arestas
                    if(dst < i){
                        continue;
                    }
                    aresta a;
                    a.origem = i;
                    a.destino = dst;
                    a.peso = pso;
                    arestas.push_back(a);
                }
            }
            //ordenar as arestas em ordem crescente em relaçao ao peso
            
            //make set pai
            for (int i=0; i<arestas.size(); i++){
                pai[i] = i;
                //rank ja esta definido 0 para todos
            }

            sort(arestas.begin(),arestas.end(), comparacao);
              
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
            return agm;

        }



};

int main(){
    int VERTEX, EDGES;
    cout << "--------KRUSKAL-BABYY-WOOOO---------" << endl;
    cout << "Digite o numero de vertices e arestas: " << endl;
    cin >> VERTEX >> EDGES;
    cout << "-------------------" << endl;
    //vertex + 1 pq começa por 1, nao 0.
    grafo g(VERTEX+1);
    
    cout<< "insira os vertice u -> vertice v-> peso w" << endl;
    for(int i=0; i<EDGES; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addAresta(u, v, w);
        g.addAresta(v, u, w);
    
    }
    cout << "-------------------" << endl;
    vector<aresta> agm = g.kruskall();

    cout<< "saida kruskall " << endl;
    for (const auto& aresta : agm){
        cout << "(" << aresta.origem << " - " << aresta.destino << ") ";
    }
    cout << endl;
}

