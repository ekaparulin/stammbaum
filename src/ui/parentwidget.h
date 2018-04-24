#ifndef PARENTWIDGET_H
#define PARENTWIDGET_H

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


private:
    Ui::ParentWidget *ui;
    std::shared_ptr<QStandardItemModel> model;
    EditParent                          m_edit;
};

#endif // PARENTWIDGET_H
