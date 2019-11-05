//
// Created by femianjc on 9/11/19.
//

#ifndef LAB3_GLMIO_H
#define LAB3_GLMIO_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

template<int N, typename T, glm::qualifier Q>
inline std::ostream& operator<<(std::ostream& out,  glm::vec<N,T,Q> const& v ){
    return out << glm::to_string(v);
}

#endif //LAB3_GLMIO_H
