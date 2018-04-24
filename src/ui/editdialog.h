#ifndef EVENT_DIALOG_H
#define EVENT_DIALOG_H

#include "people/base.h"

#include <QDialog>

#define UI_SETUP        ui->setupUi(this); \
                        connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveForm()));

namespace people {
class Base;
}

class EditDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();

    virtual void edit(const people::Base*) = 0;

signals:
    void save(const people::Base*);

public slots:
    virtual void add(bool);

protected slots:
    virtual void saveForm() = 0;

protected:
    void clearForm();

};

#endif // EVENT_EDIT_DIALOG_H
