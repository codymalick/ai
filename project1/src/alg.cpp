#include "alg.h"

bool PrinodeComparator::operator()(const prinode& a, const prinode& b) const {
    return std::get<1>(a) > std::get<1>(b);
}