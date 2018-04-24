#include "parentwidget.h"
#include "ui_parentwidget.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

#define TYPE_COL 0
#define NAME_COL 1

ParentWidget::ParentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParentWidget),
    m_editMother(this, people::Parent::Type::Mother),
    m_editFather(this, people::Parent::Type::Father) {
    ui->setupUi(this);

    connect(ui->motherBtn, SIGNAL(clicked(bool)),this,SLOT(editMother(bool)));
    connect(ui->fatherBtn, SIGNAL(clicked(bool)),this,SLOT(editFather(bool)));


}

ParentWidget::~ParentWidget() {
    delete ui;
}

std::shared_ptr<QUuid> ParentWidget::mother() const {
    return m_mother;
}

void ParentWidget::setMother(const QUuid &mother) {
    m_mother = std::make_shared<QUuid>(mother);
}

std::shared_ptr<QUuid> ParentWidget::father() const {
    return m_father;
}

void ParentWidget::setFather(const QUuid &father) {
    m_father = std::make_shared<QUuid>(father);
}

void ParentWidget::editFather(bool) {
    m_editFather.edit(m_father);
}

void ParentWidget::editMother(bool) {
    m_editMother.edit(m_mother);
}

