#include "parentwidget.h"
#include "ui_parentwidget.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

#define TYPE_COL 0
#define NAME_COL 1

const QMap<people::Parent::Type, QString> ParentWidget::TYPE_STRINGS {
    {people::Parent::Type::Mother, QObject::tr("Father")},
    {people::Parent::Type::Mother, QObject::tr("Mother")}

};

ParentWidget::ParentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParentWidget) {
    ui->setupUi(this);

}

ParentWidget::~ParentWidget() {
    delete ui;
}
