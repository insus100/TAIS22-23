
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
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
class Necronomicon {
public:
	Necronomicon(Digrafo const& g, vector<char> const& instrucciones) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false), aveces(false), instrucciones(instrucciones) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	bool a_veces() const {
		return aveces;
	}
	bool hayCiclo() const {
		return hayciclo;
	}

private:
	vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	vector<int> ant; // ant[v] = vértice anterior en el camino a v
	vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	vector<char> instrucciones;
	Camino _ciclo; // ciclo dirigido (vacío si no existe)
	bool hayciclo;
	bool aveces;

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
				for (int x = v; x != w; x = ant[x]) {
					_ciclo.push_front(x);
					if (instrucciones[x] == 'C') aveces = true;
				}
					
				_ciclo.push_front(w); _ciclo.push_front(v);
			}
		}
		apilado[v] = false;
	}
};


bool resuelveCaso() {

	// leer los datos de la entrada
	int L, num;
	char ins;
	cin >> L;
	if (!std::cin)  // fin de la entrada
		return false;
	Digrafo g(L);
	vector<char> instrucciones(L);
	for (int i = 0; i < L; i++) {
		cin >> ins;
		if (ins != 'A') {//la instruccion es de salto (J, C)
			cin >> num;
			g.ponArista(i, num - 1);
			if(ins == 'C' && i < L - 1) {
				g.ponArista(i, i + 1);
			}
		}
		else if(i < L - 1)  {
			g.ponArista(i, i + 1);
		}
		instrucciones[i] = ins;
	}

	// resolver el caso posiblemente llamando a otras funciones
	Necronomicon n(g, instrucciones);
	// escribir la solución
	if (n.hayCiclo()) {
		n.a_veces() ? cout << "A VECES\n" : cout << "NUNCA\n";
	}else{
		cout << "SIEMPRE\n";
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
