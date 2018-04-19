#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include "people/event.h"
#include "editevent.h"

#include <QWidget>
#include <QMap>
#include <QActionGroup>

namespace Ui {
class EventWidget;
}

class QStandardItemModel;
class EventWidget : public QWidget {
    Q_OBJECT

public:
    explicit EventWidget(QWidget *parent = 0);
    ~EventWidget();

    void addEvent(const people::Event&);
    void initTableView();
    static const QString eventType(const people::Event::Type);
    QList<people::Event> events() const;
public:
    static const QMap<people::Event::Type, QString> TYPE_STRINGS;

private slots:
    void addEvent(bool);
    void saveEvent(const people::Base*);
    void eventMenu(QPoint pos);
    void editEvent(QAction *);
    void deleteEvent(QAction* );
    void eventDoubleClicked(const QModelIndex &);
private:
    QList<people::Event::Type> pendingEvents() const;
    QActionGroup* eventMenuItem(QMenu *, QModelIndex, const QString&);

private:
    Ui::EventWidget                    *ui;
    std::shared_ptr<QStandardItemModel> model;
    EditEvent                           m_edit;
};

#endif // EVENTWIDGET_H
