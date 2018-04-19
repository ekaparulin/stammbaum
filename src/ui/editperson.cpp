#include "editperson.h"
#include "ui_editperson.h"
#include "eventwidget.h"

#include "people/person.h"
#include <QDebug>

EditPerson::EditPerson(QWidget *parent) :
    EditDialog(parent),
    ui(new Ui::EditPerson),
    m_eventWidget(new EventWidget(this)) {

    UI_SETUP

    ui->id->setVisible(false);
    ui->eventsTabLayout->addWidget(m_eventWidget.get());

}

EditPerson::~EditPerson() {
    delete ui;
}

void EditPerson::edit(const people::Base *b) {
    clearForm();
    m_eventWidget->initTableView();

    auto p = reinterpret_cast<const people::Person*>(b);
    qDebug() << p->firstName();
    ui->id->setValue(p->id());
    ui->firstName->setText(p->firstName());
    ui->familyName->setText(p->lastName());

    qDebug() << __FUNCTION__ << " " << p->events().size();
    for(auto& evt: p->events()) {
        qDebug() << __FUNCTION__ << " " << (int) evt.type() << evt.date();
        m_eventWidget->addEvent(evt);
    }
    show();
}

void EditPerson::saveForm() {
    qDebug() << __FUNCTION__;

    m_person = std::make_shared<people::Person>();
    m_person->setId(ui->id->value());
    m_person->setFirstName(ui->firstName->text());
    m_person->setLastName(ui->familyName->text());
    m_person->setEvents(m_eventWidget->events());

    m_eventWidget->initTableView();
    hide();

    emit save(static_cast<people::Base*>(m_person.get()));
}

