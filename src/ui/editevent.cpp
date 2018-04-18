#include "editevent.h"
#include "ui_editevent.h"
#include "people/event.h"

#include <QDebug>

EditEvent::EditEvent(QWidget *parent) :
    EditDialog(parent),
    ui(new Ui::EditEvent) {

    UI_SETUP
}

EditEvent::~EditEvent() {
    delete ui;
}

void EditEvent::edit(const people::Base *b) {
    clearForm();
    // e --> UI
    auto e = reinterpret_cast<const people::Event*>(b);
    qDebug() << e->date();
    show();
}

void EditEvent::saveForm() {
    m_event = std::make_shared<people::Event>();
    m_event->setDate(QDateTime::currentDateTime());
    m_event->setType(people::Event::Type::Birth);
    emit save(static_cast<people::Base*>(m_event.get()));
}

