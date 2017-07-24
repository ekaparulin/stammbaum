#ifndef GENEALOGY_FAMILYNAME_H
#define GENEALOGY_FAMILYNAME_H

#include <QString>
#include <QUuid>

namespace genealogy {

class FamilyName
{
public:
    FamilyName();
    FamilyName(const QString& name, const QString& prefix = "", const QString& suffix = "");
    QString name() const;
private:
    QUuid m_id;
    QString m_prefix;
    QString m_name;
    QString m_suffix;
};

}
#endif // GENEALOGY_FAMILYNAME_H
