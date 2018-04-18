#include "editperson.h"
#include "ui_editperson.h"
#include "eventwidget.h"

#include "people/person.h"
#include <QDebug>

EditPerson::EditPerson(QWidget *parent) :
    EditDialog(parent),
    ui(new Ui::EditPerson) {

    UI_SETUP

    ui->id->setVisible(false);
    ui->gridLayout->addWidget(new EventWidget(this));
}

EditPerson::~EditPerson() {
    delete ui;
}

void EditPerson::edit(const people::Base *b) {
    clearForm();
    auto p = reinterpret_cast<const people::Person*>(b);
    qDebug() << p->firstName();
    ui->id->setValue(p->id());
    ui->firstName->setText(p->firstName());
    ui->familyName->setText(p->lastName());
    ui->birthDate->setSelectedDate(p->birthDate().date());
    ui->birthTime->setTime(p->birthDate().time());
    ui->isDead->setChecked(!p->alive());
    if(!p->alive()) {
        ui->deathDate->setSelectedDate(p->deathDate().date());
        ui->deathTime->setTime(p->deathDate().time());
    }
    show();
}

void EditPerson::saveForm() {
    qDebug() << __FUNCTION__;

    m_person = std::make_shared<people::Person>();
    m_person->setId(ui->id->value());
    m_person->setFirstName(ui->firstName->text());
    m_person->setLastName(ui->familyName->text());
    m_person->setBirthDate(QDateTime(ui->birthDate->selectedDate(), ui->birthTime->time()));
    m_person->setAlive(!ui->isDead->isChecked());
    if(m_person->alive()) {
        m_person->setDeathDate(QDateTime(ui->deathDate->selectedDate(), ui->deathTime->time()));
    }

    hide();
    emit save(static_cast<people::Base*>(m_person.get()));
}

