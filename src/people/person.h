#ifndef PEOPLE_PERSON_H
#define PEOPLE_PERSON_H

#include "base.h"
#include "event.h"
#include "parent.h"

#include <map>
#include <QUuid>

namespace people {

class Person: public Base {
public:
    using EventPtr = std::shared_ptr<Event>;
    using UuidPtr = std::shared_ptr<QUuid>;
    enum class Gender: int {
        Unknown,
        Male,
        Female
    };

    Person(const QUuid& id = QUuid::createUuid());
    ~Person();

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString fullName() const;

    bool alive() const;
    void setAlive(bool alive);

    void addParent(Parent::Type, const QUuid&);
    UuidPtr parent(Parent::Type) const;

    const QUuid& id() const;

    QList<Event> events() const;
    void setEvents(const QList<Event> &events);
    EventPtr event(Event::Type) const;
    void addEvent(const Event&);

    Gender gender() const;
    void setGender(const Gender &gender);

    QString toString() const;

private:
    QUuid       m_id;
    QString     m_firstName;
    QString     m_lastName;
    Gender         m_gender { Gender::Unknown };

    QList<Event> m_events;
    std::map<Parent::Type, std::shared_ptr<QUuid>> m_parents;

    bool        m_alive {true};
};

}
#endif // PEOPLE_PERSON_H
