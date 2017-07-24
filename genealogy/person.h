#ifndef GENEALOGY_PERSON_H
#define GENEALOGY_PERSON_H

#include <QSharedPointer>
#include <QVector>
#include <QDateTime>
#include <QUuid>
#include <QStringList>


namespace genealogy {

class Family;
class FamilyName;

class Person
{
public:
    Person();

    void setDayOfBirth(const QDateTime& dayOfBirth);
    void setDayOfDeath(const QDateTime& dayOfDeath);

    void addName(const QString& name);
    void clearNames();

    void addFamilyName(const FamilyName& familyName);
    void clearFamilyNames();

    void setOriginFamily(const QSharedPointer<Family>& family);

    void addFamily(const QSharedPointer<Family>& family);
    void clearFamilies();

    QString toString() const;

private:
    QUuid m_id;
    QStringList m_names;
    QVector<FamilyName> m_familyNames;

    QSharedPointer<Family> m_origin {nullptr};

    QVector<QSharedPointer<Family>> m_families {nullptr};

    QSharedPointer<QDateTime> m_dayOfBirth {nullptr};

    QSharedPointer<QDateTime> m_dayOfDeath {nullptr};
    bool m_isAlive {true};
};

}

#endif // GENEALOGY_PERSON_H
