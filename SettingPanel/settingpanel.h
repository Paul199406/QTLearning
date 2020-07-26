#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QScrollArea>
#include "epushbutton.h"
#include "egroupbox.h"

class SettingPanel : public QWidget
{
    Q_OBJECT

public:
    SettingPanel(QWidget *parent = 0);
    ~SettingPanel();

protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void resizeEvent(QResizeEvent *event);

private:
     void initQTreeWidget();
     void initScrollAreaWidget(QTreeWidgetItem *item);
     void initSettingsWidget();
     void initPopupWidget();
     void initStartWidget();
     void initDefendWidget();
     void initRepairWidget();
     void childItemChanged(QTreeWidgetItem *item);
     void setAllSelectedFalse();

private slots:
     void slotItemClicked(QTreeWidgetItem *item, int column);
     void slotValueChanged(int value);

private:
    QPixmap backGroundPix;
    QPoint movePoint;
    bool mousePress;
    EPushButton *minButton;
    EPushButton *closeButton;
    QRect rectMove;

    QTreeWidget *treeWidget;
    QPushButton *makeSure;
    QScrollArea *scrollArea;
    QWidget *widgetScrollArea;
    bool signFlag;

    EGroupBox *functionBox;
    EGroupBox *rightmenuBox;
    EGroupBox *updatesetupBox;
    EGroupBox *startmunuBox;
    EGroupBox *userexperienceBox;
    EGroupBox *cloundplanBox;
    EGroupBox *netcloudplanBox;

    EGroupBox *defendpopBox;
    EGroupBox *onlinebuysafeBox;
    EGroupBox *mailsafeBox;
    EGroupBox *chatsafeBox;
    EGroupBox *downloadsafeBox;
    EGroupBox *repairsafeBox;
    EGroupBox *accounttaskBox;
    EGroupBox *clearrubishBox;
    EGroupBox *autostartinfoBox;
    EGroupBox *drivertipsBox;

    EGroupBox *startBox;
};

#endif // SETTINGPANEL_H
