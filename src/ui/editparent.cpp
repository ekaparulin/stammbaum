#include "editparent.h"
#include "ui_editparent.h"

EditParent::EditParent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditParent)
{
    ui->setupUi(this);
}

EditParent::~EditParent()
{
    delete ui;
}
