
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Camion {
public:
    Camion(GrafoValorado<int> const& g, int const& ini, int const& fin, int const& anchura) : visit(g.V(), false), anchuraCamion(anchura), fin(fin) {
        dfs(g, ini);
    }
    bool getFin(){
        return visit[fin];
    }
private:
    vector<bool> visit;
    int anchuraCamion;
    int fin;
    void dfs(GrafoValorado<int> const& G, int const &v) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= anchuraCamion) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(G, w);
            }
        }
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int V, E;
    cin >> V >> E;
    if (!std::cin)  // fin de la entrada
        return false;
    GrafoValorado<int> g(V);
    int v1, v2, valor;
    for (int i = 0; i < E; i++) {
        cin >> v1 >> v2 >> valor;
        g.ponArista({ v1 - 1 , v2 - 1, valor });
    }
    int k, origen, dest, anchura;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> origen >> dest >> anchura;
        Camion c(g, origen-1, dest-1, anchura);
        c.getFin() ? cout << "SI\n" : cout << "NO\n";
    }

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
