#include <QDebug>

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

QString Person::fullName() const {
    return QString("%1 %2")
           .arg(m_firstName)
           .arg(m_lastName);
}

bool Person::alive() const {
    return m_alive;
}

void Person::setAlive(bool alive) {
    m_alive = alive;
}

void Person::addParent(Parent::Type t, const QUuid& i) {
    m_parents[t] = std::make_shared<QUuid>(i);
}

Person::UuidPtr Person::parent(Parent::Type t) const {
    UuidPtr ret;
    auto itr = m_parents.find(t);
    if(itr != m_parents.end()) {
        ret = (*itr).second;
    }
    return ret;
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

Person::EventPtr Person::event(Event::Type t) const {
    EventPtr ret;
    for(const Event& evt: m_events) {
        if(evt.type() != t) {
            continue;
        }
        ret = std::make_shared<Event>(evt);
        break;
    }
    return ret;
}

void Person::addEvent(const Event &e) {
    m_events.append(e);
}

Person::Gender Person::gender() const {
    return m_gender;
}

void Person::setGender(const Gender &g) {
    m_gender = g;
}

QString Person::toString() const {
    QString ret("ID=%1, FN=%2, LN=%3, SX=%4, EVTS[%5], PARENTS[%6], ALIVE=%7 ");
    return ret.arg(m_id.toString())
           .arg("m_firstName")
           .arg("m_lastName")
           .arg(QString::number(0))
           .arg(QString::number(0))
           .arg(QString::number(0))
           .arg(m_alive ? "yes" : "no");
}


} /* namespace people */
