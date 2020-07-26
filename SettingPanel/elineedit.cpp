#include "elineedit.h"
#include <QPainter>

ELineEdit::ELineEdit(QWidget *parent)
    : QLineEdit(parent)
    , _hint("")
    , _error(false)
{
    setStyleSheet("QLineEdit{border:1px solid #C3C3C3;background:#77C082;color:#19649F;margin-left:8px;margin-right:10px;border-radius:5px;}"
                  "QLineEdit:hover{border: 1px solid #108F2A;}"
                  "QLineEdit:focus{border: 1px solid #108F2A;}"
                  "QLineEdit:disabled{color:#666666;border:1px solid #999999;}"
                  );
    this->setCursor(Qt::PointingHandCursor);
}

ELineEdit::~ELineEdit()
{

}

void ELineEdit::setHint(const QString &hint)
{
    _hint = hint;
    repaint();
}

void ELineEdit::setError(const bool &error)
{
    if (error) {
        setStyleSheet("QLineEdit{border:1px solid #FF0000;background:#77C082;color:#19649F;margin-left:8px;margin-right:10px;border-radius:5px;}"
                      "QLineEdit:hover{border: 1px solid #FF0000;}"
                      "QLineEdit:focus{border: 1px solid #FF0000;}"
                      "QLineEdit:disabled{color:#666666;border:1px solid #FF0000;}"
                      );
    }
    else {
        setStyleSheet("QLineEdit{border:1px solid #C3C3C3;background:#77C082;color:#19649F;margin-left:8px;margin-right:10px;border-radius:5px;}"
                      "QLineEdit:hover{border: 1px solid #108F2A;}"
                      "QLineEdit:focus{border: 1px solid #108F2A;}"
                      "QLineEdit:disabled{color:#666666;border:1px solid #999999;}"
                      );
    }
}

void ELineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
    QPainter painter(this);

    if (!this->text().isEmpty()) return;
    QRect rt = rect();
    painter.setPen(QPen(QColor("#666666")));
    painter.drawText(rt.translated(10,0), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic, _hint);
}

