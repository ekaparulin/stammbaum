#include "editperson.h"
#include "ui_editperson.h"
#include "eventwidget.h"
#include "parentwidget.h"

#include "people/person.h"
#include <QDebug>

EditPerson::EditPerson(QWidget *parent) :
    EditDialog(parent),
    ui(new Ui::EditPerson),
    m_eventWidget(new EventWidget(this)),
    m_parentWidget(new ParentWidget(this)) {

    UI_SETUP

    ui->id->setVisible(false);
    ui->tabWidget->setCurrentIndex(0);
    ui->eventsTabLayout->addWidget(m_eventWidget.get());
    ui->parentsTabLayout->addWidget(m_parentWidget.get());

}

EditPerson::~EditPerson() {
    delete ui;
}

void EditPerson::edit(const people::Base *b) {
    clearForm();
    m_eventWidget->initTableView();
    auto p = reinterpret_cast<const people::Person*>(b);
    ui->id->setText(p->id().toString());
    ui->firstName->setText(p->firstName());
    ui->familyName->setText(p->lastName());

    for(auto& evt: p->events()) {
        m_eventWidget->addEvent(evt);
    }

    ui->sex->setCurrentIndex(static_cast<int>(p->sex()));
    m_parentWidget->setPerson(p);
    show();
}

void EditPerson::add(bool f) {
    EditDialog::add(f);
    ui->id->setText(QUuid::createUuid().toString());
    m_parentWidget->setPerson(nullptr);
}

void EditPerson::saveForm() {
    qDebug() << __FUNCTION__ << ui->id->text();

    m_person = std::make_shared<people::Person>(QUuid::fromString(ui->id->text()));
    m_person->setFirstName(ui->firstName->text());
    m_person->setLastName(ui->familyName->text());
    m_person->setSex(static_cast<people::Person::Sex>(ui->sex->currentIndex()));
    m_person->setEvents(m_eventWidget->events());

    if(m_parentWidget->parent(people::Parent::Type::Mother).use_count())
        m_person->addParent(people::Parent::Type::Mother, *(m_parentWidget->parent(people::Parent::Type::Mother)));
    if(m_parentWidget->parent(people::Parent::Type::Father).use_count())
        m_person->addParent(people::Parent::Type::Father, *(m_parentWidget->parent(people::Parent::Type::Father)));

    m_eventWidget->initTableView();
    hide();

    emit save(static_cast<people::Base*>(m_person.get()));
}

