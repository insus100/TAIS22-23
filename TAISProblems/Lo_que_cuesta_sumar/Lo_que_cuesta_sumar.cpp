
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>//para priority_queue
using namespace std;

//#include "priori"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
long long int esfuerzoMinimo(priority_queue<long long int, vector<long long int>, greater<long long int>>& cola, const int& N) {
    int tam = N;
    long long int suma = 0, esfuerzo = 0;
    while (tam > 1) {
        auto val1 = cola.top(); cola.pop();
        auto val2 = cola.top(); cola.pop();
        val1 += val2;
        esfuerzo += val1;
        cola.push(val1);
        tam--;
    }
    return esfuerzo;
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)
        return false;
    priority_queue<long long int, vector<long long int>, greater<long long int>> cola_min;
    for (int i = 0; i < N; i++) {
        int n; cin >> n;
        cola_min.push(n);
    }

    // resolver el caso posiblemente llamando a otras funciones
    cout << esfuerzoMinimo(cola_min, N) << "\n";
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
