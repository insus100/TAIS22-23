
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class MaximaCompConexa {
public:
    MaximaCompConexa(Grafo const& g) : visit(g.V(), false), maxim(0) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) { // se recorre una nueva componente conexa
                int tam = dfs(g, v);
                maxim = max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const {
        return maxim;
    }
private:
    vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int maxim; // tamaño de la componente mayor
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

void resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;//N es el numero de personas que viven en la ciudad, M los pares de amigos.

    Grafo g(N);//grafo con N vertices.
    for (int i = 0; i < M; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g.ponArista(v1 - 1, v2 - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    MaximaCompConexa mcc(g);
    // escribir la solución
    cout << mcc.maximo() << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
