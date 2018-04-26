#include "editparent.h"
#include "ui_editparent.h"
#include "people/person.h"

#include <QDebug>

EditParent::EditParent(QWidget *parent, people::Parent::Type t) :
    QDialog(parent),
    ui(new Ui::EditParent),
    m_type(t) {

    ui->setupUi(this);

    this->setWindowTitle(t == people::Parent::Type::Mother ? tr("Mother") : tr("Father"));

    m_model.setQuery("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people");
    ui->tableView->setModel(&m_model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addPerson()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveParent()));
}

EditParent::~EditParent() {
    delete ui;
}

void EditParent::edit(const std::shared_ptr<const people::Person>&p,
                      people::Parent::Type t) {

    // Populate table filtered by parent sex
    people::Person::Sex sex;
    switch(t) {
    case people::Parent::Type::Father:
        sex = people::Person::Sex::Male;
        break;
    case people::Parent::Type::Mother:
        sex = people::Person::Sex::Female;
        break;
    }

    QString query(QString("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people where SEX = %1").arg(QString::number(static_cast<int>(sex))));
    m_model.setQuery(query);
    show();

    if(p == nullptr) {
        return;
    }

    // Filter out yourself from parent list
    m_model.setQuery(query + QString("AND ID != \"%1\"").arg(p->id().toString()));
    qDebug() << __LINE__ << __FUNCTION__ << p.use_count();
    qDebug() << p->toString();

    if(p->parent(t)->isNull()) {
        return;
    }

    // TODO: p->parent(t) should be highlighted in the table

}

void EditParent::addPerson() {
    qDebug() << __FUNCTION__;
}

void EditParent::saveParent() {
    qDebug() << __FUNCTION__;
}
