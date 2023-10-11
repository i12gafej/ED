/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO
    if(t->is_empty())
        height=-1;
    else{
        int izquierda = -1, derecha = -1;
        auto subtree_l = t->left();
        auto subtree_r = t->right();
        if(!subtree_l->is_empty())
            izquierda = compute_height<T>(subtree_l);
        if(!subtree_r->is_empty())
            derecha = compute_height<T>(subtree_r);
        if(izquierda > derecha)
            height = izquierda+1;
        else
            height = derecha+1;    
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!t->is_empty()){
        ret_val = 1 + compute_size<T>(t->left()) + compute_size<T>(t->right());
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && p(tree->item());
        retVal = retVal && prefix_process<T, Processor>(tree->left(), p);
        retVal = retVal && prefix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && infix_process<T, Processor>(tree->left(), p);
        retVal = retVal && p(tree->item());
        retVal = retVal && infix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && postfix_process<T, Processor>(tree->left(), p);
        retVal = retVal && postfix_process<T, Processor>(tree->right(), p);
        retVal = retVal && p(tree->item());
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    std::queue<typename BTree<T>::Ref> q;
    typename BTree<T>::Ref subtree;
    q.push(tree);
    while(!q.empty() && go_on){
        subtree = q.front();
        q.pop();
        if(!subtree->is_empty()){
            go_on = p(subtree->item());
            q.push(subtree->left());
            q.push(subtree->right());
        }
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T value)mutable->bool{
        out << value << " ";
        return true;
    };
    prefix_process<T>(tree, p);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T value)mutable->bool{
        out << value << " ";
        return true;
    };
    infix_process<T>(tree, p);
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T value)mutable->bool{
        out << value << " ";
        return true;
    };
    postfix_process<T>(tree, p);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T value)mutable->bool{
        out << value << " ";
        return true;
    };
    breadth_first_process<T>(tree, p);
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T value) mutable->bool{
        count++;
        found=(it == value);
        return it != value;
    };
    prefix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T value) mutable->bool{
        count++;
        found=(it == value);
        return it != value;
    };
    infix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T value) mutable->bool{
        count++;
        found=(it == value);
        return it != value;
    };
    postfix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p=[&found,it,&count](T value) mutable->bool{
        count++;
        found=(it == value);
        return it != value;
    };
    breadth_first_process<T>(tree,p);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    bool primero=true;
    T prev;
    auto p= [&primero,&prev](T value)mutable ->bool{
        if(primero){
            prev=value;
            primero=false;
            return true;
        }
        if(prev < value){
            prev=value;
            return true;
        }
        return false;
    }; 
    ret_val=infix_process<T>(tree,p);
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO
    if(tree->is_empty()){
        return false;
    }
    if(v < tree->item()){
        ret_val=has_in_order(tree->left(),v);
    }
    else if(v > tree->item()){
        ret_val=has_in_order(tree->right(),v);
    }
    else if(v ==tree->item()){
        return true;
    }
    
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if(tree->is_empty()){
        tree->create_root(v);
    }
    if(v < tree->item()){
        if(tree->left()->is_empty()){
            tree->set_left(BTree<T>::create(v));
        }else{
            insert_in_order(tree->left(),v);
        }
    }
    else if(v > tree->item()){
        if(tree->right()->is_empty()){
            tree->set_right(BTree<T>::create(v));
        }else{
            insert_in_order(tree->right(),v);
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
