#include "person.h"

namespace people {
Person::Person() {

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

int Person::fatherId() const {
    return m_fatherId;
}

void Person::setFatherId(int fatherId) {
    m_fatherId = fatherId;
}

int Person::motherId() const {
    return m_motherId;
}

void Person::setMotherId(int motherId) {
    m_motherId = motherId;
}

int Person::id() const {
    return m_id;
}

void Person::setId(int id) {
    m_id = id;
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
