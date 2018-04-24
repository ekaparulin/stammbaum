#ifndef PEOPLE_PARENT_H
#define PEOPLE_PARENT_H

#include "base.h"

namespace people {

class Parent: public Base {
public:
    enum class Type: int {
        Mother,
        Father
    };

    Parent();
    Parent(const Type&, const int&);

    Type type() const;
    void setType(const Type &type);

    int id() const;
    void setId(int id);

private:
    Type m_type;
    int  m_id;
};

}
#endif // PEOPLE_PARENT_H
