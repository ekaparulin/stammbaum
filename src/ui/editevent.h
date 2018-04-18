#ifndef EVENT_EDIT_DIALOG_H
#define EVENT_EDIT_DIALOG_H

#include "editdialog.h"

namespace people {
class Event;
}

namespace Ui {
class EditEvent;
}

class EditEvent : public EditDialog {
    Q_OBJECT

public:
    explicit EditEvent(QWidget *parent = 0);
    ~EditEvent();

    void edit(const people::Base*);

signals:
    void save(const people::Base*);

private slots:
    void saveForm();

private:
    Ui::EditEvent *ui;
    std::shared_ptr<people::Event> m_event {nullptr};
};

#endif // EVENT_EDIT_DIALOG_H
