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
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    clearForm();
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    m_eventWidget->initTableView();
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    auto p = reinterpret_cast<const people::Person*>(b);
    qDebug() << p->firstName();
    ui->id->setText(p->id().toString());
    ui->firstName->setText(p->firstName());
    ui->familyName->setText(p->lastName());

    for(auto& evt: p->events()) {
        m_eventWidget->addEvent(evt);
    }
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    m_parentWidget->setPerson(*p);
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;
    show();
}

void EditPerson::add(bool f) {
    EditDialog::add(f);
    ui->id->setText(QUuid::createUuid().toString());
}

void EditPerson::saveForm() {
    qDebug() << __FUNCTION__ << ui->id->text();

    m_person = std::make_shared<people::Person>(QUuid::fromString(ui->id->text()));
    m_person->setFirstName(ui->firstName->text());
    m_person->setLastName(ui->familyName->text());
    m_person->setEvents(m_eventWidget->events());

    qDebug() << __FUNCTION__ << __LINE__  ;
    //if(m_parentWidget->parent(people::Parent::Type::Mother) != nullptr)
    //    m_person->addParent(people::Parent::Type::Mother, *(m_parentWidget->parent(people::Parent::Type::Mother)));
    qDebug() << __FUNCTION__ << __LINE__;
    //if(m_parentWidget->parent(people::Parent::Type::Father) != nullptr)
    //    m_person->addParent(people::Parent::Type::Father, *(m_parentWidget->parent(people::Parent::Type::Father)));
    qDebug() << __FUNCTION__ << __LINE__;
    m_eventWidget->initTableView();
    hide();

    emit save(static_cast<people::Base*>(m_person.get()));
}

