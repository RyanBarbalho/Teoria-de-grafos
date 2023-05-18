//algoritmo de prim que printa um unico valor que é a soma de todas as 
//arestas que compoem a arvore geradora minima
#include<bits/stdc++.h>
#include <vector>
using namespace std;

//v = numero de vertices, E = numero de arestas
int V, E;
void montargrafo(vector<vector<pair<int,int>>> grafo, int E){
    for(int i = 0; i < E; i++){
        //vertice U vai para o vertice V que tem peso W
        int u, v, custo;
        cin >> u >> v >> custo;
        
        //vertice, peso
        grafo[u].push_back({v,custo});
            //aresta do v para o u com custo x
        grafo[v].push_back({u,custo});
    }
}

void prim(){
    
    vector<vector<pair<int,int>>> grafo(V);
    //exemplo -> grafo(0) -> (1,25), (2,10)
    //lista de adjacencia
    
    //montar o grafo
    for(int i = 0; i < E; i++){
        //vertice U vai para o vertice V que tem peso W
        int u, v, custo;
        cin >> u >> v >> custo;
        
        //vertice, peso
        grafo[u].push_back({v,custo});
            //aresta do v para o u com custo x
        grafo[v].push_back({u,custo});
    }
    ////////////////////////////////////////////////////////////////////////   
        //fila de prioridade
        priority_queue<pair<int,int>> prim;
        //marcador se visitei ou nao
        vector<bool> visitado(V, false);
        //marco o primeiro como visitado
        visitado[0] = true;
        //edge = menor aresta
        //adicionei todas as arestas que saem do vertice 0
        for(pair<int,int> edge: grafo[0]){
            //adiciono custo negativo primeiro e depois coloco a aresta
            //pois o maior negativo vai ser o menor positivo
            prim.push({-edge.second, edge.first});
        }
        
        
        int soma = 0;
        //enquanto prim nao for vazio
        //vou pegar a menor aresta e ir para o vertice no qual nao visitei
        while(prim.size()){
            //pego a menor aresta da fila de prioridade
            pair<int,int> edge = prim.top();
            prim.pop();
            //se o vertice foi visitado ignoro
            if(visitado[edge.second]) continue;

            //se nao foi visitado, visito e adiciono o custo
            soma = soma + (-edge.first);

            visitado[edge.second] = true;
            for(pair<int,int> edge: grafo[edge.second]){
                prim.push({-edge.second, edge.first});
                //adicionar as arestas dele no prim
            }
        }

        cout << soma << endl;

    }

int prim(){ //enquanto fizer leitura e v nao é falso
//montar o grafo
       
    cin >> V >> E;
    pinto();


    return 0;
}