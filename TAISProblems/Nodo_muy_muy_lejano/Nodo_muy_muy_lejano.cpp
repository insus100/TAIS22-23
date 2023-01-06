
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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
class Consulta {
public:
	Consulta(Grafo const& g, int nodo_ini, int ttl) : visit(g.V(), false), dist(g.V(), 0), nodo_ini(nodo_ini), ttl(ttl), nodos(g.V()), nodos_alcanzados(0) {
		if (!visit[nodo_ini]) { 
			bfs(g, nodo_ini);
		}
	}

	int nodosInalcanzables() const& {
		return nodos - nodos_alcanzados - 1;
	}

private:
	vector<bool> visit;
	vector<int> dist;
	int nodos;
	int ttl;
	int nodo_ini;
	int nodos_alcanzados;

	void bfs(Grafo const& g, int nodo_ini) {
		std::queue<int> q;
		dist[nodo_ini] = 0; visit[nodo_ini] = true;
		q.push(nodo_ini);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w] && dist[v] < ttl) {
					dist[w] = dist[v] + 1; visit[w] = true;
					nodos_alcanzados++;
					q.push(w);
				}
			}
		}
	}
};


bool resuelveCaso() {

	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;

	if (!std::cin)  // fin de la entrada
		return false;
	Grafo g(N);
	int v1, v2;
	for (int i = 0; i < C; i++) {
		cin >> v1 >> v2;
		g.ponArista(v1 - 1, v2 - 1);
	}

	int num_consultas, nodo_ini, ttl;
	cin >> num_consultas;
	
	for (int i = 0; i < num_consultas; i++) {
		cin >> nodo_ini >> ttl;
		Consulta c(g, nodo_ini - 1, ttl);
		cout << c.nodosInalcanzables() << "\n";
	}
	cout << "---\n";
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
