/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Íñigo Velasco Sánchez
  * Estudiante 2: Javier Gil Caballero
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;
//#include "PriorityQueue.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Creamos una estructura Cliente con el tiempo en ser atendidos y el numero de caja y el operador < para que se vayan insertando correctamente en la cola de minimos.
 En el resuelveCaso inicializamos en una cola de prioridad el número de caja y el tiempo.
 En resolver recorremos los clientes en espera y si hay alguna caja libre, se la asignamos, leemos el tiempo que tarda en ser atendido, volvemos a meter el cliente a la cola
 y restamos 1 a las cajas libres.
 Cuando no hay cajas libres sumamos el tiempo de espera de cliente a la caja más prioritaria para que sea atendido en dicha caja de tal manera que Ismael tendrá que ir a esa caja.
 //@ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cliente {
	int tiempo;
	int caja;
};

bool operator<(Cliente const& a, Cliente const& b) {
	//return a.tiempo < b.tiempo || a.caja < b.caja;
	return (a.tiempo > b.tiempo) || (a.tiempo == b.tiempo && a.caja > b.caja);
	/*if (a.tiempo < b.tiempo) {
		return true;
	}
	else if (a.tiempo == b.tiempo) {
		return a.caja < b.caja;

	}
	return false;*/
}

struct Compare
{
	bool operator()(Cliente const& a, Cliente const& b)
	{
		return (a.tiempo > b.tiempo) || (a.tiempo == b.tiempo && a.caja > b.caja);
	}
};

int resolver(priority_queue<Cliente>& c, int C) {//coste O(NlogN) siendo N el numero de cajas
	int libres = c.size();
	int tiem = 0;
	for (int i = 0; i < C; i++) {
		if (libres > 0) {
			auto cl = c.top();
			c.pop();
			cin >> cl.tiempo;
			c.push(cl);
			libres--;
		}
		else {
			auto cl = c.top();
			c.pop();
			cin >> tiem;
			cl.tiempo += tiem;
			c.push(cl);
		}
		tiem++;
	}
	return c.top().caja;
}
bool resuelveCaso() {
	int C = 0, N = 0;
	// leer los datos de la entrada
	cin >> N >> C;
	if (N == 0)
		return false;
	//PriorityQueue<Cliente> cola;
	priority_queue<Cliente> cola;
	Cliente c;
	for (int i = 0; i < N; i++) {
		c.caja = i + 1;
		c.tiempo = 0;
		cola.push(c);
	}

	// resolver el caso posiblemente llamando a otras funciones
	cout << resolver(cola, C) << "\n";
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