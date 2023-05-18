#include <iostream>
#include<vector>
#include<queue>
using namespace std;

int main(){
    //vertices, arestas
    int V, E;
    cin >> V >> E;
    //cada vertice tem seus vizinhos e peso
    vector<vector<pair<int, int>>> G(V);

    for(int i = 0; i < E; i++){
        //vertice U vai para o vertice V que tem peso W
        int u, v, peso;
        cin >> u >> v >> peso;
        v--; u--;
        //vertice, peso
        G[u].push_back({v, peso});
    }
    //                      distancia, vertice
    //fila de prioridade
    priority_queue<pair<int, int>>djikstra; 
    //vetor de distancias onde tudo começa com valor infinito
    vector<int> distancia(V, INT16_MAX);

    distancia[0] = 0; 
    //distancia =0, vetice = 0
    //ADICIONO NA PRIORITY QUEUE
    //fila dos candidatos a serem relaxados
    djikstra.push({0, 0});
    while(djikstra.size() > 0){
        int v = djikstra.top().second;
        int custo = -djikstra.top().first;
        djikstra.pop(); 

        if(custo!= distancia[v]) continue;
        //em cada relaxamento eu olhos pros vizinhos
        for(auto edge:G[v]){
            int u= edge.first;
            int custo = edge.second;
            //quando deu consigo um caminho melhor?
            if(distancia[u] > distancia[v] + custo){

                distancia[u] = distancia[v] + custo;
                //"-" é utilizado pois a priority queue vai guardar valor positivo
                djikstra.push({-distancia[u], u});
            }

        }
    }

    for(int d: distancia){
        cout << d << " ";
    }
    cout << "\n";

    

}



//entrada
// 6 8
// 1 2 5
// 1 3 4
// 1 4 2
// 1 6 6
// 2 4 1
// 2 5 7
// 3 5 6
// 4 6 1