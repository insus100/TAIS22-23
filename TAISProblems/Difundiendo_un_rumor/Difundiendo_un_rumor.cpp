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
  * Puesto: 16 lab 1
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;
#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Creamos una clase auxiliar (MinimoSoborno) para hacer las llamadas recursivas a la función dfs que nos hará el recorrido en profundidad del grafo para
 ir mirando cuál es el menor soborno para cada componente conexa del grafo. Si una componente conexa solo tiene un vértice entonces se suma
 el precio del soborno de ese vértice (no tiene amigos).
 El coste de la funcion que resuelve el problema "getSobornoMinimo" es O(V*(V+A)), el coste de DFS es V+A
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct Habitante {
    bool sabeRumor;
    int soborno;
};

class MinimoSoborno {
private:
    vector<bool> visit;
    int sobornoMin = INT_MAX;
    int V, A;
    int dfs(Grafo const& G, int v) {
        visit[v] = true;
        if (habitantes[v].soborno < sobornoMin) {
            sobornoMin = habitantes[v].soborno;
        }
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                dfs(G, w);
            }
        }
        return sobornoMin;
    }

public:
    vector<Habitante> habitantes;
    MinimoSoborno(Grafo const& G) : visit(G.V(), false), sobornoMin(INT_MAX), habitantes(G.V(), {false, 0}) {
        
    }
    int getSobornoMinimo(Grafo const& G) {
        int total = 0;
        for (int v = 0; v < G.V(); v++) {
            if (!visit[v]) {
                total += dfs(G, v);
                sobornoMin = INT_MAX;
            }
        }
        return total;
    }
};

bool resuelveCaso() {

    // leemos la entrada
    int N, M;
    cin >> N >> M;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    Grafo g(N);
    MinimoSoborno ms(g);
    
    for (int i = 0; i < N; i++) {
        int oro;
        cin >> oro;
        //Habitante h(oro);
        ms.habitantes[i] = {false, oro};
    }

    for (int i = 0; i < M; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--;
        g.ponArista(v1, v2);
    }

    cout << ms.getSobornoMinimo(g) << "\n";

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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
