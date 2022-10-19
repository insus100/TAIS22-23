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
  * Puesto 0116
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <climits>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Utilizamos el algoritmo de Kruskal con un grafo valorado no dirigido para sacar el ARM.
 Hemos modificado el algoritmo de Kruskal en el constructor de la clase GrafoAeropuerto para que solo una o construya una carretera si el coste de esta es menor que el del aeropuerto.
 El tamaño del conjunto de conjuntos disjuntos final será el número de componentes conexas del grafo es decir el numero de aeropuertos a construir.
 El coste en tiempo del algoritmo de Kruskal O(AlogA) y el coste en espacio de orden O(A), siendo A el numero de aristas del grafo valorado.
 Se construye una cola de prioridad con A elementos que son las aristas, y se realiza la operación pop (coste O(logA)) A veces.
 El resto de métodos tienen coste O(1) pues solo devuelven un valor almacenado en memoria.
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>
const int INFINITO = INT_MAX;

template <typename Valor>
class GrafoAeropuerto {
public:
    //coste en tiempo O(AlogA) siendo A el numero de aristas del grafo valorado, y coste en espacio de O(A)
    GrafoAeropuerto(GrafoValorado<int> g, int A) : coste(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            Arista<Valor> a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w) && a.valor() < A) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        conjuntos = cjtos.num_cjtos();
    }

    Valor costeARM() const {
        return coste;
    }
    int getConjuntos() {
        return conjuntos;
    }
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    int conjuntos;
};

bool resuelveCaso() {

    // leemos la entrada
    int N, M, A;
    cin >> N >> M >> A;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    int x, y, c;
    GrafoValorado<int> g(N);
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> c;
        x--;
        y--;
        g.ponArista({x, y, c});
    }
    GrafoAeropuerto<int>ga(g, A);
    int aeropuertos = ga.getConjuntos();
    cout << ga.costeARM() + A * aeropuertos << " " << aeropuertos << "\n";

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
