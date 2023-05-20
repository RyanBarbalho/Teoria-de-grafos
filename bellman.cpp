//belman ford algorithm
#include<iostream>
#include<list>
#include<vector>
#include<limits.h>
#define inf 9999999
using namespace std;

//criar um grafo
struct Aresta{
    int origem;
    int destino;
    int peso;
};

class grafo{
    private:
        int V;
        //lista de adjacencia
        //origem e destino
        list<pair<int,int>> *adj;
    public:
        grafo(int V){
            this->V = V;
            adj = new list<pair<int,int>>[V];
        }
        void addAresta(int u, int v, int w){
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }   
        void bellmanFord(int origem)
        {
            //distance from the origin to the other vertices
            vector<int> distance(V, inf);
            //parent of each vertex
            vector<int> parent(V);
            //distance from the origin to itself
            distance[origem] = 0;
            parent[origem] = -1;
            //relax all edges V-1 times
            bool updated; //little bit more efficient
            for(int i=0; i<V - 1; i++){
                //u = origin, v = destination, w = weight
                updated = false;
                for(int u=0; u< V; u++){
                    //go through all the EDGES
                    for(auto it = adj[u].begin(); it!=adj[u].end(); it++){
                        int destination = it->first;
                        //weight of the edge
                        int weight = it->second;
                        //relax the edges
                        //check if the distance from the origin to the destination is greater than the distance from the origin to the origin + the weight of the edge
                        if(distance[destination]> distance[u] + weight  and distance[u]!=inf){
                            //update the distance
                            distance[destination] = distance[u] + weight;
                            //update the parent
                            parent[destination] = u;
                            updated = true;
                        }
                    }
                     
                }
                if(updated == false) break;
            }
            //check for negative weight cycles
            //if we see any change in the shortest path, there is a negative cycle
            //so we execute the algorithm one more time
            for(int u=0; u<V; u++){
                for(auto it = adj[u].begin(); it!=adj[u].end(); it++){
                    int destination = it->first;
                    int weight = it->second;
                    if(distance[destination]> distance[u] + weight and distance[u]!=inf){
                        cout<<"Negative weight cycle found"<<endl;
                        return;
                    }
                }
            }
            //print the shortest path
            for(int i=1 ; i<V ; i++){
                cout << i << ":"<< distance[i] << " ";
            }
            cout<<endl;
        }
};

int main(){
    int V = 6, E = 8;
    grafo g(V+1);
    cout << "--------BELLMAN-FORD-BABYY-WOOOO---------" << endl;
    cout << "-----------------------------------------" << endl;
    g.addAresta(1,2,5);
    g.addAresta(1,3,4);
    g.addAresta(1,4,2);
    g.addAresta(1,6,-1);
    g.addAresta(2,4,1);
    g.addAresta(2,5,7);
    g.addAresta(3,5,6);
    g.addAresta(4,6,1);
    
    g.bellmanFord(1);

    return 0;
}