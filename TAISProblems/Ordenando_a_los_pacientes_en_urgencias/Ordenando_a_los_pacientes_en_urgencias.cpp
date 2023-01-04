
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
struct Ingreso {
    string nombre;
    int gravedad;
    int turno;
    bool operator<(const Ingreso& b) const {
        if (gravedad == b.gravedad) {
            return turno > b.turno;
        }
        return gravedad < b.gravedad;
    };
};
bool resuelveCaso() {

    // leer los datos de la entrada
    int num_eventos;
    cin >> num_eventos;
    if (num_eventos == 0)
        return false;
    priority_queue<Ingreso, vector<Ingreso>, less<Ingreso>> q;
    Ingreso in;
    for (int i = 0; i < num_eventos; i++) {
        char tipo;
        cin >> tipo;
        if (tipo == 'I') {
            cin >> in.nombre >> in.gravedad;
            in.turno = i;
            q.push(in);
        }
        else {//A
            in = q.top(); q.pop();
            cout << in.nombre << "\n";
        }
    }
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
    cout << "---\n";
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
