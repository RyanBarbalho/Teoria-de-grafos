#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ostream>
#include <string.h>

using namespace std;
#define inf 9999999
// algoritmo de kruskal

struct aresta
{
    int origem;
    int destino;
    int peso;
};

class grafo
{
private:
    // V = numero de vertices
    int V;
    // lista de adjacencia
    list<pair<int, int>> *adj;

public:
    // construtor
    grafo(int V)
    {
        this->V = V;
        // criar a lista de adjacencia (lista de listas)
        // o pair = vertice, peso
        adj = new list<pair<int, int>>[V];
    }
    void addAresta(int u, int v, int w)
    {
        // vertice u vai para o vertice v com peso w

        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    // union-find
    int find(int u, vector<int> &pai)
    {
        if (pai[u] != u)
        {
            return find(pai[u], pai);
        }
        else
        {
            return u;
        }
    }
    // possivel conserto de find
    //  int find(int u, vector<int> &pai){
    //      if (pai[u] != u){
    //          return find(pai[u], pai);
    //      }
    //      else{
    //          return u;
    //      }
    //  }

    // union
    void uniao(int u, int v, vector<int> &pai, vector<int> &rank)
    {
        int origem = find(u, pai);
        int destino = find(v, pai);

        // faz a união por rank
        if (rank[origem] >= rank[destino])
        {
            pai[destino] = origem;
            if (rank[origem] == rank[destino])
            {
                rank[origem]++;
            }
        }
        else
        {
            pai[origem] = destino;
        }
    }
    static bool comparacao(const aresta &a, const aresta &b)
    {
        return a.peso < b.peso;
    }

    // kruskall

    static bool comparacaoSaida(const aresta &a, const aresta &b)
    {
        if (a.origem == b.origem)
            return a.destino < b.destino;
        else
            return a.origem < b.origem;
    }

    void kruskall(string arquivoEntrada, string arquivoSaida, bool s, bool o)
    {
        // vetor que guarda os vertices que fazem parte da arvore
        //  T = {}
        vector<aresta> agm; // agm = T
        // vetor de arestas que serao ordenadas por peso
        vector<aresta> arestas;
        //(make_set)
        // vetor que armazena o vertice pai de cada vertice
        vector<int> pai(V);
        // vetor que armazena o rank de cada vertice
        vector<int> rank(V, 0);

        int pesoTotal = 0;
        // criar vetor com todas as arestas e pesos
        //  i representa cada vertice
        for (int i = 0; i < V; i++)
        {
            for (auto it = adj[i].begin(); it != adj[i].end(); it++)
            {
                int dst = (*it).first;
                int pso = (*it).second;
                // evitar que duplique as arestas
                if (dst < i)
                {
                    continue;
                }
                aresta a;
                a.origem = i;
                a.destino = dst;
                a.peso = pso;
                arestas.push_back(a);
            }
        }
        // ordenar as arestas em ordem crescente em relaçao ao peso
        sort(arestas.begin(), arestas.end(), comparacao);
        // make set pai
        for (int i = 0; i < arestas.size(); i++)
        {
            pai[i] = i;
            // rank ja esta definido 0 para todos
        }

        // arvore geradora minima
        // percorre todas as aresta com o peso sorteado (ordem crescente)
        for (int i = 0; i < arestas.size(); i++)
        {
            int u = arestas[i].origem;
            int v = arestas[i].destino;
            // se os vertices u e v nao estao na mesma arvore
            if (find(u, pai) != find(v, pai))
            {
                // adiciona a aresta na arvore
                // T = T U {(u,v)}
                agm.push_back(arestas[i]);
                uniao(u, v, pai, rank);
            }
        }
        sort(agm.begin(), agm.end(), comparacaoSaida);

        for (int i = 0; i < agm.size(); i++)
        {
            pesoTotal += agm[i].peso;
        }
        // sort do agm

        // printar o agm
        if (s)
        {
            if (o)
            {
                ofstream saida;
                // abre o arquivo de saida e escreve dentro dele
                saida.open(arquivoSaida);
                for (int i = 0; i < agm.size(); i++)
                {
                    saida << "(" << agm[i].origem << "," << agm[i].destino << ") ";
                }
                saida.close();
            }
            else
            {
                for (int i = 0; i < agm.size(); i++)
                {
                    cout << "(" << agm[i].origem << "," << agm[i].destino << ") ";
                }
                cout << endl;
            }
        }
        else
        {
            if (o)
            {
                ofstream saida;
                // abre o arquivo de saida e escreve dentro dele
                saida.open(arquivoSaida);
                saida << pesoTotal;
                saida.close();
            }
            else
            {
                cout << pesoTotal << endl;
            }
        }
    }
};

void rodaKruskal(bool s, bool o, string arquivoEntrada, string arquivoSaida)
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
    grafo g(VERTEX + 1);
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
    g.kruskall(arquivoEntrada, arquivoSaida, s, o);
}

// argc = numero de argumentos, argv = argumentos
int main(int argc, char *argv[])
{
    bool s = false;
    bool f = false;
    // o = true, se o arquivo de saida foi passado
    bool o = false;
    string arquivoEntrada = "";
    string arquivoSaida = "";

    // vertice de origem aqui vai ser o 1 mesmo

    if (argc - 1 == 0)
        printf("ERRO, nenhum argumento foi mandado!\n");

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h"))
            cout << "-h : mostra o help\n"
                    "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                    "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                    "-s : mostra a solução (em ordem crescente)\n"
                 << endl;
        if (!strcmp(argv[i], "-s"))
        {
            s = true;
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
    }
    if (f)
    {
        rodaKruskal(s, o, arquivoEntrada, arquivoSaida);
    }
    return 0;
}
