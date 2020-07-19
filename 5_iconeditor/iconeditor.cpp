#include <QRegion>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    /*；
指示小部件内容是西北对齐且静态的。
调整大小后，此类小部件将仅针对其自身的新可见部分接收绘画事件。
该标志由窗口小部件的作者设置或清除。
*/
    setAttribute(Qt::WA_StaticContents);
    //大小策略:告诉布局系统是否可以对这个窗口部件进行拉长或缩放，这里设置为这个窗口布局的大小提示
    //就是他的最小尺寸大小，不能缩短到比他的大小提示还要小的尺寸
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor = Qt::black;//黑色
    zoom = 8;//缩放因子被设置为8，图标中每一个像素都将会显示为一个8*8的正方形

    image = QImage(16, 16, QImage::Format_ARGB32);//初始化为16*16像素，32位AGRB（支持半透明）
    image.fill(qRgba(0, 0, 0, 0));//黑色 透明： 00   不透明：FF
}

void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void IconEditor::setZoomFactor(int newZoom)
{
    if (newZoom < 1)
        newZoom = 1;

    if (newZoom != zoom) {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

void IconEditor::setIconImage(const QImage &newImage)
{
    if (newImage != image) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();//使用新图像强制重绘这个窗口部件
        updateGeometry();//告诉包含这个窗口部件的任意布局，这个窗口部件的大小提示已经发生改变，不仅会自动适应新的大小提示
    }
}

//大小提  返回一个窗口部件的理想大小。
//在这里使用缩放因子*图片尺寸 作为这个窗口部件的理想大小。
//吐过缩放因子>=3,那么每一个方向上需要再额外增加一个像素，以便可以容纳一个网格线
QSize IconEditor::sizeHint() const
{
    QSize size = zoom * image.size();
    if (zoom >= 3)
        size += QSize(1, 1);
    return size;
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    static int cnt = 1;
    qDebug() << "paintevent:" << cnt++;
    QPainter painter(this);

    if (zoom >= 3) {
        //绘制网格线
        painter.setPen(palette().foreground().color());
        for (int i = 0; i <= image.width(); ++i)
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        for (int j = 0; j <= image.height(); ++j)
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
    }

    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty())
            {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255)
                    painter.fillRect(rect, Qt::white);
                painter.fillRect(rect, color);
            }
        }
    }
}

//设置或清空一个像素
void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {
            image.setPixel(i, j, penColor().rgba());
        } else {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3) {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    } else {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}
