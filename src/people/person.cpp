#include "person.h"
#include <QDebug>
namespace people {
Person::Person(const QUuid& id):
    m_id(id) {

    // m_parents[Parent::Type::Father] = std::shared_ptr<QUuid>(new QUuid());
    // m_parents[Parent::Type::Mother] = std::shared_ptr<QUuid>(new QUuid());

}

Person::~Person() {
    qDebug() << __FUNCTION__;
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
    m_parents[t]=std::make_shared<QUuid>(i);
}

std::shared_ptr<QUuid> Person::parent(Parent::Type t) const {
    qDebug() << __FUNCTION__ << __FILE__ << __LINE__ << m_parents.size();
    auto itr = m_parents.find(t);
    qDebug() << __FUNCTION__ << __FILE__ << __LINE__;
    if(itr != m_parents.end()) {
        qDebug() << __FUNCTION__ << __FILE__ << __LINE__;
        return (*itr).second;
    }
    qDebug() << __FUNCTION__ << __FILE__ << __LINE__;
    return std::shared_ptr<QUuid>();
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

Person::Sex Person::sex() const {
    return m_sex;
}

void Person::setSex(const Sex &sex) {
    m_sex = sex;
}

QString Person::toString() const {
    QString ret("ID=%1, FN=%2, LN=%3, SX=%4, EVTS[%5], PARENTS[%6], ALIVE=%7 ");

    /*  QUuid       m_id;
      QString     m_firstName;
      QString     m_lastName;
      Sex         m_sex;

      QList<Event> m_events;
      std::map<Parent::Type, std::shared_ptr<QUuid>> m_parents;

      bool        m_alive {true};
      */
    return ret.arg(m_id.toString())
           .arg("m_firstName")
           .arg("m_lastName")
           .arg(QString::number(0))
           .arg(QString::number(0))
           .arg(QString::number(0))
           .arg(m_alive ? "yes" : "no");
}


} /* namespace people */
