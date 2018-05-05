#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

#include "parentwidget.h"
#include "ui_parentwidget.h"

#define TYPE_COL 0
#define NAME_COL 1

ParentWidget::ParentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParentWidget),
    m_editMother(this, people::Parent::Type::Mother),
    m_editFather(this, people::Parent::Type::Father),
    m_dbm(db::Manager::instance()) {
    ui->setupUi(this);

    connect(ui->motherBtn, SIGNAL(clicked(bool)),this,SLOT(editMother(bool)));
    connect(ui->fatherBtn, SIGNAL(clicked(bool)),this,SLOT(editFather(bool)));

    connect(&m_editFather, SIGNAL(save(const QUuid&)), this, SLOT(saveFather(const QUuid&)));
    connect(&m_editMother, SIGNAL(save(const QUuid&)), this, SLOT(saveMother(const QUuid&)));
}

ParentWidget::~ParentWidget() {
    delete ui;
}

void ParentWidget::editFather(bool) {
    m_editFather.edit(m_person);
}

void ParentWidget::editMother(bool) {
    m_editMother.edit(m_person);
}

void ParentWidget::saveFather(const QUuid &id) {
    m_person->addParent(people::Parent::Type::Father, id);
    updateUi();
}

void ParentWidget::saveMother(const QUuid &id) {
    m_person->addParent(people::Parent::Type::Mother, id);
    updateUi();
}

void ParentWidget::clearUi() {
    ui->motherText->setText("");
    ui->fatherText->setText("");
}

void ParentWidget::updateUi() {
    clearUi();
    auto momId = m_person->parent(people::Parent::Type::Mother);
    if(momId.use_count()) {
        ui->motherText->setText(m_dbm->person(momId->toString())->fullName());
    }

    auto dadId = m_person->parent(people::Parent::Type::Father);
    if(dadId.use_count()) {
        ui->fatherText->setText(m_dbm->person(dadId->toString())->fullName());
    }
}

void ParentWidget::setPerson(const people::Person *p) {

    m_person = std::make_shared<people::Person>(p != nullptr ? people::Person(*p): people::Person());
    updateUi();
}

const std::shared_ptr<QUuid> ParentWidget::parent(people::Parent::Type t) {
    return m_person->parent(t);
}

