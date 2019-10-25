#ifndef VECTOREXT_H
#define VECTOREXT_H

#include <iostream>
#include <vector3d.h>

template <typename T>
std::ostream & operator << (std::ostream &os, const irr::core::vector3d<T> &v)
{
    os << v.X << " " << v.Y << " " << v.Z;
    return os;
}

#endif // VECTOREXT_H
