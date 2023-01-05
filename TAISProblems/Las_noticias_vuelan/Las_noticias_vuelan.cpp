
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Noticias {
public:
    Noticias(Grafo const& g) : visit(g.V(), false), contado(g.V(), false), conocen(g.V(), 0), amigos(1) {
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) { // se recorre una nueva componente conexa
                amigos = 1;
                dfs(g, v);
                for (int i = 0; i < visit.size(); i++) {
                    if (visit[i] && !contado[i]) {
                        conocen[i] = amigos;//asignamos al resto de personas que están en la componente conexa el número, para no tener que volver a hacer la llamada a dfs.
                        contado[i] = true;
                    }
                }
            }
            //visit.assign(visit.size(), false);//TIMELIMIT
        }
    }

    vector<int> conocenNoticia() const& {
        return conocen;
    }

private:
    vector<bool> visit;
    vector<bool> contado;
    vector<int> conocen;
    int amigos;
    void dfs(Grafo const& g, int v) {
        visit[v] = true;
        //int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                amigos++;
                dfs(g, w);
            }
        }
        //visit[v] = false;//se reinicia visit a false una vez realizada la llamada recursiva.
        //return tam;
    }
};


bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;
    Grafo g(N);

    int n, v1 = -1, v2 = -1;
    for (int i = 0; i < M; i++) {
        cin >> n;
        if (n != 0) {
            cin >> v1;
            for (int j = 0; j < n - 1; j++) {
                cin >> v2;
                g.ponArista(v1 - 1, v2 - 1);
                v1 = v2;
            }
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    Noticias noticias(g);
    // escribir la solución
    for (int& i : noticias.conocenNoticia())
        cout << i << " ";
    cout << "\n";
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
