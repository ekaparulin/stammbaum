#ifndef PARENTWIDGET_H
#define PARENTWIDGET_H

#include "people/person.h"
#include "people/parent.h"
#include "editparent.h"

#include <QActionGroup>
#include <QWidget>

namespace Ui {
class ParentWidget;
}

class QStandardItemModel;
class ParentWidget : public QWidget {
    Q_OBJECT

public:
    explicit ParentWidget(QWidget *parent = 0);
    ~ParentWidget();

public:
    static const QMap<people::Parent::Type, QString> TYPE_STRINGS;

    void setPerson(const people::Person *person);

    const std::shared_ptr<QUuid> parent(people::Parent::Type);

    void clearUi();

private slots:
    void editFather(bool);
    void editMother(bool);

    void saveFather(const QUuid&);
    void saveMother(const QUuid&);
private:
    void updateUi();
private:
    Ui::ParentWidget *ui;
    std::shared_ptr<people::Person>     m_person;
    EditParent                          m_editMother;
    EditParent                          m_editFather;

};

#endif // PARENTWIDGET_H
