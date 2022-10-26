/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Javier Gil Caballero TAIS42
  * Estudiante 2: Íñigo Velasco Sánchez TAIS105
  * Puesto 0109
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Hemos creado una clase auxiliar Laberinto, en su constructor inicializamos las variables privadas y ejecutamos el algoritmo de Dijkstra
 para calcular el camino mínimo desde el vértice origen (que en este caso es la salida del laberinto S) hasta el resto de vértices.
 Tiene un coste en tiempo de O(AlogV) y en espacio O(V) siendo A el número de aristas del digrafo valorado, y V el número de vértices.
 El método cuantos llegan a tiempo calcula el número de ratones que llegan al final del laberinto antes de T y tiene un coste de O(N) siendo
 N el número de aristas que recorre el ratón para llegar al final en el menor tiempo posible. 
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>
template <typename Valor>
class Laberinto {
public:
    Laberinto(DigrafoValorado<Valor> const& g, int S, int T) : origen(S), dist(g.V(), INF), ulti(g.V()), pq(g.V()), t(T), ratones(0) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (AristaDirigida<Valor> a : g.ady(v))
                relajar(a);
        }

        cuantosLleganATiempo();
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int getRatones() const { return ratones; }
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen, t;
    vector<Valor> dist;
    vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    int ratones;

    void relajar(AristaDirigida<Valor> &a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
    void cuantosLleganATiempo() {
        for (int i = 0; i < dist.size(); i++) {
            if (i != origen && dist[i] <= t) {
                ratones++;
            }
        }
    }

};


bool resuelveCaso() {

    // leemos la entrada
    int N, S, T, P;
    cin >> N >> S >> T >> P;

    if (!cin)
        return false;
    DigrafoValorado<int>dg(N);
    int v1, v2, valor;
    for (int i = 0; i < P; i++) {
        cin >> v1 >> v2 >> valor;
        v1--;
        v2--;
        dg.ponArista({ v2, v1, valor });
    }

    // leer el resto del caso y resolverlo
    Laberinto<int> l(dg, S - 1, T);
    cout << l.getRatones() << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE");
#endif
    return 0;
}
