
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class CostePuente {
public:
	CostePuente(GrafoValorado<int> const& g) : visit(g.V(), false), coste(0), multiplesConjuntos(false) {
		ARM_Kruskal(g);
	}

	int costeARM() const {
		return coste;
	}
	vector<Arista<int>> const& ARM() const {
		return _ARM;
	}
	bool getMultCjtos(){
		return multiplesConjuntos;
	}
private:
	vector<bool> visit;
	int coste;
	vector<Arista<int>> _ARM;
	bool multiplesConjuntos;

	void ARM_Kruskal(GrafoValorado<int> const& g) {
		PriorityQueue<Arista<int>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
		if (cjtos.num_cjtos() > 1) {
			multiplesConjuntos = true;
		}
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int I, P;
	cin >> I >> P;
	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> g(I);
	int v1, v2, coste;
	for (int i = 0; i < P; i++) {
		cin >> v1 >> v2 >> coste;
		g.ponArista({ v1 - 1, v2 - 1, coste });
	}
	// resolver el caso posiblemente llamando a otras funciones
	CostePuente cp(g);
	// escribir la solución
	cp.getMultCjtos() ? cout << "No hay puentes suficientes\n" : cout << cp.costeARM() << "\n";
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
