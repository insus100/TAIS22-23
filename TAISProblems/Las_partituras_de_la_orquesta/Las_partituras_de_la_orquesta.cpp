/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Javier Gil Caballero (TAIS42)
  * Estudiante 2: Íñigo Velasco Sánchez (TAIS105)
  * Puesto 10 lab 1
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

 El coste de la operacion resolver es O(plogN) siendo p el numero de partituras que nos quedan por repartir una vez
 asignadas 1 a cada instrumento, y N el numero de instrumentos distintos.

 Creamos un struct para cada atril que contenga el numero de musicos por instrumento y empiece con 1 sola partitura para cada uno.
 En el comparador repartimos las partituras entre los musicos de un mismo instrumento, así se reordenan cada vez que modifiquemos la cola.
 Cuando la división es impar, sumamos 1 al resultado para quedarnos con el mayor resultado después de dividir.
 El comparador lo ordenará en una cola de máximos según el número de músicos por partitura.
 Al final nos queda en la cabeza de la cola el Atril con el mayor número de músicos que se agolparán a su alrededor.
 Devolvemos un entero que contenga el número de músicos que es la solución que nos pide el problema.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct Atril {
    int  musicos;
    int partitura;
};

bool operator>(Atril const& a, Atril const& b) {
    int partiturasA = a.musicos / a.partitura, partiturasB = b.musicos / b.partitura;

    //si el número de musicos es impar nos quedamos con el mayor al dividirlos
    if(a.musicos % a.partitura != 0) partiturasA++;
    if(b.musicos % b.partitura != 0) partiturasB++;
    return partiturasA < partiturasB;
}

int resolver(priority_queue<Atril, vector<Atril>, greater<Atril>>& cola, int& p, int const& N) {
    while (p > 0) {
        Atril a = cola.top(); cola.pop();
        a.partitura++;
        p--;
        cola.push(a);
    }
    Atril b = cola.top();
    int ret = b.musicos / b.partitura;
    if (b.musicos % b.partitura != 0)
        ret++;
    return ret;
}

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;
    priority_queue<Atril, vector<Atril>, greater<Atril>> cola;
    int musicos;
    for (int i = 0; i < N; i++) {
        cin >> musicos;
        cola.push({ musicos, 1 });
    }
    P -= N;
    // leer el resto del caso y resolverlo
    cout << resolver(cola, P, N) << "\n";
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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
