/**
 * @file trie.cpp
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
#include "trie.hpp"

Trie::Trie()
{
    //TODO
    root_ = nullptr;
    prefix_ = "";
    //
    assert(is_empty());
}

Trie::Ref Trie::create()
{    
    return std::make_shared<Trie>();
}

Trie::Trie(TrieNode::Ref root_node, std::string const& pref)
{
    //TODO
    root_ = root_node;
    prefix_ = pref;
    //
    assert(prefix() == pref);
}

Trie::Ref Trie::create(TrieNode::Ref root_node, std::string const& prefix)
{
    //We cannot use std::make_shared here
    //because the constructor is protected.
    typename Trie::Ref trie ( new Trie(root_node, prefix));
    return trie;
}

Trie::Ref Trie::create(std::istream& in) noexcept(false)
{
    Trie::Ref trie = nullptr;
    //TODO
    std::string c, prefix;
    TrieNode::Ref nodo;
    in >> c;
    if (c != "["){
        throw std::runtime_error("Wrong input format");
    }
    in >> c;
    if(c != "\""){
        throw std::runtime_error("Wrong input format");
    }
    while(in >> c && c != "\""){
        if(c == "[")
            throw std::runtime_error("Wrong input format");
        int n = stoi(c, nullptr, 16);
		char l = static_cast<char>(n);
        prefix.push_back(l);
    }
    nodo->create(in);
    trie->create(nodo, prefix);
    in >> c;
    
    
    //
    return trie;
}

bool
Trie::is_empty() const
{
    bool ret_v=true;
    //TODO
    ret_v = (root_ == nullptr);
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    //TODO
    ret_val = prefix_;
    //
    return ret_val;
}

bool
Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    //TODO
    ret_val = root_->is_key();
    //
    return ret_val;
}


TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node = nullptr;
    //TODO
    node = root_;
    //
    return node;
}

bool
Trie::has(std::string const& k) const
{
    assert(!is_empty());
    bool found = false;
    //TODO
    //Hint: use find_node() to do this.
    //Remember: The Trie can have a prefix==k but does not store the key k.    
    TrieNode::Ref node;
    node = find_node(k);
    found = (node != nullptr && node->is_key());
    //
    return found;
}

static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> & keys)
{
    //TODO
    //Remember: node->is_key() means the prefix is a key too.
    
    if(node->is_key()){
        keys.push_back(prefix);
    }
    node->goto_first_child();
    while(node->current_exists()){
        preorder_traversal(node->current_node(), prefix+node->current_symbol(), keys);
        node->goto_next_child();
    }
    //
}


void
Trie::retrieve(std::vector<std::string>& keys) const
{
    assert(!is_empty());
    //TODO
    //Remember add the subtrie's prefix to the retrieve keys.
    preorder_traversal(root(), prefix(), keys);
    //
}

Trie::Ref
Trie::child(std::string const& pref) const
{
    assert(!is_empty());
    Trie::Ref ret_v = Trie::create();
    //TODO
    //Hint: use find_node() to do this.
    TrieNode::Ref node;
    Trie::Ref aux;
    node = find_node(pref);
    if(node == nullptr){
        aux = Trie::create(node, "");
    }else{
        aux = Trie::create(node, prefix_ + pref);
    }
    
    ret_v = aux;
    //
    assert(ret_v != nullptr);
    return ret_v;
}

bool
Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO
    ret_val = root_->current_exists();
    //
    return ret_val;
}

Trie::Ref
Trie::current() const
{
    assert(current_exists());
    Trie::Ref trie = nullptr;
    //TODO
    trie = create(root_->current_node(), prefix_ + current_symbol());
    //
    return trie;
}

char
Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO
    symbol = (root_->current_symbol());
    //
    return symbol;
}

void
Trie::insert(std::string const& k)
{
    assert(k != "");
    //TODO
    TrieNode::Ref node;
    if(root() == nullptr){
        root_ = TrieNode::create(false);
    }
    node = root();
    for(long unsigned int i = 0; i < k.size(); i++){
        if(node->has(k[i])){
            node = node->child(k[i]);
        }
        else{
            TrieNode::Ref new_node = TrieNode::create(false);
            node->set_child(k[i], new_node);
            node = new_node;
        }
    }
    node->set_is_key_state(true);
    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    //TODO
    //Remember: the prefix "" must return the trie's root node.
    node = root();
    size_t i = 0;
    while(i < pref.size() && node != nullptr){
        if(node->has(pref[i])){
            node = node->child(pref[i]);
            i++;
        }
        else{
            node = nullptr;
        }
            
    }
    //
    return node;
}

std::ostream&
Trie::fold(std::ostream& out) const
{
    //TODO
    //if(prefix() == ""){
    //    out << "[ \" " << prefix() << " \"";
    //}
    //else{
        out<<"[ \" ";
        for(size_t i = 0; i < prefix().size(); i++){
            out<<std::hex<<(short)prefix()[i]<<" ";
        }
        out<<"\" ";
        if(root() != nullptr)
            root_->fold(out);
        out<<" ]";
    //}
    
    //
    return out;
}

bool
Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    //TODO
    found = root_->find_child(symbol);
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol()==symbol);
    return found;
}

void
Trie::goto_first_symbol()
{
    assert(!is_empty());
    //TODO
    root_->goto_first_child();
    //
    assert(!current_exists() ||
           current()->prefix()==prefix()+current_symbol());
}

void
Trie::goto_next_symbol()
{
    assert(current_exists());
    //TODO
    root_->goto_next_child();
    //
}
