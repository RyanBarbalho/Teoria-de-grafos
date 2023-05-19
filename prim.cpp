#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<limits.h>
using namespace std;
#define inf 9999999
//algoritmo de prim

class grafo{
    private:
        int V;
        
        list<pair<int, int>> *adj;

    public:
    //construtor
        grafo(int V){
            this->V = V+1;
            //criar a lista de adjacencia (lista de listas)
            adj = new list<pair<int, int>>[V+1];
        }
        void addAresta(int u, int v, int w){
            
            //vertice u vai para o vertice v com peso w
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }
        void primAlgorithm(int origem){
           
            //vetor que guarda os vertices que fazem parte da arvore
            vector<bool> visitado(V, false);
            visitado[origem] = true;
            //vetor que armazena o peso minimo de cada vertice
            vector<int> key(V, inf);
            //vetor que armazena o vertice pai de cada vertice
            vector<int> pai(V, -1);
            
            
            
            //fila de prioridade que seleciona a proxima aresta de menor peso
            priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> prim;
            
            int root = origem;
            key[root] = 0;
            //adiciona na fila de prioridade
                                //peso   //vertice
            prim.push(make_pair(key[root], root));

            while(!prim.empty()){
                //extrair o vertice com o menor peso(key) da fila de prioridade
                int u = prim.top().second;
                prim.pop();

                visitado[u] = true;

                //percorrer os vertices adjacentes
                list<pair<int, int>>::iterator it;
                for(it = adj[u].begin(); it !=adj[u].end(); it++){
                    int v = (*it).first;
                    int peso = (*it).second;

                    //se o vertice nao foi visitado e o peso da aresta for menor que o peso minimo do vertice
                    if(visitado[v] == false && peso < key[v]){
                        //atualiza o peso minimo do vertice
                        key[v] = peso;
                        //adiciona na fila de prioridade
                        prim.push(make_pair(key[v], v));
                        //atualiza o vertice pai
                        pai[v] = u;
                    }
                }

            }
            //printa a arvore geradora minima
            for(int i = 1; i < V; i++){
                if(pai[i] == -1) continue;
            
                cout << "aresta: " << pai[i] << " ->" << i << ", peso: " << key[i] << endl; 

            }

        }
};



int main(){
    int VERTEX, EDGES;
    cout << "--------PRIM-BABYY-WOOOO---------" << endl;
    cout << "Digite o numero de vertices e arestas: " << endl;
    cin >> VERTEX >> EDGES;
    cout << "-------------------" << endl;
    cout << VERTEX << " " << EDGES << endl;
    cout << "-------------------" << endl;
    grafo g(VERTEX);
    cout<< "insira os vertice u -> vertice v-> peso w" << endl;
    for(int i=0; i<EDGES; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addAresta(u, v, w);

    }
    cout << "-------------------" << endl;
    //vertice de origem aqui vai ser o 1 mesmo
    int origem = 1;
    g.primAlgorithm(origem);


}
