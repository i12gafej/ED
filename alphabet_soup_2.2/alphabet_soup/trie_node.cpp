/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //TODO
    isKey = is_key_state;
    current_ = dict_.begin(); //el cursor se pone al principio del mapa
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //TODO
    ret_val = isKey;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO
    ret_v = (dict_.find(k) != dict_.end()); //la funcion devuelve end() si no encuentra el elemento k
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //TODO
    node = dict_.at(k); //at devuelve referencia a dicha parte del mapa
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //TODO
    ret_val = (current_ != dict_.end()); 
    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //TODO
    node = current_->second;
    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO
    symbol = current_->first;
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //TODO
    isKey = new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //TODO
    current_ = dict_.find(s); //ponemos el iterador en find, si no lo encuentra sale end
    found = (current_ != dict_.end());
    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //TODO
    current_ = dict_.begin();
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //TODO
    ++current_;
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //TODO
    dict_[k] = node; //la clave k significa la referencia dada
    current_ = dict_.find(k); //el cursor tiene que apuntar al hijo
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //TODO
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip
    out << "[ "<< (isKey ? "T" : "F");
    for (const auto& entry : dict_)
    {
        out << " " << std::hex << (short)entry.first << " ";
        entry.second->fold(out);
    }
    out << " ]";
    return out;
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO
    std::string c;
    in >> c;
    if (c != "["){
        throw std::runtime_error("Wrong input format");
    }
    in >> c;
    bool is_key;
    if(c == "T")
        is_key = true;
    else if(c == "F")
          is_key = false;
    else
        throw std::runtime_error("Wrong input format");
    // si es true es T si es false es F
    node = TrieNode::create(is_key); //creamos el nodo que apunta al trie
    while (in >> c && c != "]") //mientras no se cierre se le
    {
        char symbol ;
        symbol = (char)std::stoi(c, nullptr,16);
        
        //unsigned int symbol_c = static_cast<int>(symbol);
        node->set_child(symbol, TrieNode::create(in));
    }
       if(c != "]")
            throw std::runtime_error("Wrong input format");
    //
    return node;
}
