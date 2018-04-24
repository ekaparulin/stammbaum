#ifndef EDITPARENT_H
#define EDITPARENT_H
#include"people/parent.h"
#include <QDialog>

namespace Ui {
class EditParent;
}

class EditParent : public QDialog {
    Q_OBJECT

public:
    explicit EditParent(QWidget *parent = 0, people::Parent::Type = people::Parent::Type::Mother);
    ~EditParent();

    void edit(std::shared_ptr<QUuid>);

signals:
    void save(const QUuid&);

private slots:
    void addPerson();
    void saveParent();
private:
    Ui::EditParent *ui;
    people::Parent::Type m_type;
};

#endif // EDITPARENT_H
