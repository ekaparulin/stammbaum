#include "person.h"

namespace people {
Person::Person(const QUuid& id):
    m_id(id) {

}
Person::~Person() {

}

QString Person::firstName() const {
    return m_firstName;
}

void Person::setFirstName(const QString &firstName) {
    m_firstName = firstName;
}

QString Person::lastName() const {
    return m_lastName;
}

void Person::setLastName(const QString &lastName) {
    m_lastName = lastName;
}

bool Person::alive() const {
    return m_alive;
}

void Person::setAlive(bool alive) {
    m_alive = alive;
}

void Person::addParent(Parent::Type t, const QUuid& i) {
    m_parents[t]=i;
}

QUuid Person::parent(Parent::Type t) const {
    if(m_parents.contains(t)) {
        return m_parents[t];
    }
    throw std::exception();
}

const QUuid& Person::id() const {
    return m_id;
}

QList<Event> Person::events() const {
    return m_events;
}

void Person::setEvents(const QList<Event> &events) {
    m_events = events;
}

const Event &Person::event(Event::Type t) const {
    for(const Event& evt: m_events) {
        if(evt.type() == t) {
            return evt;
        }
    }
    throw std::exception();
}

void Person::addEvent(const Event &e) {
    m_events.append(e);
}


} /* namespace people */
