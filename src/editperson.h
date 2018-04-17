#ifndef EDITPERSON_H
#define EDITPERSON_H

#include "person/person.h"
#include <QDialog>


namespace Ui {
class EditPerson;
}

class EditPerson : public QDialog {
    Q_OBJECT

public:

    explicit EditPerson(QWidget *parent = 0);
    ~EditPerson();

    void edit(const person::Person&);

signals:
    void save(const person::Person&);

public slots:
    void add(bool);

private slots:
    void saveForm();

private:
    void clearForm();
private:
    Ui::EditPerson  *ui;

};

#endif // EDITPERSON_H
