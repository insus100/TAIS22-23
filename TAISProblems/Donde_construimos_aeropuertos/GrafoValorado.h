//
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


template <typename Valor>
class Arista {
public:
   Arista() : pimpl(nullptr) {}
   Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}
   
   int uno() const { return pimpl->v; }
   int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
   Valor valor() const { return pimpl->valor; }
   
   void print(std::ostream & o = std::cout) const {
      o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
   }
   
   bool operator<(Arista<Valor> const& b) const {
      return valor() < b.valor();
   }
   bool operator>(Arista<Valor> const& b) const {
      return b.valor() < valor();
   }
private:
   struct Arista_impl {
      int v, w;
      Valor valor;
      Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
   };
   
   std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, Arista<Valor> const& ar) {
   ar.print(o);
   return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:
   
   /**
    * Crea un grafo valorado con V vértices, sin aristas.
    */
   GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }
   
   /**
    * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
    * primer es el índice del primer vértice del grafo en el entrada.
    */
   GrafoValorado(std::istream & flujo, int primer = 0) : _A(0) {
      flujo >> _V;
      if (!flujo) return;
      _ady.resize(_V);
      int E, v, w;
      Valor c;
      flujo >> E;
      while (E--) {
         flujo >> v >> w >> c;
         ponArista({v - primer, w - primer, c});
      }
   }

   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int A() const { return _A; }
   
   /**
    * Añade una arista al grafo.
    * @throws invalid_argument si algún vértice no existe
    */
   void ponArista(Arista<Valor> arista) {
      int v = arista.uno(), w = arista.otro(v);
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::invalid_argument("Vertice inexistente");
      ++_A;
      _ady[v].push_back(arista);
      _ady[w].push_back(arista);
   }
   
   /**
    * Devuelve la lista de adyacentes de v.
    * @throws invalid_argument si v no existe
    */
   AdysVal<Valor> const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::invalid_argument("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Devuelve las aristas del grafo.
    */
   std::vector<Arista<Valor>> aristas() const {
      std::vector<Arista<Valor>> ars;
      for (int v = 0; v < V(); ++v)
         for (auto arista : ady(v))
            if (v < arista.otro(v))
               ars.push_back(arista);
      return ars;
   }
   
   /**
    * Muestra el grafo en el stream de salida o
    */
   void print(std::ostream& o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (auto v = 0; v < _V; ++v) {
         o << v << ": ";
         for (auto const& w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }
   
private:
   int _V;   // número de vértices
   int _A;   // número de aristas
   std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
};


/**
 * Para mostrar grafos por la salida estándar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream & o, GrafoValorado<Valor> const& g) {
   g.print(o);
   return o;
}

#endif /* GRAFOVALORADO_H_ */
