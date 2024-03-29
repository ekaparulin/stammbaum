#ifndef EDITPARENT_H
#define EDITPARENT_H


#include "people/parent.h"
#include "people/person.h"
#include "db/dbmanager.h"
#include "editperson.h"

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

    people::Person::Gender parentsGender();

signals:
    void save(const QUuid&);

private slots:
    void addPerson();
    void saveParent();
    void savePerson(const people::Base*);

private:
    void selectParent(const QUuid&);

private:

    Ui::EditParent              *ui;
    people::Parent::Type        m_type;
    QSqlQueryModel              m_model;
    QString                     m_query;
    std::shared_ptr<EditPerson> m_ep;
};

#endif // EDITPARENT_H
