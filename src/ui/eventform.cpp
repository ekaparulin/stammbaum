#include "eventform.h"
#include "ui_eventform.h"

#include "people/event.h"

#include <QDebug>

EventForm::EventForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventForm) {

    ui->setupUi(this);

    QAction *add = new QAction(tr("&Add"), this);
    connect(add, SIGNAL(triggered(bool)), &m_addDlg, SLOT(add(bool)));
    ui->toolBar->addAction(add);

    connect(&m_addDlg, SIGNAL(save(const people::Base*)), this, SLOT(saveEvent(const people::Base*)));

}

EventForm::~EventForm() {
    delete ui;
}

void EventForm::saveEvent(const people::Base* b) {
    auto e = reinterpret_cast<const people::Event*>(b);
    qDebug() << __FUNCTION__ << e->date();
}
