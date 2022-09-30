
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

class ArbolLibre {
private:
    vector<bool> visit;
    int visitados;
    int V, A;
    void dfs(Grafo const& G, int v) {
        visitados++;
        visit[v] = true;
        for (int w : G.ady(v))
            if (!visit[w])
                dfs(G, w);
    }

public:
    ArbolLibre(Grafo const& G) : visit(G.V(), false), visitados(0), V(G.V()), A(G.A()) {
        dfs(G, 0);
    }

    bool esArbolLibre() const {
        return (visitados == V) && (V - 1 == A);
    }
};

bool resuelveCaso() {
    
    // leer los datos de la entrada
    Grafo grafo(cin);
    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    ArbolLibre arb(grafo);
    arb.esArbolLibre() ? cout << "SI\n" : cout << "NO\n";
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
