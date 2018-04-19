#ifndef EVENT_H
#define EVENT_H

#include "base.h"

#include <QDateTime>
#include <QObject>

namespace people {
class Event: public Base {
public:
    enum class Type: int {
        Birth,
        Death
    };

    Event();
    Event(Event::Type t, const QDateTime& d);
    ~Event();

    QDateTime date() const;
    void setDate(const QDateTime &date);

    Type type() const;
    void setType(const Type &type);

private:
    Type      m_type;
    QDateTime m_date;
};
} /* namespace people */
#endif // EVENT_H
