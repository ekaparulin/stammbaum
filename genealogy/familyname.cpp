#include "familyname.h"

namespace genealogy {

FamilyName::FamilyName():
    m_id(QUuid::createUuid())
{

}

FamilyName::FamilyName(const QString& name, const QString& prefix, const QString& suffix):
    m_id(QUuid::createUuid()),
    m_prefix(prefix),
    m_name(name),
    m_suffix(suffix)
{

}

QString FamilyName::name() const
{
    return QString("%1%2%3").arg(m_prefix).arg(m_name).arg(m_suffix);
}

}
