/**
 * @file ip_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <algorithm>
#include "ip_utils.hpp"

std::uint64_t
IpToInt::operator() (const IP& ip) const
{
    std::uint64_t ret_val = 0l;
    //TODO
    //Remember: casting to 64 bits unsigned integer to do not loss bits.
    //Hint: mult by 2^n means shift to left n bits.
    ret_val = (static_cast<uint64_t>(ip.bytes[0]) << 24)+
              (static_cast<uint64_t>(ip.bytes[1]) << 16) +
              (static_cast<uint64_t>(ip.bytes[2]) << 8) +
              (static_cast<uint64_t>(ip.bytes[3]));
    //
    return ret_val;
}

std::ostream&
operator<< (std::ostream& out, const IP& ip)
{
    //TODO
    //Remember: we want to output the ascii code, not the char.
    out << (static_cast<uint64_t>(ip.bytes[0])) <<
           (static_cast<uint64_t>(ip.bytes[1])) <<
           (static_cast<uint64_t>(ip.bytes[2])) <<
           (static_cast<uint64_t>(ip.bytes[3]));
    //
    return out;
}

std::istream&
operator>>(std::istream& in, IP& ip) noexcept(false)
{
    //TODO
    //Hint: you can use a std::istringstream to convert from text to uint8_t.
    //Hint: you can use the std::replace algorithm to replace '.' by ' '.
    //Remember: if a wrong format is detected, throw an runtime_error exception.
    std::string text_ip;
    int v[4];
    size_t i = 0;
    in >> text_ip;
    for(const auto& entry: text_ip){
        if(entry == '.'){
            text_ip[i] = ' ';
        }
        i++;
    }

    std::istringstream iss(text_ip);
    for(size_t j = 0; j < 4; j++){
        if(!(iss >> v[j] || v[j] < 0 || v[j] > 255)){
            throw std::runtime_error("Ip: wrong input format.");
        }
        ip.bytes[j] = static_cast<uint8_t>(v[j]);
    }
    //
    return in;
}

IpToInt::Ref
IpToInt::create()
{
    return std::make_shared<IpToInt>();
}
