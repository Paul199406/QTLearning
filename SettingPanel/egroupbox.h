#ifndef EGROUPBOX_H
#define EGROUPBOX_H

#include <QWidget>
#include <QGroupBox>
class EGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit EGroupBox(QWidget *parent = 0);
    void setSelected(bool b){}

signals:

public slots:
};

#endif // EGROUPBOX_H
