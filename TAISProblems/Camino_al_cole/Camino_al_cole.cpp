
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template <typename Valor>
class Cole {
public:
    Cole(DigrafoValorado<Valor> const& g, int orig = 0) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), num_caminos(g.V(), 0) {
        dist[origen] = 0;
        num_caminos[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }

    int getCaminosMinimos() const {
        return num_caminos[num_caminos.size() - 1];
    }

private:
    const Valor INF = numeric_limits<Valor>::max();
    int origen;
    vector<Valor> dist;
    vector<Valor> num_caminos;
    vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            //dist_min = min(dist[v], dist_min);
            pq.update(w, dist[w]);
            num_caminos[w] = num_caminos[v];
        }
        else if (dist[w] == dist[v] + a.valor()) {
            num_caminos[w] += num_caminos[v];
        }
    }
};
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;
    int v1, v2, valor;
    DigrafoValorado<int> g(N);
    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2 >> valor;
        g.ponArista({ v1 - 1, v2 - 1, valor });
        g.ponArista({ v2 - 1, v1 - 1, valor });
    }
    // resolver el caso posiblemente llamando a otras funciones

    Cole<int> c(g, 0);

    // escribir la solución
    cout << c.getCaminosMinimos() << "\n";
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
