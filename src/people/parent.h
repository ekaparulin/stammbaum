#ifndef PEOPLE_PARENT_H
#define PEOPLE_PARENT_H

#include "base.h"

namespace people {

class Parent: public Base {
public:
    static const int MIN_AGE { 15 };
    static const int MAX_AGE { 50 };

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
