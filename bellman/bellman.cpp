// belman ford algorithm
#include <iostream>
#include <list>
#include <vector>
#include <limits.h>
#define inf 9999999
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ostream>
#include <string.h>
using namespace std;
// criar um grafo
struct Aresta
{
    int origem;
    int destino;
    int peso;
};

class grafo
{
private:
    int V;
    // lista de adjacencia
    // origem e destino
    list<pair<int, int>> *adj;

public:
    grafo(int V)
    {
        this->V = V;
        adj = new list<pair<int, int>>[V];
    }
    // destrutor do grafo (libera memoria)
    ~grafo()
    {
        delete[] adj;
    }
    void addAresta(int u, int v, int w)
    {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    void bellmanFord(int origem, bool o, string arquivoSaida)
    {
        // distance from the origin to the other vertices
        vector<int> distance(V, inf);
        // parent of each vertex
        vector<int> parent(V);
        // distance from the origin to itself
        distance[origem] = 0;
        parent[origem] = -1;
        // relax all edges V-1 times
        bool updated; // little bit more efficient
        for (int i = 0; i < V - 1; i++)
        {
            // u = origin, v = destination, w = weight
            updated = false;
            for (int u = 0; u < V; u++)
            {
                // go through all the EDGES
                for (auto it = adj[u].begin(); it != adj[u].end(); it++)
                {
                    int destination = it->first;
                    // weight of the edge
                    int weight = it->second;
                    // relax the edges
                    // check if the distance from the origin to the destination is greater than the distance from the origin to the origin + the weight of the edge
                    if (distance[destination] > distance[u] + weight and distance[u] != inf)
                    {
                        // update the distance
                        distance[destination] = distance[u] + weight;
                        // update the parent
                        parent[destination] = u;
                        updated = true;
                    }
                }
            }
            if (updated == false)
                break;
        }
        // check for negative weight cycles
        // if we see any change in the shortest path, there is a negative cycle
        // so we execute the algorithm one more time
        for (int u = 0; u < V; u++)
        {
            for (auto it = adj[u].begin(); it != adj[u].end(); it++)
            {
                int destination = it->first;
                int weight = it->second;
                if (distance[destination] > distance[u] + weight and distance[u] != inf)
                {
                    cout << "Negative weight cycle found." << endl;
                    return;
                }
            }
        }
        ////////////////////////////// SAIDA //////////////////////////
        // print the shortest path
        if (o)
        {
            ofstream saida;
            saida.open(arquivoSaida);
            for (int i = 1; i < V; i++)
            {
                if (distance[i] == inf)
                    distance[i] = -1;

                saida << i << ":" << distance[i] << " ";
            }
            saida.close();
        }
        else
        {
            for (int i = 1; i < V; i++)
            {
                // esse verificador foi posto caso o grafo nao seja conexo
                if (distance[i] == inf)
                    distance[i] = -1;

                cout << i << ":" << distance[i] << " ";
            }
            cout << endl;
        }
    }
};

void rodaBellman(bool o, string arquivoEntrada, string arquivoSaida, int origem)
{
    int VERTEX, EDGES;
    // entrada = arquivoEntrada;
    ifstream entrada;
    entrada.open(arquivoEntrada);
    string texto;
    getline(entrada, texto);

    istringstream iss(texto);
    iss >> VERTEX >> EDGES;
    grafo g(VERTEX + 1);

    for (int i = 0; i < EDGES; i++)
    {
        int u, v, w;
        getline(entrada, texto);
        istringstream iss(texto);
        iss >> u >> v >> w;
        g.addAresta(u, v, w);
    }
    entrada.close();
    g.bellmanFord(origem, o, arquivoSaida);
}

int main(int argc, char *argv[])
{
    bool f = false;
    // o = true, se o arquivo de saida foi passado
    bool o = false;
    string arquivoEntrada = "";
    string arquivoSaida = "";

    // vertice de origem
    int origem = 1;

    // vertice de origem aqui vai ser o 1 mesmo

    if (argc - 1 == 0)
        printf("ERRO, nenhum argumento foi mandado!\n");

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
        {
            cout << "-h : mostra o help\n"
                    "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                    "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                    "-i : vértice inicial"
                 << endl;
        }
        if (argc - 1 < 2 && (!strcmp(argv[i], "-o") || !strcmp(argv[i], "-f") || !strcmp(argv[i], "-i") || !strcmp(argv[i], "-l")))
        {
            printf("ERRO, USE MAIS UM ARGUMENTO COMO DITO NO HELP (-h)\n");
            break;
        }
        if (!strcmp(argv[i], "-o"))
        {

            if (argv[i + 1] == NULL)
            {
                printf("ERRO, NAO FOI PASSADO O NOME DO ARQUIVO DE SAIDA\n"
                       "USE -h PARA AJUDA\n");
                break;
            }
            else
            {
                arquivoSaida = argv[i + 1];
                o = true;
                i++;
            }
        }
        if (!strcmp(argv[i], "-f"))
        {
            f = true;
            arquivoEntrada = argv[i + 1];
            i++;
        }
        if (!strcmp(argv[i], "-i"))
        {
            // vertice de origem = alguma coisa to integer
            origem = atoi(argv[i + 1]);
        }
    }
    if (f)
    {
        rodaBellman(o, arquivoEntrada, arquivoSaida, origem);
    }
    return 0;
}
