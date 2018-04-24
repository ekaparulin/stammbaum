#include "parent.h"

namespace people {

Parent::Parent() {

}

Parent::Parent(const Parent::Type &t, const int &i):
    m_type(t),
    m_id(i) {

}

Parent::Type Parent::type() const {
    return m_type;
}

void Parent::setType(const Type &type) {
    m_type = type;
}

int Parent::id() const {
    return m_id;
}

void Parent::setId(int id) {
    m_id = id;
}

}
