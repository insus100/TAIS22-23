
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase
#define INF 1000000000 //10^9

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Juego
{
public:
    Juego(Digrafo const& g, int s) : visit(g.V(), false), dist(g.V())
    {
        bfs(g, s);
    }
    int distancia(int v) const { return dist[v]; }

private:
    std::vector<bool> visit; //visit[v] existe camino de s a v
    std::vector<int> dist;   //ant[v] distancia de s a v mas corta

    void bfs(Digrafo const& g, int s)
    {
        std::queue<int> cola;
        visit[s] = true;
        dist[s] = 0;
        cola.push(s);
        while (!cola.empty())
        {
            int v = cola.front();
            cola.pop();
            for (int w : g.ady(v))
            {
                if (!visit[w])
                {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    cola.push(w);
                }
            }
        }
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int N, K, S, E;
    cin >> N >> K >> S >> E;
    if (N == 0)
        return false;
    int casillas = N * N;
    vector<int> finAtajo(casillas + 1, -1);
    Digrafo g(casillas + 1);
    for (int i = 0; i < S + E; ++i)
    { //serpientes y escaleras
        int v, w;
        std::cin >> v >> w;
        finAtajo[v] = w;
    }
    for (int i = 1; i <= casillas; ++i)
    { //paso de casilla en casilla
        for (int j = 1; j <= K; j++)
        {
            int extremo = i + j;
            if (extremo <= casillas)
            {
                if (finAtajo[extremo] != -1)
                    g.ponArista(i, finAtajo[extremo]);
                else
                    g.ponArista(i, extremo);
            }
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    Juego Serpiente(g, 1);
    // escribir la solución
    if (g.V() == 0)
        std::cout << "1" << std::endl;
    else
        std::cout << Serpiente.distancia(casillas) << std::endl;
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
