
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
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
struct Paciente {
	int id;
	int periodo;
	int suma;
	bool operator>(Paciente const& b)const {
		if (suma == b.suma) {
			return id > b.id;
		}
		return suma > b.suma;
	}
	Paciente() : id(id), periodo(periodo), suma(periodo)
	{
	}
};


bool resuelveCaso() {

	// leer los datos de la entrada
	int num_pacientes;
	cin >> num_pacientes;
	if (num_pacientes == 0)
		return false;
	priority_queue<Paciente, vector<Paciente>, greater<Paciente>> q;
	Paciente p;
	for (int i = 0; i < num_pacientes;i++) {
		cin >> p.id >> p.periodo;
		p.suma = p.periodo;
		q.push(p);
	}

	int envios;
	cin >> envios;
	for (int i = 0; i < envios;i++) {
		p = q.top(); q.pop();
		cout << p.id << "\n";
		p.suma += p.periodo;
		q.push(p);
	}
	cout << "---\n";
	// resolver el caso posiblemente llamando a otras funciones

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
