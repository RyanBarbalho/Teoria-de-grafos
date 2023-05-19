#include<iostream>
#include<list>
#include<queue>
#include<vector>
#include<limits.h>
#define inf 9999999
using namespace std;

//criar um grafo
class Grafo{
    private:
        //V = numero de vertices
        int V;
        //lista de adjacencia
        list<pair<int, int>> *adj;

    public:
        Grafo(int V){
            this->V = V+1;
            //criar a lista de adjacencia (lista de listas) 
            //o pair = vertice, peso
            adj = new list<pair<int, int>>[V+1];
        }

        //adicionar aresta
        //u = vertice de origem, v = vertice de destino, w = peso
        void addAresta(int u, int v, int w){
            //vertice u vai para o vertice v com peso w
            adj[u].push_back(make_pair(v, w));
            //vertice v vai para o vertice u com peso w
        }
        //dijkstra vai printar cada vertice e seu custo a partir da origem
        int dijkstra(int origem, int destino){
            //vetor de distancias onde tudo começa com valor infinito
            vector<int> distancia;
            //vetores visitados 
            vector<bool> visitado;

            //fila de prioridade           
            priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> filaPrioriMin;
            
            //vetores de distancai = infinito, distancai origem = 0, visitado = false
            for(int i =0; i < V; i++){
                visitado.push_back(false);
                distancia.push_back(inf);
            }
            distancia[origem] = 0;

            //adiciona na fila de prioridade 
            //                                   distancia, vertice
            filaPrioriMin.push(make_pair(distancia[origem], origem));

            while(!filaPrioriMin.empty()){
                //extrir o vertice do topo
                int u = filaPrioriMin.top().second;
                filaPrioriMin.pop();

                //marcar como visitado
                if(visitado[u] == false){
                    visitado[u] = true;

                    //percorrer os vertices adjacentes
                    list<pair<int, int>>::iterator it;

                    //percorre a lista de adjacencia
                    for(it = adj[u].begin(); it != adj[u].end(); it++){
                        //pega o vertice adjacente e o peso
                        int v = (*it).first;
                        int peso = (*it).second;

                        //relaxamento
                        if(distancia[v] > distancia[u] + peso){
                            //atualiza a distancia
                            distancia[v] = distancia[u] + peso;
                            //adiciona na fila de prioridade
                            filaPrioriMin.push(make_pair(distancia[v], v));
                            

                        }
                    }
                }
            }

            //printa a distancia de cada vertic
            return distancia[destino];
        }
};

int main(){
    int VERTEX, EDGES;
    cout << "--------DJKSTRA-BABYY-WOOOO---------" << endl;
    cout << "Digite o numero de vertices e arestas: " << endl;
    cin >> VERTEX >> EDGES;
    cout << "-------------------" << endl;
    cout << VERTEX << " " << EDGES << endl;
    cout << "-------------------" << endl;
    Grafo g(VERTEX);
    cout<< "insira os vertice u -> vertice v-> peso w" << endl;
    for(int i=0; i<EDGES; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g.addAresta(u, v, w);

    }
    for (int i=1; i<= VERTEX; i++){
        //printar o resultado do dijkstra
        cout<< "Distancia do vertice 1 ao vertice " << i << ": ";
        cout << g.dijkstra(1, i) << endl;
    }

    return 0;
}
