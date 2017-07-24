#ifndef GENEALOGY_FAMILY_H
#define GENEALOGY_FAMILY_H

#include <QSharedPointer>
#include <QVector>
#include <QPair>
#include <QDate>
#include <QUuid>

namespace genealogy {

class Person;
class Family
{
public:
    Family();
private:
    QUuid m_id;
    QPair<QSharedPointer<Person>,QSharedPointer<Person>> m_parents {nullptr, nullptr};
    QSharedPointer<QDate> m_foundation {nullptr};
    QVector<QSharedPointer<Person>> m_children;
};

}
#endif // GENEALOGY_FAMILY_H
