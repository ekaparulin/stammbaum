#ifndef EDITPARENT_H
#define EDITPARENT_H

#include <QDialog>

namespace Ui {
    class EditParent;
}

class EditParent : public QDialog
{
    Q_OBJECT

public:
    explicit EditParent(QWidget *parent = 0);
    ~EditParent();

private:
    Ui::EditParent *ui;
};

#endif // EDITPARENT_H
