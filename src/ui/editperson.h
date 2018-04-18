#ifndef EDIT_PERSON_H
#define EDIT_PERSON_H

#include "editdialog.h"

namespace people {
class Person;
}

namespace Ui {
class EditPerson;
}

class EditPerson : public EditDialog {
    Q_OBJECT

public:

    explicit EditPerson(QWidget *parent = 0);
    ~EditPerson();

    void edit(const people::Base*);

signals:
    void save(const people::Base*);

private slots:
    void saveForm();

private:
    Ui::EditPerson  *ui;
    std::shared_ptr<people::Person> m_person {nullptr};
};

#endif // EDIT_PERSON_H
