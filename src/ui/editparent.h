#ifndef EDITPARENT_H
#define EDITPARENT_H


#include "people/parent.h"
#include "people/person.h"
#include "db/dbmanager.h"

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class EditParent;
}

class EditParent : public QDialog {
    Q_OBJECT

public:
    explicit EditParent(QWidget *parent = 0, people::Parent::Type = people::Parent::Type::Mother);
    ~EditParent();

    void edit(const std::shared_ptr<const people::Person>&);

    people::Person::Sex parentsGender();

signals:
    void save(const QUuid&);

private slots:
    void addPerson();
    void saveParent();
private:
    Ui::EditParent *ui;
    people::Parent::Type m_type;
    QSqlQueryModel  m_model;
};

#endif // EDITPARENT_H
