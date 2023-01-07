
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
class Navegar {
public:
	Navegar(DigrafoValorado<Valor> const& g, vector<int> const& tiempos_carga, int orig = 0) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), tiempos_carga(tiempos_carga) {
		dist[origen] = tiempos_carga[origen];
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}
	bool hayCamino(int v) const { return dist[v] != INF; }
	int distancia(int v) const { return dist[v]; }
private:
	const Valor INF = numeric_limits<Valor>::max();
	int origen;
	vector<Valor> dist;
	vector<Valor> tiempos_carga;
	vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor() + tiempos_carga[w]) {
			dist[w] = dist[v] + a.valor() + tiempos_carga[w]; ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};
bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;
	if (N == 0)
		return false;

	vector<int> tiempos_carga(N);
	for (int i = 0; i < N; i++) {
		cin >> tiempos_carga[i];
	}

	int M, v1, v2, valor;
	cin >> M;
	DigrafoValorado<int> g(N);
	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2 >> valor;
		g.ponArista({ v1 - 1, v2 - 1, valor });
	}
	// resolver el caso posiblemente llamando a otras funciones
	Navegar<int> n(g, tiempos_carga, 0);

	// escribir la solución
	if(n.hayCamino(N-1)){
		cout << n.distancia(N - 1) << "\n";
	}else{
		cout << "IMPOSIBLE\n";
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
