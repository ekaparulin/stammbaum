#ifndef EVENTWIDGET_H
#define EVENTWIDGET_H

#include <QWidget>

namespace Ui {
    class EventWidget;
}

class EventWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventWidget(QWidget *parent = 0);
    ~EventWidget();

private:
    Ui::EventWidget *ui;
};

#endif // EVENTWIDGET_H
