
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
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

struct Pelicula {
	int ini;
	int fin;
	bool operator<(Pelicula const& b) {
		return fin < b.fin;
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int N, horas, minutos, duracion;
	cin >> N;
	if (N == 0)
		return false;
	vector<Pelicula> p(N);
	Pelicula peli;
	for (int i = 0; i < N; i++) {
		cin >> horas;
		cin.ignore(1);
		cin >> minutos >> duracion;
		peli.ini = horas * 60 + minutos;
		peli.fin = peli.ini + duracion + 10;
		p[i] = peli;
	}

	// resolver el caso posiblemente llamando a otras funciones
	sort(p.begin(), p.end());
	// escribir la solución
	int sol = 1, i = 1, ant = p[0].fin;
	while (i < N) {
		if (p[i].ini >= ant) {
			sol++;
			ant = p[i].fin;
		}
		i++;
	}
	cout << sol << "\n";
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
