#include "editparent.h"
#include "ui_editparent.h"

#include <QDebug>

EditParent::EditParent(QWidget *parent, people::Parent::Type t) :
    QDialog(parent),
    ui(new Ui::EditParent),
    m_type(t) {
    ui->setupUi(this);

    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(addPerson()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveParent()));
}

EditParent::~EditParent() {
    delete ui;
}

void EditParent::edit(std::shared_ptr<QUuid>) {
    // TODO: Populate table filtered by parent sex

    show();
}

void EditParent::addPerson() {
    qDebug() << __FUNCTION__;
}

void EditParent::saveParent() {
    qDebug() << __FUNCTION__;
}
