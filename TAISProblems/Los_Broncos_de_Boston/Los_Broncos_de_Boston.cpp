/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Javier Gil Caballero TAIS42
  * Estudiante 2: Íñigo Velasco Sánchez TAIS105
  * Puesto 0111
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Escribe también una demostración que justifique que tu solución encuentra
 siempre soluciones óptimas.

 Leemos las puntuaciones en dos vectores y los ordenamos usando sort. Los broncos de mayor a menor y los rivales de menor a mayor para luego 
 sacar la diferencia máxima.
 El coste en tiempo del algoritmo es O(NlogN) siendo N el número de partidos pronosticados.

 Demostración de optimalidad:
 Tenemos ordenado el vector de los Broncos de mayor a menor y el de los rivales de menor a mayor como hemos comentado anteriormente.
 Por lo tanto el resultado de nuestro acumulado va a ser la resta del k-esimo mayor resultado de los Broncos con el k-esimo menor resultado de
 los rivales.
 suma = {max(0, B[k]- R[k]) siendo k= 1...N}

 B[0]>= B[1]...|B[i]...>=B[N]
 R[0]<= R[1]...|R[i]...<=B[N]
 O[0] ? O[1]...|O[i]...? O[N]

 Como el vector de los Broncos sabemos que está ordenado de mayor a menor no existe un valor en el vector de la solución óptima tal que
 B[i] < O[i] porque los valores mayores a ese punto ya han sido utilizados en la solución óptima.

 Esto demuestra que la solución óptima tiene como ecuación: suma = {max(0, O[k]- R[k]) siendo k= 1...N} que es la misma ecuación que nuestra
 solución, demostrando que es la mejor solución posible.
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

bool resuelveCaso() {

    int N;
    cin >> N;  // número de partidos

    if (N == 0)
        return false;
    vector<int> broncos(N), rivales(N);
    // leer el resto del caso y resolverlo
    int puntuacion;
    for (int i = 0; i < N; i++) {
        cin >> rivales[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> broncos[i];
    }
    sort(broncos.begin(), broncos.end(), greater<int>());
    sort(rivales.begin(), rivales.end());
    int acum = 0;
    for (int i = 0; i < N; i++) {
        if (broncos[i] > rivales[i])
            acum += broncos[i] - rivales[i];
    }
    cout << acum << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE");
#endif
    return 0;
}
