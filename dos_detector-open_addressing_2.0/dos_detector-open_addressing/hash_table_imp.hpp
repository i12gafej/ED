/**
 * @file hash_table_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cassert>

#include "hash_table.hpp"


template<class K, class V, class KeyToInt>
HashTable<K, V, KeyToInt>::HashTable(size_t m,
                                           typename KeyToInt::Ref key_to_int,
                                           OACollisionResolution::Ref hash)
{
    assert(m == hash->m());
    //TODO
    table_ = std::make_shared<table_t>(m);
    hash_ = hash;
    key_to_int_ = key_to_int;
    curr_ = 0;
    used_entries_ = 0;
    //
    assert(!is_valid());
    assert(size()==m);
}

template<class K, class V, class KeyToInt>
typename HashTable<K, V, KeyToInt>::Ref
HashTable<K, V, KeyToInt>::create(size_t m,
                                        typename KeyToInt::Ref key_to_int,
                                        OACollisionResolution::Ref hash)
{
    return std::make_shared<HashTable<K, V, KeyToInt>>(m, key_to_int,
                                                            hash);
}

template<class K, class V, class KeyToInt>
size_t
HashTable<K, V, KeyToInt>::size() const
{
    size_t ret_v = 0;
    //TODO
    ret_v = table_->size();//es un puntero
    //
    return ret_v;
}

template<class K, class V, class KeyToInt>
float
HashTable<K, V, KeyToInt>::load_factor() const
{
    float ret_v = 0.0f;
    //TODO
    ret_v = (float)used_entries_ / size();
    //
    return ret_v;
}


template<class K, class V, class KeyToInt>
bool
HashTable<K, V, KeyToInt>::has(K const& k) const
{
    bool ret_v = false;
    //TODO
    // Hint: use the find method but save/restore the state.
    size_t i = 0;
    auto aux = 0;
    do{
        aux = hash_->operator()(key_to_int_->operator()(k), i);
        i = i+1;
    } while(!(*table_)[aux].is_empty() || (*table_)[aux].get_key() == k) ;
    //
    return ret_v;
}

template<class K, class V, class KeyToInt>
bool
HashTable<K, V, KeyToInt>::is_valid() const
{
    bool ret_v = false;
    //TODO
    // Remember: check curr_ is in the table range and the table entry is valid.
    //CUIDAO si no deleted sin !
    ret_v = curr_ >= 0 && curr_ < size() && (*table_)[curr_].is_valid();
    //
    return ret_v;
}


template<class K, class V, class KeyToInt>
K
HashTable<K, V, KeyToInt>::get_key() const
{
    assert(is_valid());
    K ret_v;
    //TODO
    ret_v = (*table_)[curr_].get_key();
    //
    return ret_v;
}

template<class K, class V, class KeyToInt>
V
HashTable<K, V, KeyToInt>::get_value() const
{
    assert(is_valid());
    V ret_v = V();
    //TODO
    ret_v = (*table_)[curr_].get_value();
    //
    return ret_v;
}

template<class K, class V, class KeyToInt>
bool
HashTable<K, V, KeyToInt>::find(K const& k)
{
    assert(load_factor()<1.0f);
    bool is_found=false;
    //TODO
    size_t i = 0;
    
    do{
        curr_ = hash_->operator()(key_to_int_->operator()(k), i);//(*hash_)((*key_to_int_)(k), i);
        i++;
    }while((*table_)[curr_].is_empty() || (*table_)[curr_].get_key() == k);
    is_found = (*table_)[curr_].is_valid() && (*table_)[curr_].get_key() == k;
    //
    assert(!is_valid() || get_key()==k);
    return is_found;
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::insert(K const& k, V const& v)
{
    assert(load_factor()<1.0f);

    //TODO
    //locate the key.
    find(k);
    if((*table_) [curr_].is_empty()){
        used_entries_++;
    }
    (*table_)[curr_].set(k,v);
    rehash();
    //
    assert(load_factor()<1.0f);
    assert(is_valid());
    assert(get_key()==k);
    assert(get_value()==v);
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::remove()
{
#ifndef NDEBUG
    assert(is_valid());    
    K old_k = get_key();
#endif
    //TODO
    //Remember: we are using a mark to sign "deleted".
    (*table_)[curr_].set_deleted();
    //
    assert(!is_valid());
    assert(!has(old_k));
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::set_value(const V& v)
{
    assert(is_valid());
    //TODO
    (*table_)[curr_].set_value(v);
    //
    assert(get_value()==v);
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::rehash()
{
    assert(is_valid()); //We assume to be call after inserting.
    auto old_curr_key = get_key();
    //TODO
    //Remember: you must restore the cursor to point at the same <key,value>.
    //Remember: rehash when load_factor > 0.5
    //Remember: we use a 2 factor to grown the current size.
    //Remember: a new hash function will be picked at from the Universal Family.
    //Hint: use the assign operator = to switch the new table with "this".
    if(load_factor() > 0.5){
        auto newHash =  hash_->pick_at_new(size());
        auto newTable = HashTable<K,V,KeyToInt>(size()*2,key_to_int_, newHash);
        goto_begin();
        while(curr_ < size()){
            newTable.insert((*table_)[curr_].get_key(), (*table_)[curr_].get_value());
            goto_next();
        }
        (*this) = newTable;
        find(old_curr_key);
    }

    
    //
    assert(load_factor()<=0.5);
    assert(is_valid() && get_key()==old_curr_key);
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::goto_begin()
{
    //TODO
    //Remember: move cursor to the first (from position 0) valid entry
    //         if there is.
    curr_ = 0;
    for(size_t i = 0; i < size() && !is_valid(); i++){
        curr_ = i;
    }
    /*for(size_t i = 0; i < size() && !is_valid(); i++){
        if(!(*table_)[i].is_empty()){
            curr_ = i;
            i = size();
        }
    }*/
    //
}

template<class K, class V, class KeyToInt>
void
HashTable<K, V, KeyToInt>::goto_next()
{
    assert(is_valid());
    //TODO
    //Remember: move cursor to the next valid position if there is.
    curr_++;
    while(!is_valid() && curr_ < size()){
        curr_++;
    }
    //
}
