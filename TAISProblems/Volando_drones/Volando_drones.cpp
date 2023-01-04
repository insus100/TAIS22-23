
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Dron {
	int pila9;//tiempo que le queda en la pila de 9V
	int pila15;//tiempo que le queda en la pila de 1.5V
	int tiempo_vuelo;
};

int horas_vuelo(vector<Dron> d, priority_queue<int> &pilas9, priority_queue<int> &pilas15, int i = 0, int tiempo_max = 0) {
	while (!pilas9.empty() && !pilas15.empty() && i < d.size()) {
		//ponemos pilas a los drones;
		d[i].pila9 = pilas9.top(); pilas9.pop();
		d[i].pila15 = pilas15.top(); pilas15.pop();
		//calculamos el tiempo de vuelo maximo con esas pilas (que es el tiempo minimo de vida entre las dos pilas)
		d[i].tiempo_vuelo = min(d[i].pila9, d[i].pila15);
		tiempo_max += d[i].tiempo_vuelo;
		//restamos vida a las pilas.
		d[i].pila9 -= d[i].tiempo_vuelo;
		d[i].pila15 -= d[i].tiempo_vuelo;
		i++;
	}
	for (Dron dron : d) {
		if (dron.pila9 > 0) pilas9.push(dron.pila9);
		else if (dron.pila15 > 0) pilas15.push(dron.pila15);
	}
	return tiempo_max;
}

bool resuelveCaso() {

	// leer los datos de la entrada
	int N, A, B;
	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> A >> B;
	vector<Dron> d(N);
	priority_queue<int> pilas9, pilas15;
	int t_vuelo;
	for (int i = 0; i < A; i++) {
		cin >> t_vuelo;
		pilas9.push(t_vuelo);
	}

	for (int i = 0; i < B; i++) {
		cin >> t_vuelo;
		pilas15.push(t_vuelo);
	}

	while (!pilas9.empty() && !pilas15.empty()) {
		cout << horas_vuelo(d, pilas9, pilas15) << " ";
	}
	cout << "\n";
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
