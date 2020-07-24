#ifndef EPUSHBUTTON_H
#define EPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class EPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit EPushButton(QWidget *parent = 0);
    void setPixName(QString str) {}
    void setToolTip(QString str) {}

signals:

public slots:
};

#endif // EPUSHBUTTON_H
