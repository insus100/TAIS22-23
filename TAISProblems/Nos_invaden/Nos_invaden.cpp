
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

bool resuelveCaso() {

	// leer los datos de la entrada
	int N;
	cin >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> enemigos(N);
	vector<int> defensa(N);
	for (int i = 0; i < N; i++) {
		cin >> enemigos[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> defensa[i];
	}
	// resolver el caso posiblemente llamando a otras funciones
	sort(enemigos.begin(), enemigos.end(), greater<int>());
	sort(defensa.begin(), defensa.end(), greater<int>());
	int victoria = 0, i = 0, j = 0;

	while (i < N && j < N) {
		if (enemigos[i] <= defensa[j]) {//si gana defensa
			victoria++;
			i++;
			j++;
		}
		else {//si gana el ataque
			i++;
		}
	}
	cout << victoria << "\n";
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
