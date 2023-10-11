/**
 * @file floyd_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <utility>
#include <stack>
#include "floyd_algorithm.hpp"

#ifdef __VERBOSE__
#include <iostream>
#include <iomanip>
extern int Verbose_level;
#endif

void tratar_camino(size_t u, size_t v, IMatrix::Ref I, std::list<size_t> & path);

template<class T>
void floyd_algorithm(const typename WGraph<T>::Ref g, FMatrix::Ref& D,
                     IMatrix::Ref& I)
{
    D = g->weight_matrix();
    I = IMatrix::create(g->size(), g->size(), -1);

    //TODO: Codify the Floyd algorithm.
    for(size_t z = 0; z < g->size(); z++)
    {
        for(size_t w = 0; w < g->size(); w++)
        {
            for(size_t a = 0; a < g->size(); a++)
            {
                if(D->get(w,z)+D->get(z,a)<D->get(w,a))
                {
                    D->set(w,a,D->get(w,z)+D->get(z,a));
                    I->set(w,a,z);
                }
            }
        }
    }
    
    //
}

std::list<size_t> floyd_path(size_t src, size_t dst, IMatrix::Ref I)
{
    //Prec: distance (u,v) < inf
    std::list<size_t> path;

    //TODO: Find the path.
    //Hint: Think first. Is it necessary to build a binary tree? or it
    //is enough to do an first-depth search using an iterative approach with
    //a stack of pairs (u,v).

    path.resize(0);
    tratar_camino(src,dst,I,path);
    path.push_back(dst);
    
    //
    return path;
}
void tratar_camino(size_t u, size_t v, IMatrix::Ref I, std::list<size_t> & path){
    size_t a = I->get(u,v);
    if (a == (size_t)-1){
        path.push_back(u); 
    }
    else{
        tratar_camino(u, a, I, path); 
        tratar_camino(a, v, I, path); 
    }
}




