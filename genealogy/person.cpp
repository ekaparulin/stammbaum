#include "person.h"
#include "family.h"
#include "familyname.h"
#include <QJsonObject>
#include <QStringList>


namespace genealogy {

Person::Person():
    m_id(QUuid::createUuid())
{

}

void Person::setDayOfDeath(const QDateTime& dayOfDeath)
{
    m_dayOfDeath.reset(new QDateTime(dayOfDeath));
    m_isAlive = true;
}

void Person::addName(const QString& name)
{
    m_names.append(name);
}

void Person::addFamilyName(const FamilyName& familyName)
{
    m_familyNames.append(familyName);
}

QString Person::toString() const
{
    QStringList ret;
    QJsonObject json;

    ret << "Person: {";

    json["id"] = m_id.toString();


    for(auto key : json.keys()) {
        ret << key + " = " + json[key].toString();
    }

    ret << ", names = " + m_names.join(" ");
    ret << ", familyNames =";
    for(auto fn: m_familyNames) {
        ret << fn.name();
    }

    ret << "}";

    return ret.join(" ");
}

}
