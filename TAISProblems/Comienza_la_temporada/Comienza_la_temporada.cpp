
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
    int N, M;
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> tallasChicos(N);
    vector<int> tallasStock(M);
    for (int i = 0; i < N; i++) {
        cin >> tallasChicos[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> tallasStock[i];
    }
    // resolver el caso posiblemente llamando a otras funciones
    sort(tallasChicos.begin(), tallasChicos.end(), greater<int>());
    sort(tallasStock.begin(), tallasStock.end(), greater<int>());
    int i = 0, j = 0, sol = 0;
    while (i < N && j < M) {
        if (tallasChicos[i] == tallasStock[j] || tallasChicos[i] + 1 == tallasStock[j]) {//si le vale la chamarra.
            sol++;
            i++;
            j++;
        }
        else if (tallasChicos[i] > tallasStock[j]) {
            i++;
        } else j++;
    }
    // escribir la solución
    cout << N - sol << "\n";
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
