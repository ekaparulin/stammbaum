#ifndef EDIT_PERSON_H
#define EDIT_PERSON_H

#include "editdialog.h"
#include "people/person.h"

namespace Ui {
class EditPerson;
}

class EventWidget;
class ParentWidget;
class EditPerson : public EditDialog {
    Q_OBJECT

public:

    explicit EditPerson(QWidget *parent = 0);
    ~EditPerson();

    void edit(const people::Base*) override;
    void setGender(people::Person::Gender);
signals:
    void save(const people::Base*);

public slots:
    void add(bool) override;

private slots:
    void saveForm() override;

private:
    Ui::EditPerson  *ui;
    std::shared_ptr<people::Person> m_person {nullptr};
    std::shared_ptr<EventWidget>    m_eventWidget;
    std::shared_ptr<ParentWidget>    m_parentWidget;
};

#endif // EDIT_PERSON_H
