#include <QCalendarWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTimeEdit>
#include <QComboBox>

#include "editdialog.h"
#include "ui_eventeditdialog.h"
#include "people/event.h"


EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent) {

    hide();
}

EditDialog::~EditDialog() {
}

void EditDialog::add(bool) {
    clearForm();
    show();
}

void EditDialog::clearForm() {
    foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
        widget->clear();
    }
    foreach(QCalendarWidget *widget, this->findChildren<QCalendarWidget*>()) {
        widget->setSelectedDate(QDate::currentDate());
    }
    foreach(QTimeEdit *widget, this->findChildren<QTimeEdit*>()) {
        widget->setTime(QTime::currentTime());
    }
    foreach(QCheckBox *widget, this->findChildren<QCheckBox*>()) {
        widget->setChecked(false);
    }
    foreach(QSpinBox *widget, this->findChildren<QSpinBox*>()) {
        widget->setValue(0);
    }
    foreach(QComboBox *widget, this->findChildren<QComboBox*>()) {
        widget->setCurrentIndex(0);
    }
}

