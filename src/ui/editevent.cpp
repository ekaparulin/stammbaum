#include "editevent.h"
#include "ui_editevent.h"
#include "people/event.h"
#include "eventwidget.h"

#include <QDebug>

EditEvent::EditEvent(QWidget *parent) :
    EditDialog(parent),
    ui(new Ui::EditEvent) {

    UI_SETUP

}

EditEvent::~EditEvent() {
    delete ui;
}

void EditEvent::edit(const people::Base *) {
    clearForm();
    show();
}

void EditEvent::saveForm() {
    m_event = std::make_shared<people::Event>();

    m_event->setDate(QDateTime(ui->calendarWidget->selectedDate(), ui->timeEdit->time()));
    m_event->setType(static_cast<people::Event::Type>(ui->comboBox->currentData().toInt()));
    emit save(static_cast<people::Base*>(m_event.get()));
}

QList<people::Event::Type> EditEvent::types() const {
    return m_types;
}

void EditEvent::setTypes(const QList<people::Event::Type> &types) {
    m_types = types;
    ui->comboBox->clear();
    for(auto eType: m_types) {
        ui->comboBox->addItem(EventWidget::eventType(eType), QVariant(static_cast<int>(eType)));
    }

}

void EditEvent::setDate(const QDateTime &dt) {
    ui->calendarWidget->setSelectedDate(dt.date());
    ui->timeEdit->setTime(dt.time());
}

