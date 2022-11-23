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
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "Matriz.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución (tanto en
 tiempo como en espacio), en función del tamaño del problema.

 Escribe en particular la especificación y definición de la recurrencia
 en la que te has basado para resolver el problema por programación dinámica.

 El coste en tiempo es O(sizeX*sizeY) porque recorremos toda la matrix.
 El coste en espacio es O(sizeX*sizeY) que es el tamaño de la matriz.

 Para ver la solucion, cogemos la ultima letra de cada palabra, si coincide significa que la subsecuencia mas larga va a terminar por la misma
 letra. Sino, comparamos la ultima letra de la primera palabra con la penultima de la segunda palabra, si se cumple que son la misma letra
 la subsecuencia acaba con esa letra, sino comparamos la penultima letra de la primera palabra con la ultima de la segunda palabra.
 La recurrencia es:
 sol(i, j) = {
     sol(i - 1, j - 1) + 1 si X[i - 1] == Y[j - 1]
     max(sol(i - 1, j), sol(i, j - 1)) si X[i - 1] != Y[j - 1]
}
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>



bool resuelveCaso() {

    // leemos la entrada
    string X, Y;
    cin >> X >> Y;

    if (!cin)
        return false;

    int sizeX = X.size(), sizeY = Y.size();
    Matriz<int> mat(sizeX + 1, sizeY + 1, 0);

    // resolver el caso
    for (int i = 1; i <= sizeX; i++) {
        for (int j = 1; j <= sizeY; j++) {
            if (X[i - 1] == Y[j - 1])
                mat[i][j] = mat[i - 1][j - 1] + 1;
            else
                mat[i][j] = max(mat[i - 1][j], mat[i][j - 1]);
        }
    }
    int num_characters = mat[sizeX][sizeY];
    string result(num_characters, ' ');
    int curSizeX = sizeX, curSizeY = sizeY;
    int found_characters = 0;
    while (found_characters < num_characters) {
        if (X[curSizeX - 1] != Y[curSizeY - 1]) {
            if (mat[curSizeX][curSizeY] == mat[curSizeX - 1][curSizeY])
                curSizeX--;
            else if (mat[curSizeX][curSizeY] == mat[curSizeX][curSizeY - 1])
                curSizeY--;
        }
        else {
            result[num_characters - found_characters - 1] = X[curSizeX - 1];
            curSizeX--;
            curSizeY--;
            found_characters++;
        }
    }
    for (auto c : result)
        cout << c;
    cout << "\n";
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
