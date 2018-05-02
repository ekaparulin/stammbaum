#include "eventwidget.h"
#include "ui_eventwidget.h"


#include <QStandardItemModel>
#include <QMenu>
#include <QDebug>

#define TYPE_COL 0
#define DATE_COL 1

const QMap<people::Event::Type, QString> EventWidget::TYPE_STRINGS {
    {people::Event::Type::Birth, QObject::tr("Birth")},
    {people::Event::Type::Death, QObject::tr("Death")}
};

EventWidget::EventWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventWidget),
    model(new QStandardItemModel(0,2,this)),
    m_edit(this) {

    ui->setupUi(this);

    initTableView();

    connect(ui->newEventBtn,SIGNAL(clicked(bool)), this, SLOT(addEvent(bool)));
    connect(&m_edit, SIGNAL(save(const people::Base*)), this, SLOT(saveEvent(const people::Base *)));

    connect(ui->eventTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(eventMenu(QPoint)));
    connect(ui->eventTable, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(eventDoubleClicked(const QModelIndex &)));
}

EventWidget::~EventWidget() {
    delete ui;
}

void EventWidget::addEvent(const people::Event &e) {
    int rowNr = model->rowCount();
    for(int i=0; i< model->rowCount(); ++i) {
        if(TYPE_STRINGS.key(model->item(i, TYPE_COL)->text()) != e.type()) {
            continue;
        }
        rowNr = i;
        break;
    }

    model->setItem(rowNr, TYPE_COL, new QStandardItem(TYPE_STRINGS[e.type()]));
    model->item(rowNr, TYPE_COL)->setEditable(false);

    model->setItem(rowNr, DATE_COL, new QStandardItem(e.date().toString()));
    model->item(rowNr, DATE_COL)->setEditable(false);

    ui->newEventBtn->setEnabled(pendingEvents().size()!=0);
}

void EventWidget::initTableView() {
    model->clear();

    ui->eventTable->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->eventTable->verticalHeader()->hide();
    ui->eventTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->eventTable->horizontalHeader()->setStretchLastSection(true);

    model->setHorizontalHeaderItem(TYPE_COL, new QStandardItem(QString("Type")));
    model->setHorizontalHeaderItem(DATE_COL, new QStandardItem(QString("Value")));

    ui->eventTable->setModel(model.get());
    ui->newEventBtn->setEnabled(true);

}

const QString EventWidget::eventType(people::Event::Type t) {
    auto itr = TYPE_STRINGS.find(t);
    if(itr != TYPE_STRINGS.end()) {
        return itr.value();
    }
    return tr("Unknown");
}

QList<people::Event> EventWidget::events() const {
    QList<people::Event> ret;
    for(int i=0; i < model->rowCount(); ++i) {
        people::Event e;
        e.setType(TYPE_STRINGS.key(model->item(i, TYPE_COL)->text()));
        e.setDate(QDateTime::fromString(model->item(i, DATE_COL)->text()));
        ret.append(e);
    }
    return ret;
}

QList<people::Event::Type> EventWidget::pendingEvents() const {
    auto eventTypes = TYPE_STRINGS.keys();
    for(int i=0; i < model->rowCount(); ++i) {
        auto pos = eventTypes.indexOf(TYPE_STRINGS.key(model->item(i, TYPE_COL)->text()));
        if(pos != -1 ) {
            eventTypes.removeAt(pos);
        }
    }

    return eventTypes;
}

void EventWidget::addEvent(bool) {
    m_edit.setTypes(pendingEvents());
    m_edit.show();
}

void EventWidget::saveEvent(const people::Base *b) {
    auto e = reinterpret_cast<const people::Event*>(b);
    addEvent(*e);
}

void EventWidget::eventMenu(QPoint pos) {
    QModelIndex index = ui->eventTable->indexAt(pos);

    QMenu *menu = new QMenu(this);

    QActionGroup *editEvent = eventMenuItem(menu, index, tr("Edit"));
    connect(editEvent, SIGNAL(triggered(QAction*)), this, SLOT(editEvent(QAction*)));

    QActionGroup *deleteEvent = eventMenuItem(menu, index, tr("Delete"));
    connect(deleteEvent, SIGNAL(triggered(QAction*)), this, SLOT(deleteEvent(QAction*)));

    menu->popup(ui->eventTable->viewport()->mapToGlobal(pos));
}

QActionGroup * EventWidget::eventMenuItem(QMenu *menu, QModelIndex index,  const QString& label) {
    QActionGroup *actionGroup = new QActionGroup(menu);
    QAction *action = new QAction(label, this);
    action->setData(index.row());
    actionGroup->addAction(action);
    menu->addAction(action);

    return actionGroup;
}

void EventWidget::editEvent(QAction *action) {

    auto rowId = action->data().toInt();
    auto eType = pendingEvents();
    eType.clear();
    eType.append(TYPE_STRINGS.key(model->item(rowId, TYPE_COL)->text()));

    m_edit.setTypes(eType);
    m_edit.setDate(QDateTime::fromString(model->item(rowId, DATE_COL)->text()));;
    m_edit.show();
}

void EventWidget::deleteEvent(QAction* action) {
    model->removeRow(action->data().toInt());
}

void EventWidget::eventDoubleClicked(const QModelIndex &i) {
    QAction a;
    a.setData(i.row());
    editEvent(&a);
}
