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

people::Person::Sex EditParent::parentsGender() {
    people::Person::Sex sex;
    switch(m_type) {
    case people::Parent::Type::Father:
        sex = people::Person::Sex::Male;
        break;
    case people::Parent::Type::Mother:
        sex = people::Person::Sex::Female;
        break;
    }

    return sex;
}

void EditParent::edit(const std::shared_ptr<const people::Person>&p) {

    // Populate table filtered by parent gender
    QString query(QString("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people where SEX = %1").arg(QString::number(static_cast<int>(parentsGender()))));
    m_model.setQuery(query);
    show();

    if(p == nullptr) {
        return;
    }

    // Filter out yourself from parent list
    m_model.setQuery(query + QString(" AND ID != \"%1\"").arg(p->id().toString()));

    if(p->parent(m_type).use_count() == 0 || p->parent(m_type)->isNull()) {
        return;
    }

    // TODO: p->parent(t) should be highlighted in the table
    for(int i = 0; i < m_model.rowCount(); ++i) {
        if(m_model.data(m_model.index(i, 0)).toString()
                .compare(p->parent(m_type)->toString()) != 0) {
            continue;
        }
        ui->tableView->setCurrentIndex(m_model.index(i, 0));
        break;
    }

}

void EditParent::addPerson() {
    qDebug() << __FUNCTION__;
}

void EditParent::saveParent() {
    emit save(QUuid::fromString(m_model.data(m_model.index(ui->tableView->currentIndex().row(), 0)).toString()));
}
