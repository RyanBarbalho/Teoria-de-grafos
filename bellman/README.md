# Algoritmo de Bellman Ford
# sobre o algoritmo
O Algoritmo de Bellman-Ford é um algoritmo de busca de caminho mínimo em um digrafo (grafo orientado ou dirigido) ponderado, ou seja, cujas arestas têm peso, inclusive negativo. O Algoritmo de Dijkstra resolve o mesmo problema, num tempo menor, porém exige que todas as arestas tenham pesos positivos. Portanto, o algoritmo de Bellman-Ford é normalmente usado apenas quando existem arestas de peso negativo.
# como compilar algoritmo#
Para compilar a necessário executar o comando no terminal:
```ubuntu
make
```

assim, o arquivo será compilado no formato binario como bellman.bin. A fim de obter informação sobre algoritmo deve-se executar o comando:

```ubuntu
./bellman.bin -h

      "-h : mostra o help\n"
                    "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
                    "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada\n"
                    "-i : vértice inicial\n"
                    "modelo de entrada: ./bellman -f<arquivo de entrada> -o<arquivo de saida> -i<vertice inicial>\n"
```

# formato da entrada

```ubuntu
V E
v u w
. . .
. . .
. . .
vn un wn
```
V= numero de vértices, E= numero de arestas

v = vertice de origem, u = vertice de destino e w = peso da aresta

# formato da saída

O formato da saída se dará pelo caminho contendo ``v``:``u`` até o fim do caminho, contendo os vertices de origem e destino.

```ubuntu
./bellman.bin -f entrada.mtx -i 1 

    1:0 2:3 3:4 4:2 5:10 6:3
```
A fim de salvar o resultado do algoritmo em algum arquivo deve-se executar o comando:

```ubuntu
./bellman.bin -f entrada.mtx -i 1 -o saida.txt
```





