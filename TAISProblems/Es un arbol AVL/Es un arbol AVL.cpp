
/*@ <answer>
 *
 * Nombre y Apellidos: Íñigo Velasco Sánchez
 *
 *@ </answer> */

#include <fstream>
#include "BinTree.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool esEquilibrado(const BinTree<int>& t, int &alt) {
    if (t.empty()) {
        alt = 0;
        return true;//si es vacio está equilibrado
    }
    else {
        int alturaIzq, alturaDer;

        bool izq = esEquilibrado(t.left(), alturaIzq);
        bool der = esEquilibrado(t.right(), alturaDer);

        alt = max(alturaDer, alturaIzq) + 1;

        if (abs(alturaIzq - alturaDer) <= 1 && izq && der)
            return true;
        else
            return false;
    }
}

bool esAVL(const BinTree<int>& t, bool& avl, int& min, int& max) {
    if (!t.empty() && avl) {
        if (t.right().empty() && t.left().empty()) {
            min = t.root();
            max = t.root();
        }
        else {
            int aux = -1;
            if (!t.left().empty()) {
                esAVL(t.left(), avl, min, max);
                if (max >= t.root()) {
                    avl = false;
                }
                else {
                    max = t.root();
                }
                aux = min;
            }

            if (!t.right().empty()) {
                esAVL(t.right(), avl, min, max);

                if (min <= t.root()) {
                    avl = false;
                }
                else if (aux != -1) {
                    min = aux;
                }
                else {
                    min = t.root();
                }
            }
        }
    }
    return avl;
}

void resuelveCaso() {

    // leer los datos de la entrada
    auto t = read_tree<int>(cin);
    int altura = 0, min = INT32_MAX, max = INT32_MIN;
    bool avl = true;
    esEquilibrado(t, altura) && esAVL(t, avl, min, max) ? cout << "SI" : cout << "NO";
    cout << "\n";
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
