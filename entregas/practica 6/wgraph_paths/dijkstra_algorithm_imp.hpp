/**
 * @file dijkstra_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 * 
 * std::queue<std::tuple<float, T, T>> cola;
    g->goto_first_node()
    cola.push(make_tuple(0.0, ))
 */
#pragma once
#include <cassert>
#include <tuple>
#include <queue>
#include <limits>
#include <functional>

#include "dijkstra_algorithm.hpp"


template<class T>
void dijkstra_algorithm(typename WGraph<T>::Ref g,
                        std::vector<size_t>& predecessors,
                        std::vector<float>& distances)
{
    assert(g->has_current_node());

    //TODO
    //Hint: initialize distances with inf.
    //Hint: Initialize the vector of predecessors so that each vertex is a
    //      predecessor of itself.
    //Hint: use the the template tuple para represent edges. Set the fields so
    //      the tuples will be sorted properly.
    //      @see: https://en.cppreference.com/w/cpp/utility/tuple
    // Hint: you can use the keyword "using" to create an alias "Tuple"
    int nVertices = g->size();
    //P ← Array[Int]::make(g.nVertices()) 
    predecessors.resize(nVertices);
    
    // D ← Array[Float]::make(g.nVertices()) 
    //D ← ∞
    distances.resize(nVertices);

     for (int i = 0; i < nVertices; i++)
    {
        predecessors[i] = -1;                                  
        distances[i] = std::numeric_limits<float>::infinity(); 
    }
    
    //start:Vertex
    size_t startVertex = g->current_node()->label();
    distances[startVertex] = 0.0;
    
    //q ← PriorityQueue[Tuple[Float, Int, Int]]
    std::priority_queue<std::tuple<float, int, int>,
                        std::vector<std::tuple<float, int, int>>,
                        std::greater<std::tuple<float, int, int>>> pq;
    //q.enque(Tuple(0.0, start, start))
    pq.push(std::make_tuple(0.0, startVertex, startVertex));
    

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        int u = std::get<1>(t);
        
        

        if (!g->node(u)->is_visited()) {
            predecessors[u] = std::get<2>(t);
            distances[u] = std::get<0>(t);
            g->node(u)->set_visited(true);
            g->goto_node(g->node(u));
            while (g->has_current_edge()) {
                auto v = g->current_edge()->other(g->node(u));
                if (!g->node(v->label())->is_visited()) {
                    
                    pq.push(std::make_tuple(distances[u] + g->current_weight(), v->label(), u));
                }
            }
        }

        
    }
    //
}


inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t>const& predecessors)
{
    assert(src<predecessors.size());
    assert(dst<predecessors.size());
    assert(predecessors[src]==src);
    std::list<size_t> path;
    //TODO
    //  size_t currentVertex = dst;
    //   while (currentVertex != src) {
    //     path.push_front(currentVertex);
    //     currentVertex = predecessors[currentVertex];
    // }
     size_t current = dst;

    if(predecessors[current]==current){
        path.push_front(current);
        return path;
       }
    while (current != src) {
        path.push_front(current);
        current = predecessors[current];
    }

    path.push_front(src);
    // path.push_front(src);
    //
    return path;
}

