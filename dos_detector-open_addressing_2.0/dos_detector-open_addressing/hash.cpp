/**
 * @file hash.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "hash.hpp"
#include <cassert>
#include <cstdlib>

/**Global object to generate random bits.*/
std::minstd_rand Generator;

double
uniform()
{
    double ret_v = 0.0;
    //TODO
    //Hint: Use std::uniform_real_distribution<double>
    //Remember use Generator as random bit generator.
    std::uniform_real_distribution<double>();
    ret_v =std::uniform_real_distribution<double>(0.0,1.0)(Generator);
   
    //
    assert(0.0l<=ret_v && ret_v<1.0l);
    return ret_v;
}


std::uint64_t
pick_at_random(std::uint64_t const& a, std::uint64_t const& b)
{
    assert(a<b);
    std::uint64_t ret_v = 0;
    //TODO
    //Hint: Use std::uniform_int_distribution<std::uint64_t>
    ret_v = std::uniform_int_distribution<std::uint64_t>(a,b)(Generator);
    //
    assert(a<=ret_v && ret_v<=b);
    return  ret_v;
}

//////////////////////////////////////////////////////////////
// Universal hash function.
//////////////////////////////////////////////////////////////

UHash::UHash(size_t M, std::uint64_t P)
{
    assert(M>1 && (M & (M-1))==0); //m is two power.
    assert(M<P);
    // TODO

    m_=M;
    p_=P;
    a_=pick_at_random(1,p()-1);
    b_=pick_at_random(0,p()-1);
    
    //
    assert(M==m());
    assert(P==p());
    assert(0<a() && a()<p());
    assert(0<=b() && b()<p());
}

UHash::Ref UHash::create(size_t m, std::uint64_t p)
{
    return std::make_shared<UHash>(m, p);
}


UHash::UHash(size_t M, std::uint64_t P, std::uint64_t A,
               std::uint64_t B)
{
    assert(M>1 && (M & (M-1))==0);
    assert(M<P);
    assert(0<A && A<P);
    assert(0<=B && B<P);    
    // TODO
    
    m_=M;
    p_=P;
    a_=A;
    b_=B;
    
    //
    assert(M==m());
    assert(P==p());
    assert(A==a());
    assert(B==b());
}

UHash::Ref UHash::create(size_t m, std::uint64_t p, std::uint64_t a,
                  std::uint64_t b)
{
    return std::make_shared<UHash>(m, p, a, b);
}

UHash::Ref UHash::pick_at_new(std::uint64_t const& new_m) const
{
    assert(new_m>1 && (new_m & (new_m-1))==0); // new_m is two power.
    assert(new_m < p());
    UHash::Ref new_f;
    // TODO
    
    new_f=UHash::create(new_m,p());
    //
    assert (new_f->m() == new_m);
    assert (new_f->p() == p());
    assert (new_f->a() != a() || new_f->b() != b());
    return new_f;
}

size_t
UHash::operator()(std::uint64_t k) const
{
    assert(k < p());
    size_t hash = 0;
    // TODO
    // Hint: use static_cast to static type conversions.
    hash=static_cast<size_t>((a()*k+b())%p())%m();
    
    //
    assert(hash<m());
    return hash;
}

size_t
UHash::operator()(std::uint64_t k, size_t iter) const
{
    //The universal function has not collision algorithm.
    return this->operator()(k);
}

std::uint64_t
UHash::m() const
{
    size_t ret_v = 0;
    // TODO
    ret_v=m_;
    
    //
    return ret_v;
}

std::uint64_t
UHash::p() const
{
    size_t ret_v = 0;
    // TODO
    ret_v=p_;
    
    //
    return ret_v;
}

std::uint64_t
UHash::a() const
{
    size_t ret_v = 0;
    // TODO
    
    ret_v=a_;
    //
    return ret_v;
}

std::uint64_t
UHash::b() const
{
    size_t ret_v = 0;
    // TODO
    ret_v=b_;
    //
    return ret_v;
}


//////////////////////////////////////////////////////////////
// Linear Probing hash function.
//////////////////////////////////////////////////////////////

LPHash::LPHash(UHash::Ref hash_f)
{
    hash_f_ = hash_f;
}

OACollisionResolution::Ref
LPHash::create(UHash::Ref hash_f)
{
    return std::make_shared<LPHash>(hash_f);
}

std::uint64_t
LPHash::m() const
{
    return hash()->m();
}

UHash::Ref
LPHash::hash() const
{
    return hash_f_;
}


OACollisionResolution::Ref
LPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m>1 && (new_m & (new_m-1))==0);
    return LPHash::create(UHash::create(new_m, hash_f_->p()));    
}

size_t
LPHash::operator()(uint64_t k, size_t iter) const
{
    size_t ret_v = 0;
    //TODO
    //Remember: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Hint: you could save the first value in a static variable to avoid recompute it when
    //      a collision happened.
    if(iter==0){
            ret_v=hash()->operator()(k);
    }
    else{
            ret_v=(hash()->operator()(k)+iter)%m();
    }

    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Quadratic Probing hash function.
//////////////////////////////////////////////////////////////

QPHash::QPHash(UHash::Ref hash_f)
{
    hash_f_ = hash_f;
}

OACollisionResolution::Ref
QPHash::create(UHash::Ref hash_f)
{
    return std::make_shared<QPHash>(hash_f);
}

UHash::Ref
QPHash::hash() const
{
    return hash_f_;
}

std::uint64_t
QPHash::m() const
{
    return hash()->m();
}

OACollisionResolution::Ref
QPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m>1 && (new_m & (new_m-1))==0);
    return QPHash::create(UHash::create(new_m, hash_f_->p()));
}

size_t
QPHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v=0;
    //TODO
    //Remember: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Hint: you could save the first value to avoid recompute it when
    //      a collision happened.
    //Remember: m is two power and c1= c2 = 1/2.
    double c1=0.5;
    double c2=0.5;
    if(iter==0){
        ret_v=hash()->operator()(k);
    }
    else{
      ret_v=(uint16_t)(hash()->operator()(k)+iter*c1+iter*iter*c2)%m();
    }

    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Random Probing hash function.
//////////////////////////////////////////////////////////////

RPHash::RPHash(UHash::Ref hash_f, std::uint64_t c)
{
    hash_f_ = hash_f;
    c_ = c;
}

OACollisionResolution::Ref
RPHash::create(UHash::Ref hash_f, std::uint64_t c)
{
    return std::make_shared<RPHash>(hash_f, c);
}

UHash::Ref 
RPHash::hash() const
{
    return hash_f_;
}

std::uint64_t
RPHash::m() const
{
    return hash()->m();
}

OACollisionResolution::Ref
RPHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m>1 && (new_m & (new_m-1))==0);
    return RPHash::create(UHash::create(new_m, hash_f_->p()), (new_m<<1) - 1);
}


size_t
RPHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v=0;
    // TODO
    // Remember: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    // Hint: you could save the first value to avoid recompute it when
    //      a collision happened.    
    if(iter==0){
       ret_v=hash()->operator()(k);
    }
    else{
      ret_v=(hash()->operator()(k)+c_*iter)%m();
    }

    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Double hashing hash function.
//////////////////////////////////////////////////////////////

DHash::DHash(UHash::Ref hash1, UHash::Ref hash2)
{
    assert(hash1->m()==hash2->m());
    assert(hash1->p()==hash2->p());
    hash1_ = hash1;
    hash2_ = hash2;
}

OACollisionResolution::Ref
DHash::create(UHash::Ref hash1, UHash::Ref hash2)
{
    return std::make_shared<DHash>(hash1, hash2);
}

UHash::Ref 
DHash::hash1() const
{
    return hash1_;
}

UHash::Ref 
DHash::hash2() const
{
    return hash2_;
}

std::uint64_t
DHash::m() const
{
    return hash1()->m();
}

OACollisionResolution::Ref
DHash::pick_at_new(std::uint64_t new_m) const
{
    assert(new_m>1 && (new_m & (new_m-1))==0);
    return DHash::create(UHash::create(new_m, hash1()->p()),
                         UHash::create(new_m, hash2()->p()));
}

size_t
DHash::operator()(std::uint64_t k, size_t iter) const
{
    size_t ret_v=0;
    //TODO
    //Remember: if iter == 0 (first attempt), compute the hash value using hash1.
    //         iter>0 means a collision happened so get the next proper value
    //         using a second hash from hash2 function.
    if(iter==0){
        ret_v=hash1()->operator()(k);
    }
    else{
       ret_v=(hash1()->operator()(k)+iter*hash2()->operator()(k))%m();
    }
    
    //
    return ret_v;
}

