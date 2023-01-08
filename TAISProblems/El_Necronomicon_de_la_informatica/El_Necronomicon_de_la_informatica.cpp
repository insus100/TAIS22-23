
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
	Necronomicon(Digrafo const& g, vector<char> const& instrucciones) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false), instrucciones(instrucciones) {
		dfs(g, 0);
	}
	bool hayCiclo() const {
		return hayciclo;
	}
	bool hayCamino(int v) const {
		return visit[v];
	}

private:
	vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	vector<int> ant; // ant[v] = vértice anterior en el camino a v
	vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	vector<char> instrucciones;
	Camino _ciclo; // ciclo dirigido (vacío si no existe)
	bool hayciclo;

	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			//if (hayciclo) // si hemos encontrado un ciclo terminamos
			// 	return;
			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				//ant[w] = v;
				dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
		 // se recupera retrocediendo
				hayciclo = true;
				/*for (int x = v; x != w; x = ant[x]) {
					_ciclo.push_front(x);
					//if (instrucciones[x] == 'C') aveces = true;
				}
					
				_ciclo.push_front(w); _ciclo.push_front(v);*/
			}
		}
		apilado[v] = false;
	}
};

/*
Interesa poner un vértice más, detrás de la última instrucción, para
saber que el programa ha terminado. Hay que averiguar si desde el vértice
inicial (no hay que buscar en todas las componentes conexas, solamente en la
que incluye ese vértice) se alcanza un ciclo, y si desde ese vértice es
alcanzable el último vértice (el ficticio). Dependiendo de la respuesta a
esas preguntas se decide la solución.

Si alcanza el vértice final desde el principio y no hay ciclo es siempre.
Si alcanza el vértice final desde el principio y hay ciclo es a veces.
Si no lo alcanza es nunca.
*/

bool resuelveCaso() {

	// leer los datos de la entrada
	int L, num;
	char ins;
	cin >> L;
	if (!std::cin)  // fin de la entrada
		return false;
	Digrafo g(L + 1);
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

	if(instrucciones[L - 1] != 'J') g.ponArista(g.V() - 2, g.V() - 1);//vertice ficticio "fin de programa"

	// resolver el caso posiblemente llamando a otras funciones
	Necronomicon n(g, instrucciones);
	// escribir la solución

	if (n.hayCamino(L)) {
		n.hayCiclo() ? cout << "A VECES\n" : cout << "SIEMPRE\n";
	}
	else {
		cout << "NUNCA\n";
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
