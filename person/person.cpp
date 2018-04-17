#include "person.h"

namespace person {
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

QDateTime Person::birthDate() const {
    return m_birthDate;
}

void Person::setBirthDate(const QDateTime &birthDate) {
    m_birthDate = birthDate;
}

QDateTime Person::deathDate() const {
    return m_deathDate;
}

void Person::setDeathDate(const QDateTime &deathDate) {
    m_deathDate = deathDate;
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
} /* namespace person */
