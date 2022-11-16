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
  * Puesto 0114
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Matriz.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 En la funcion concierto() inicializamos la matriz de tamaño (N*P) a -1 porque es un problema de maximizar.
 Después llamamos a la funcion recursiva resolver(), la cual utiliza programacion dinamica descendente.
 Miramos en la matriz si el subproblema[i][j] se ha resuelto y si es asi lo devolvemos. Sino en los casos recursivos devolvemos el valor [i][j]
 quedandonos con el max de ambas llamadas ya que es un problema de maximizar.
 Por ultimo despues de realizarse la llamada recursiva, creamos un vector de booleanos que pone a true los indices que pertenecen a las
 soluciones optimas.

 Escribe en particular la especificación y definición de la recurrencia
 en la que te has basado para resolver el problema por programación dinámica.
 Primera llamada
 concierto(N, P)

 Casos basicos:
 concierto(0,j) = 0 0 <= j <= P
 concierto(i, 0) = 0 0 <= i <= N

 Casos recursivos:
 concierto(i,j) =
 {
    concierto(i-1, j) si pi > j
    max(concierto(i-1, j), mochila(i-1, j-pi)+vi) si pi <= j
    
    con 1 <= i <= N y 1 <= j <= P
 }

 El problema tiene (funcion resolver) coste en tiempo de O(N*P) y en espacio adicional de O(N)
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct Festival {
    int grupos;
    int precios;
};

int resolver(vector<Festival> const& f, int i, int j, Matriz<int>& conciertos) {
    if (conciertos[i][j] != -1)
        return conciertos[i][j];
    if (i == 0 || j == 0) conciertos[i][j] = 0;
    else if (f[i - 1].precios > j)
        conciertos[i][j] = resolver(f, i - 1, j, conciertos);
    else conciertos[i][j] = max(resolver(f, i - 1, j, conciertos), resolver(f, i - 1, j - f[i - 1].precios, conciertos) + f[i - 1].grupos);
    return conciertos[i][j];
}

int concierto(vector<Festival> const& f, int M, vector<bool>& sol) {
    int n = f.size();
    Matriz<int> concierto(n + 1, M + 1, -1);
    int valor = resolver(f, n, M, concierto);
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (concierto[i][j] != concierto[i - 1][j]) {
            sol[i - 1] = true, j = j - f[i - 1].precios;
        }
        i--;
    }
    return valor;
}

bool resuelveCaso() {

    int P, N;
    cin >> P >> N;  // presupuesto y número de festivales

    if (!cin)
        return false;
    vector<Festival> f(N);
    for (int i = 0; i < N; i++) {
        Festival aux;
        cin >> aux.grupos >> aux.precios;
        f[i] = aux;
    }

    // leer el resto del caso y resolverlo
    vector<bool> sol;
    cout << concierto(f, P, sol) << "\n";




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
