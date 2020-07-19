#include <QtGui>

#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    //默认范围是从0-255，即（0x00-0xff）
    setRange(0, 255);
    //严格控制用户输入的数据必须是一个合法的十六进制数字：接受1到8个字符，范围{'0',...,'9','A',...,'F','a',...'f'}
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}
//由QSpinBox调用，用来检查目前为止用户输入文本的合法性
QValidator::State HexSpinBox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}
//当用户按下微调控的向上或向下箭头是，QSpinBox会调用他来更新微调的编辑部分
int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

//当用户在微调框的编辑器部分输入一个值并且按下Enter时，QSpinBox就会调用它
//整数值转字符串
QString HexSpinBox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}
