#ifndef EVENT_H
#define EVENT_H

#include "base.h"

#include <QDateTime>


namespace people {
class Event: public Base {
public:
    enum class Type {
        Birth,
        Death
    };

    Event();
    ~Event();

    QDateTime date() const;
    void setDate(const QDateTime &date);

    Type type() const;
    void setType(const Type &type);

private:
    QDateTime m_date;
    Type      m_type;
};
} /* namespace people */
#endif // EVENT_H
