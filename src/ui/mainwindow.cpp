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
    m_dbmPtr(db::Manager::instance()) {

    ui->setupUi(this);

    setWindowIcon(QIcon(":/icons/tree.png"));

    QAction *addPerson = new QAction(tr("&Add"), this);
    connect(addPerson, SIGNAL(triggered(bool)), &m_editPersonDlg, SLOT(add(bool)));
    ui->toolBar->addAction(addPerson);


    ui->tabWidget->setCurrentIndex(0);

    loadModel();
    ui->personList->setModel(&m_model);
    ui->personList->setColumnHidden(0, true);
    ui->personList->verticalHeader()->hide();
    ui->personList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->personList->horizontalHeader()->setStretchLastSection(true);

    ui->personList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->personList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(personMenu(QPoint)));

    connect(&m_editPersonDlg, SIGNAL(save(const people::Base*)), this, SLOT(savePerson(const people::Base*)));
    connect(&m_editPersonDlg, SIGNAL(rejected()), this, SLOT(show()));
    connect(ui->personList, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(personListClicked(const QModelIndex &)));
}

MainWindow::~MainWindow() {
    delete ui;
    //m_dbmPtr.reset();
}

void MainWindow::loadModel() {
    m_model.setQuery("select ID, FAMILY_NAME, FIRST_NAME, BIRTH_DATE from people");
    m_model.setHeaderData(1, Qt::Horizontal, QObject::tr("Last name"));
    m_model.setHeaderData(2, Qt::Horizontal, QObject::tr("First name"));
    m_model.setHeaderData(3, Qt::Horizontal, QObject::tr("Born"));

}

void MainWindow::savePerson(const people::Base* b) {
    auto p = reinterpret_cast<const people::Person*>(b);

    // Look in table for an Id of the person
    bool update = false;
    for(int i=0; i< m_model.rowCount(); ++i) {
        if(m_model.data(m_model.index(i,0)).toString().compare(p->id().toString()) != 0) {
            continue;
        }
        update = true;
        break;
    }
    if(update) {
        m_dbmPtr->updatePerson(p);
    } else {
        m_dbmPtr->addPerson(p);
    }
    loadModel();
    this->show();
}

void MainWindow::personListClicked(const QModelIndex &index) {
    if (!index.isValid()) {
        return;
    }

    m_editPersonDlg.edit(
        reinterpret_cast<const people::Base *>(
            m_dbmPtr->person(m_model.data(m_model.index(index.row(), 0))
                             .toString()).get()));
    this->hide();
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
            m_dbmPtr->person(action->data().toString()).get())
    );
    this->hide();
}

void MainWindow::deletePerson(QAction* action) {
    // TODO: Messagebox are you sure?
    qDebug() << __FILE__ << __LINE__ << __FUNCTION__
             << m_dbmPtr->deletePerson(action->data().toString());

    loadModel();
}
