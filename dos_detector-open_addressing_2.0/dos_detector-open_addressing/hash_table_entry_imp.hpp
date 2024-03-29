/**
 * @file hash_table_entry_imp.hpp
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
#include "hash_table_entry.hpp"

template<class K, class V>
HashTableEntry<K,V>::HashTableEntry()
{
    //TODO
    state_ = EntryState::EMPTY;

    //
    assert(is_empty());
}

template<class K, class V>
HashTableEntry<K,V>::HashTableEntry(const K& k, const V &v)
{
    //TODO
    data_.first = k;
    data_.second = v;
    state_ = EntryState::VALID;
    //
    assert(is_valid());
    assert(get_key()==k);
    assert(get_value()==v);
}

template<class K, class V>
bool HashTableEntry<K,V>::is_valid() const
{
    bool ret_val = false;
    //TODO
    if(state_ == EntryState::VALID){
        ret_val = true;
    }
    else{
    	ret_val = false;
    }
    //
    return ret_val;
}

template<class K, class V>
bool HashTableEntry<K,V>::is_empty() const
{
    bool ret_val = false;
    //TODO
    if(state_ == EntryState::EMPTY){
        ret_val = true;
    }
    //
    return ret_val;
}

template<class K, class V>
bool HashTableEntry<K,V>::is_deleted() const
{
    bool ret_val = false;
    //TODO
    if(state_ == EntryState::DELETED){
        ret_val = true;
    }
    //
    return ret_val;
}

template<class K, class V>
K
HashTableEntry<K,V>::get_key() const
{
    assert(!is_empty());
    K ret_val;
    //TODO
    ret_val = data_.first;
    //
    return ret_val;
}

template<class K, class V>
V
HashTableEntry<K,V>::get_value() const
{
    assert(!is_empty());
    V ret_val;
    //TODO
    ret_val = data_.second;
    //
    return ret_val;
}

template<class K, class V>
void
HashTableEntry<K,V>::set(const K& k, const V& v)
{
    //TODO

    data_.first = k;
    data_.second = v;
    state_ = EntryState::VALID;

    //
    assert(is_valid());
    assert(get_key()==k);
    assert(get_value()==v);
}

template<class K, class V>
void
HashTableEntry<K,V>::set_value(const V& v)
{
    assert(is_valid());
#ifndef NDEBUG
    K old_key = get_key();
#endif
    //TODO
    data_.second = v;
    state_ = EntryState::VALID;
    //
    assert(is_valid());
    assert(get_value()==v);
    assert(old_key == get_key());
}

template<class K, class V>
void
HashTableEntry<K,V>::set_deleted()
{
    assert(is_valid());
    //TODO
    state_ = EntryState::DELETED;
    //
    assert(is_deleted());
}
