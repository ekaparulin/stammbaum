#ifndef PEOPLE_PERSON_H
#define PEOPLE_PERSON_H

#include "base.h"
#include "event.h"

#include <QDateTime>

namespace people {

class Person: public Base {
public:
    Person();
    ~Person();

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    bool alive() const;
    void setAlive(bool alive);

    int fatherId() const;
    void setFatherId(int fatherId);

    int motherId() const;
    void setMotherId(int motherId);

    int id() const;
    void setId(int id);

    QList<Event> events() const;
    void setEvents(const QList<Event> &events);
    const Event& event(Event::Type) const;
    void addEvent(const Event&);

private:
    int         m_id {0};
    QString     m_firstName;
    QString     m_lastName;
    QList<Event> m_events;

    bool        m_alive {true};
    int         m_fatherId {0};
    int         m_motherId {0};
};

}
#endif // PEOPLE_PERSON_H
