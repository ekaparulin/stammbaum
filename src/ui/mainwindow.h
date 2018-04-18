#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editperson.h"
#include "db/dbmanager.h"

#include <QActionGroup>
#include <QMainWindow>
#include <QSqlQueryModel>

namespace people {
class Base;
}
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void savePerson(const people::Base *);
    void personListClicked(const QModelIndex &);
    void personMenu(QPoint);
    void editPerson(QAction *);
    void deletePerson(QAction *);

private:
    void loadModel();
    QActionGroup *personMenuItem(QMenu *menu, QModelIndex index, const QString&);
private:

    Ui::MainWindow          *ui;
    QSqlQueryModel          m_model;
    db::Manager::ManagerPtr m_dbmPtr;
    EditPerson              m_editPersonDlg;
};

#endif // MAINWINDOW_H
