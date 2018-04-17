#include "editperson.h"
#include "ui_editperson.h"

#include <person/person.h>
#include <QDebug>

EditPerson::EditPerson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPerson) {
    ui->setupUi(this);
    ui->id->setVisible(false);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveForm()));
    hide();
}

EditPerson::~EditPerson() {
    delete ui;
}

void EditPerson::edit(const person::Person &p) {
    clearForm();
    qDebug() << p.firstName();
    ui->id->setValue(p.id());
    ui->firstName->setText(p.firstName());
    ui->familyName->setText(p.lastName());
    ui->birthDate->setSelectedDate(p.birthDate().date());
    ui->birthTime->setTime(p.birthDate().time());
    ui->isDead->setChecked(!p.alive());
    if(!p.alive()) {
        ui->deathDate->setSelectedDate(p.deathDate().date());
        ui->deathTime->setTime(p.deathDate().time());
    }
    show();
}

void EditPerson::add(bool) {
    clearForm();
    show();
}

void EditPerson::saveForm() {
    qDebug() << __FUNCTION__;

    //m_dbmPtr->addPerson();
    //ui->firstName->text()

    person::Person p;
    p.setId(ui->id->value());
    p.setFirstName(ui->firstName->text());
    p.setLastName(ui->familyName->text());
    p.setBirthDate(QDateTime(ui->birthDate->selectedDate(), ui->birthTime->time()));
    p.setAlive(!ui->isDead->isChecked());
    if(p.alive()) {
        p.setDeathDate(QDateTime(ui->deathDate->selectedDate(), ui->deathTime->time()));
    }

    hide();
    emit save(p);
}

void EditPerson::clearForm() {
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
    foreach(QCalendarWidget *widget, this->findChildren<QCalendarWidget*>()) {
        widget->setSelectedDate(QDate::currentDate());
    }
    foreach(QTimeEdit *widget, this->findChildren<QTimeEdit*>()) {
        widget->setTime(QTime::currentTime());
    }
    foreach(QCheckBox *widget, this->findChildren<QCheckBox*>()) {
        widget->setChecked(false);
    }
    foreach(QSpinBox *widget, this->findChildren<QSpinBox*>()) {
        widget->setValue(0);
    }
}
