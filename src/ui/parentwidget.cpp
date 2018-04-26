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

void ParentWidget::editFather(bool) {
    m_editFather.edit(m_person, people::Parent::Type::Father);
}

void ParentWidget::editMother(bool) {
    m_editMother.edit(m_person, people::Parent::Type::Mother);
}

std::shared_ptr<const people::Person> ParentWidget::person() const {
    return m_person;
}

void ParentWidget::setPerson(const people::Person p) {
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << (p.toString());
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << (m_person.use_count());
    m_person = std::make_shared<const people::Person>(p);
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << (m_person.use_count());
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

}

const std::shared_ptr<QUuid> ParentWidget::parent(people::Parent::Type t) {
    return m_person->parent(t);
}

