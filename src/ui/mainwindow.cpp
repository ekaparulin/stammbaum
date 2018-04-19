#include "editperson.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db/dbmanager.h"
#include "people/person.h"
#include <QSqlQueryModel>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dbmPtr(db::Manager::defaultManager()) {

    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/tree.png"));

    QAction *addPerson = new QAction(tr("&Add"), this);
    connect(addPerson, SIGNAL(triggered(bool)), &m_editPersonDlg, SLOT(add(bool)));
    ui->toolBar->addAction(addPerson);


    loadModel();
    ui->personList->setModel(&m_model);
    ui->personList->setColumnHidden(0, true);
    ui->personList->verticalHeader()->hide();
    ui->personList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->personList->horizontalHeader()->setStretchLastSection(true);

    ui->personList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->personList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(personMenu(QPoint)));


    connect(&m_editPersonDlg, SIGNAL(save(const people::Base*)), this, SLOT(savePerson(const people::Base*)));

    connect(ui->personList, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(personListClicked(const QModelIndex &)));

    this->lower();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadModel() {
    qDebug() << __FUNCTION__;
    m_model.setQuery("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people");
    m_model.setHeaderData(1, Qt::Horizontal, QObject::tr("Last name"));
    m_model.setHeaderData(2, Qt::Horizontal, QObject::tr("First name"));
    m_model.setHeaderData(3, Qt::Horizontal, QObject::tr("Born"));

}

void MainWindow::savePerson(const people::Base* b) {
    qDebug() << __FUNCTION__;

    auto p = reinterpret_cast<const people::Person*>(b);

    if(p->id() == 0) {
        m_dbmPtr->addPerson(p);
    } else {
        m_dbmPtr->updatePerson(p);
    }
    loadModel();
}

void MainWindow::personListClicked(const QModelIndex &index) {
    if (!index.isValid()) {
        return;
    }

    qDebug() << index.row() << m_model.data(m_model.index(index.row(), 0));
    m_editPersonDlg.edit(
        reinterpret_cast<const people::Base *>(
            m_dbmPtr->person(m_model.data(m_model.index(index.row(), 0)).toInt()).get()));
}

QActionGroup * MainWindow::personMenuItem(QMenu *menu, QModelIndex index,  const QString& label) {
    QActionGroup *actionGroup = new QActionGroup(menu);
    QAction *action = new QAction(label, this);
    action->setData(m_model.data(m_model.index(index.row(), 0)));
    actionGroup->addAction(action);
    menu->addAction(action);

    return actionGroup;
}

void MainWindow::personMenu(QPoint pos) {
    QModelIndex index = ui->personList->indexAt(pos);

    QMenu *menu = new QMenu(this);

    QActionGroup *editPerson = personMenuItem(menu, index, tr("Edit"));
    connect(editPerson, SIGNAL(triggered(QAction*)), this, SLOT(editPerson(QAction*)));

    QActionGroup *deletePerson = personMenuItem(menu, index, tr("Delete"));
    connect(deletePerson, SIGNAL(triggered(QAction*)), this, SLOT(deletePerson(QAction*)));

    menu->popup(ui->personList->viewport()->mapToGlobal(pos));
}

void MainWindow::editPerson(QAction *action) {
    m_editPersonDlg.edit(
        reinterpret_cast<const people::Base *>(
            m_dbmPtr->person(action->data().toInt()).get())
    );
}

void MainWindow::deletePerson(QAction* action) {
    qDebug() << action->data();

    // TODO: Messagebox are you sure?
    qDebug() << m_dbmPtr->deletePerson(action->data().toInt());

    loadModel();
}
