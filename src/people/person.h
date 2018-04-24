#ifndef PEOPLE_PERSON_H
#define PEOPLE_PERSON_H

#include "base.h"
#include "event.h"
#include "parent.h"

#include <QMap>
#include <QUuid>

namespace people {

class Person: public Base {
public:
    enum class Sex: int {
        Male,
        Female
    };

    Person(const QUuid& id = QUuid::createUuid());
    ~Person();

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    bool alive() const;
    void setAlive(bool alive);

    void addParent(Parent::Type, const QUuid&);
    QUuid parent(Parent::Type) const;

    const QUuid& id() const;

    QList<Event> events() const;
    void setEvents(const QList<Event> &events);
    const Event& event(Event::Type) const;
    void addEvent(const Event&);

    Sex sex() const;
    void setSex(const Sex &sex);

private:
    QUuid       m_id;
    QString     m_firstName;
    QString     m_lastName;
    Sex         m_sex;

    QList<Event> m_events;
    QMap<Parent::Type, QUuid> m_parents;

    bool        m_alive {true};
};

}
#endif // PEOPLE_PERSON_H
