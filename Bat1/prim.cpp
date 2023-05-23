#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ostream>
#include <string.h>

using namespace std;
#define inf 9999999
// algoritmo de prim

class grafo
{
private:
    int V;

    list<pair<int, int>> *adj;

public:
    // construtor
    grafo(int V)
    {
        this->V = V + 1;
        // criar a lista de adjacencia (lista de listas)
        adj = new list<pair<int, int>>[V + 1];
    }
    // destrutor do grafo (libera memoria)
    ~grafo()
    {
        delete[] adj;
    }
    void addAresta(int u, int v, int w)
    {
        // vertice u vai para o vertice v com peso w
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    static bool comparacaoSaida(pair<int, int> a, pair<int, int> b)
    {
        if (a.first == b.first)
            return a.second < b.second;
        else
            return a.first < b.first;
    }
    void primAlgorithm(int origem, bool s, bool o, string arquivoSaida)
    {

        // vetor que guarda os vertices que fazem parte da arvore
        vector<bool> visitado(V, false);
        visitado[origem] = true;
        // vetor que armazena o peso minimo de cada vertice
        vector<int> key(V, inf);
        // vetor que armazena o vertice pai de cada vertice
        vector<int> pai(V, -1);
        int pesoTotal = 0;

        vector<pair<int, int>> grafoSaida;

        // fila de prioridade que seleciona a proxima aresta de menor peso
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> prim;

        int root = origem;
        key[root] = 0;
        // adiciona na fila de prioridade
        // peso   //vertice
        prim.push(make_pair(key[root], root));
        while (!prim.empty())
        {
            // extrair o vertice com o menor peso(key) da fila de prioridade
            int u = prim.top().second;
            prim.pop();

            visitado[u] = true;

            // percorrer os vertices adjacentes
            list<pair<int, int>>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); it++)
            {

                int v = (*it).first;
                int peso = (*it).second;

                // se o vertice nao foi visitado e o peso da aresta for menor que o peso minimo do vertice
                if (visitado[v] == false && peso < key[v])
                {
                    // atualiza o peso minimo do vertice
                    key[v] = peso;
                    // adiciona na fila de prioridade
                    prim.push(make_pair(key[v], v));
                    // atualiza o vertice pai
                    pai[v] = u;
                }
            }
        }
        // soma todos os pesos
        for (int i = 1; i < V; i++)
        {
            pesoTotal += key[i];
        }
        for (int i = 1; i < V; i++)
        {
            if (pai[i] == -1)
                continue;
            if (pai[i] < i)
            {
                grafoSaida.push_back(make_pair(pai[i], i));
            }
            else
                grafoSaida.push_back(make_pair(i, pai[i]));
        }
        // ordena o vetor de saida
        sort(grafoSaida.begin(), grafoSaida.end(), comparacaoSaida);

        if (s)
        {
            if (o)
            {
                ofstream saida;
                // abre o arquivo de saida e escreve dentro dele
                saida.open(arquivoSaida);
                for (int i = 0; i < grafoSaida.size(); i++)
                {
                    saida << "(" << grafoSaida[i].first << "," << grafoSaida[i].second << ") ";
                }
                saida.close();
            }
            else
            {
                for (int i = 0; i < grafoSaida.size(); i++)
                {
                    cout << "(" << grafoSaida[i].first << "," << grafoSaida[i].second << ") ";
                }
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
                cout << pesoTotal << endl;
        }
    }
};

void rodaPrim(bool s, bool o, string arquivoEntrada, string arquivoSaida, int origem)
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
    grafo g(VERTEX);
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
    g.primAlgorithm(origem, s, o, arquivoSaida);
}

// argc quantidade de argumentos // argv vetor de argumentos
int main(int argc, char *argv[])
{
    bool s = false;
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
            cout << "-h : mostra o help\n"
                    "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                    "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                    "-s : mostra a solução (em ordem crescente)\n"
                    "-i : vértice inicial"
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
        if (!strcmp(argv[i], "-i"))
        {
            // vertice de origem = alguma coisa to integer
            origem = atoi(argv[i + 1]);
        }
    }
    if (f)
    {
        rodaPrim(s, o, arquivoEntrada, arquivoSaida, origem);
    }
}