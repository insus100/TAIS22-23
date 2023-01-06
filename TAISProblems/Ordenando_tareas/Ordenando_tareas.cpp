
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque> 
using namespace std;
using Camino = deque<int>;
#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class OrdenarTareas {
public:
	OrdenarTareas(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
    }

	deque<int> const& orden() const {
        return _orden;
    }
    bool hayCiclo() const {
        return hayciclo;
    }

private:
    vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    vector<int> ant; // ant[v] = vértice anterior en el camino a v
    vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    Camino _ciclo; // ciclo dirigido (vacío si no existe)
    bool hayciclo;
	deque<int> _orden;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
         // se recupera retrocediendo
                hayciclo = true;
                for (int x = v; x != w; x = ant[x])
                    _ciclo.push_front(x);
                _ciclo.push_front(w); _ciclo.push_front(v);
            }
        }
        _orden.push_front(v + 1);
        apilado[v] = false;
    }
};
bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(N);
    int v1, v2;
    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2;
        g.ponArista(v1 - 1, v2 - 1);
    }
    // resolver el caso posiblemente llamando a otras funciones
    OrdenarTareas t(g);
    deque<int> sol = t.orden();
    if (t.hayCiclo()) {
        cout << "Imposible\n";
    }
    else {
        while (!sol.empty()) {
            cout << sol.front() << " ";
            sol.pop_front();
        }
        cout << "\n";
    }
    // escribir la solución

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
