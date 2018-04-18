#ifndef EVENTFORM_H
#define EVENTFORM_H

#include "editevent.h"

#include <QMainWindow>

namespace Ui {
class EventForm;
}

class EventForm : public QMainWindow {
    Q_OBJECT

public:
    explicit EventForm(QWidget *parent = 0);
    ~EventForm();

private slots:
    void saveEvent(const people::Base*);

private:
    Ui::EventForm *ui;
    EditEvent m_addDlg;
};

#endif // EVENTFORM_H
