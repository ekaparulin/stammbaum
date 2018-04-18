#include "event.h"

namespace people {
Event::Event() {

}

Event::~Event() {

}

QDateTime Event::date() const {
    return m_date;
}

void Event::setDate(const QDateTime &date) {
    m_date = date;
}

Event::Type Event::type() const {
    return m_type;
}

void Event::setType(const Type &type) {
    m_type = type;
}
} /* namespace people */
