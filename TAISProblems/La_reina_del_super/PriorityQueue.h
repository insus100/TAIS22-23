//
//  PriorityQueue.h
//
//  ImplementaciÃ³n de colas con prioridad de mÃ­nimos (el elemento mÃ¡s
//  prioritario es el menor) mediante montÃ­culos binarios
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

// Comparator dice cuÃ¡ndo un valor de tipo T es mÃ¡s prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {
   
   // vector que contiene los datos
   std::vector<T> array;     // primer elemento en la posiciÃ³n 1
   
   /* Objeto funciÃ³n que sabe comparar elementos.
    antes(a,b) es cierto si a es mÃ¡s prioritario que b (a debe salir antes que b) */
   Comparator antes;
   
public:
   
   PriorityQueue(Comparator c = Comparator()) : array(1), antes(c) {}
   
   /* Constructor a partir de un vector de elementos */
   PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator()) :
   array(v_ini.size() + 1), antes(c) {
      for (auto i = 0; i < v_ini.size(); ++i)
         array[i + 1] = v_ini[i];
      monticulizar();
   }

   
   /* Insertar el elemento x (que incluye su prioridad).
    Si no hay espacio, el array se agranda. */
   void push(T const& x) {
      array.push_back(x);
      flotar(array.size() - 1);
   }
   
   /* Devuelve el nÃºmero de elementos en la cola. */
   int size() const { return int(array.size()) - 1; }
   
   /* Averigua si la cola con prioridad estÃ¡ vacÃ­a. */
   bool empty() const { return size() == 0; }
   
   /* Si la cola no es vacÃ­a, devuelve el elemento mÃ¡s prioritario. */
   T const& top()  const {
      if (empty()) throw std::domain_error("La cola vacia no tiene top");
      else return array[1];
   }
   
   /* Si la cola no es vacÃ­a, elimina el elemento mÃ¡s prioritario. */
   void pop() {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
   /* Si la cola no es vacÃ­a, elimina y devuelve el elemento mÃ¡s prioritario. */
   void pop(T & prim) {
      if (empty())
         throw std::domain_error("Imposible eliminar el primero de una cola vacia");
      else {
         prim = std::move(array[1]);
         array[1] = std::move(array.back());
         array.pop_back();
         if (!empty()) hundir(1);
      }
   }
   
private:
   
   /* Flota el elemento situado en la posiciÃ³n i del montÃ­culo. */
   void flotar(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(elem, array[hueco / 2])) {
         array[hueco] = std::move(array[hueco / 2]);
         hueco /= 2;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Hunde el elemento situado en la posiciÃ³n n del montÃ­culo. */
   void hundir(int i) {
      T elem = std::move(array[i]);
      int hueco = i;
      int hijo = 2 * hueco; // hijo izquierdo, si existe
      while (hijo <= size())  {
         // cambiar al hijo derecho si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1], array[hijo]))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiÃ©ndose
         if (antes(array[hijo], elem)) {
            array[hueco] = std::move(array[hijo]);
            hueco = hijo; hijo = 2 * hueco;
         }
         else break;
      }
      array[hueco] = std::move(elem);
   }
   
   /* Convierte un vector en un montÃ­culo. */
   void monticulizar() {
      for (auto i = size() / 2; i > 0; --i)
         hundir(i);
   }
};

#endif /* PRIORITYQUEUE_H_ */