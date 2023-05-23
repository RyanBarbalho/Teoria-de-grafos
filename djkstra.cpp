#include <iostream>
#include <list>
#include <queue>
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
class Grafo
{
private:
    // V = numero de vertices
    int V;

    // lista de adjacencia
    list<pair<int, int>> *adj;

public:
    Grafo(int V)
    {
        this->V = V + 1;
        // criar a lista de adjacencia (lista de listas)
        // o pair = vertice, peso
        adj = new list<pair<int, int>>[V + 1];
    }
    // destrutor do grafo (libera memoria)
    ~Grafo()
    {
        delete[] adj;
    }

    // adicionar aresta
    // u = vertice de origem, v = vertice de destino, w = peso
    void addAresta(int u, int v, int w)
    {
        // vertice u vai para o vertice v com peso w
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
        // vertice v vai para o vertice u com peso w
    }
    // dijkstra vai printar cada vertice e seu custo a partir da origem
    void dijkstra(int origem, bool o, string arquivoSaida)
    {
        // vetor de distancias onde tudo começa com valor infinito
        vector<int> distancia(V, inf);
        // vetores visitados
        vector<bool> visitado(V, false);

        // fila de prioridade
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioriMin;

        distancia[origem] = 0;

        // adiciona na fila de prioridade
        //                                    distancia, vertice
        filaPrioriMin.push(make_pair(distancia[origem], origem));

        while (!filaPrioriMin.empty())
        {
            // extrir o vertice do topo
            int u = filaPrioriMin.top().second;
            filaPrioriMin.pop();

            // marcar como visitado
            if (visitado[u] == false)
            {
                visitado[u] = true;

                // percorrer os vertices adjacentes
                list<pair<int, int>>::iterator it;

                // percorre a lista de adjacencia
                for (it = adj[u].begin(); it != adj[u].end(); it++)
                {
                    // pega o vertice adjacente e o peso
                    int v = (*it).first;
                    int peso = (*it).second;

                    // relaxamento
                    if (distancia[v] > distancia[u] + peso)
                    {
                        // atualiza a distancia
                        distancia[v] = distancia[u] + peso;
                        // adiciona na fila de prioridade
                        filaPrioriMin.push(make_pair(distancia[v], v));
                    }
                }
            }
        }

        // printa a distancia de cada vertice

        if (o)
        {
            ofstream saida;
            // abre o arquivo de saida e escreve dentro dele
            saida.open(arquivoSaida);
            for (int i = 1; i < distancia.size(); i++)
            {
                if (distancia[i] == inf)
                    distancia[i] = -1;
                saida << i << ":" << distancia[i] << " ";
            }
            saida.close();
        }
        else
        {
            for (int i = 1; i < distancia.size(); i++)
            {
                if (distancia[i] == inf)
                    distancia[i] = -1;
                cout << i << ":" << distancia[i] << " ";
            }
            cout << endl;
        }
    }
};

void rodaDijkstra(bool o, string arquivoEntrada, string arquivoSaida, int origem)
{
    int VERTEX, EDGES;
    ifstream entrada;
    entrada.open(arquivoEntrada);
    // cada linha do arquivo
    string texto;
    // pega a primeira linha do arquivo e bota na string texto
    getline(entrada, texto);
    // iss é um stream de strings (variavel que vai receber o texto)
    ////inteiro string string
    istringstream iss(texto);
    // vai ser o vertex e edges
    iss >> VERTEX >> EDGES;
    Grafo g(VERTEX);
    // pega cada linha do arquivo e bota na string texto
    for (int i = 0; i < EDGES; i++)
    {
        int u, v, w;
        getline(entrada, texto);
        istringstream iss(texto);
        iss >> u >> v >> w;

        g.addAresta(u, v, w);
    }
    // fechar o arquivo
    entrada.close();
    g.dijkstra(origem, o, arquivoSaida);
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
            o = true;
            arquivoSaida = argv[i + 1];
            i++;
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
        rodaDijkstra(o, arquivoEntrada, arquivoSaida, origem);
    }
    return 0;
}
