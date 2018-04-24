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

    std::shared_ptr<QUuid> mother() const;
    void setMother(const QUuid &mother);

    std::shared_ptr<QUuid> father() const;
    void setFather(const QUuid &father);

private slots:
    void editFather(bool);
    void editMother(bool);

private:
    Ui::ParentWidget *ui;

    EditParent                          m_editMother;
    EditParent                          m_editFather;
    std::shared_ptr<QUuid>              m_mother {nullptr};
    std::shared_ptr<QUuid>              m_father {nullptr};
};

#endif // PARENTWIDGET_H
