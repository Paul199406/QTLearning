#ifndef ELINEEDIT_H
#define ELINEEDIT_H

#include <QLineEdit>
class ELineEdit : public QLineEdit
{
    Q_OBJECT
public:
    ELineEdit(QWidget *parent = NULL);
    ~ELineEdit();
    void setHint(const QString &hint);
    void setError(const bool &error);
    bool isError() { return _error; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString _hint;
    bool _error;
};

#endif // ELINEEDIT_H
