
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
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

struct Tarea {
    bool repite; // si es periódica o no
    int ini, fin, intervalo;
};

// cuándo b tiene que salir antes
bool operator<(Tarea const& a, Tarea const& b) {
    return a.ini > b.ini;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M, T;
    cin >> N >> M >> T;
    if (!std::cin)  // fin de la entrada
        return false;
    int ini, fin, intervalo;
    priority_queue<Tarea> cola;
    for (int i = 0; i < N; i++) {//tareas unicas
        cin >> ini >> fin;
        cola.push({ false, ini, fin, 0 });
    }
    for (int i = 0; i < M; i++) {//tareas periodicas
        cin >> ini >> fin >> intervalo;
        cola.push({ true, ini, fin, intervalo });
    }

    // resolver el caso posiblemente llamando a otras funciones
    bool conflicto = false;
    int ocupado = 0; // hasta cuándo estoy ocupado con las tareas procesadas
    while (!conflicto && !cola.empty() && cola.top().ini < T) {
        auto [rep, ini, fin, inter] = cola.top(); cola.pop();
        conflicto = ini < ocupado;
        ocupado = fin;
        if (rep) { // añadimos a la cola la nueva aparición de la tarea periódica
            cola.push({ true, ini + inter, fin + inter, inter });
        }
    }

    // escribir la solución
    conflicto ? cout << "SI\n" : cout << "NO\n";

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
