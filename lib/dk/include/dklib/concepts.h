#ifndef DK_CONCEPTS_H
#define DK_CONCEPTS_H

#define DK_SATISFIES_INTERFACE(Interface, Type) \
    static_assert(Interface<Type>);

#include "gl/gl_concepts.hpp"
#include "math/math_concepts.hpp"

#endif // DK_CONCEPTS_H
