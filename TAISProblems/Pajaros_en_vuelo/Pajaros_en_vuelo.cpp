
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

class ColaMedianas {
public:
    /*Monticulo de maximos con elementos menore que la mediana incluida*/
    priority_queue<int> menores;

    /*Monticulo de maximos*/
    priority_queue<int, vector<int>, greater<int>> mayores;

    void reequilibra() {
        if (menores.size() < mayores.size()) {
            menores.push(mayores.top());
            mayores.pop();
        }
        else if (menores.size() > mayores.size() + 1) {
            mayores.push(menores.top());
            menores.pop();
        }
    }

    void insertar(int x) {
        if (menores.empty())
            menores.push(x);
        else {
            int med = menores.top();
            if (x < med)
                menores.push(x);
            else menores.push(med);
        }
    }

    ColaMedianas() {

    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int E, N;
    cin >> E >> N;
    if (E == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    priority_queue<int> edades;
    edades.push(E);//E es edad del primer pajaro
    for (int i = 0; i < N; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        edades.push(p1);
        edades.push(p2);
    }

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
