#include "settingpanel.h"
#include <QHeaderView>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QScrollBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QMouseEvent>

SettingPanel::SettingPanel(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , mousePress(false)
    , signFlag(false)
{
    resize(780, 500);
    setStyleSheet("QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#FFFFFF;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  );
    backGroundPix.load(":/background.png");
    backGroundPix = backGroundPix.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    rectMove = QRect(0, 0, width(), 35);

    treeWidget = new QTreeWidget(this);
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setFont(QFont("arial", 10, QFont::Black));
    setStyleSheet("QTreeWidget{border:0px;margin-left:-20px;margin-bottom:-10px;}"
                  "QTreeView::branch {image:none;background:#F3F3F3;}"
                  "QTreeView::item{background:#F3F3F3;height:27px;color:#000000;padding:0px 0px 0px 40px}"
                  "QTreeView::item:hover{background:#ECEFE0}"
                  "QTreeView::item:selected{background:#14922D}"

                  "QScrollArea{background:transparent;}"
                  "QScrollBar::vertical{border:0px solid grey;width:10px;margin-bottom:5px;}"
                  "QScrollBar::handle:vertical{border-radius:4px;background:#DADADA;}"
                  "QScrollBar::handle:vertical:hover{background:#D0D0D0}"
                  "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#F2F2F2;}"

                  "QLabel,QRadioButton{background:transparent;color:#000000;font-family:arial;font-size:13px;}"
                  "QCheckBox{font-family:arial;font-size:13px;border-radius:2px;color:#000000;}"
                  "QCheckBox::indicator:checked{color:#FF0000}"
                  );
    treeWidget->setRootIsDecorated(false);
    treeWidget->header()->setVisible(false);
    initQTreeWidget();

    scrollArea = new QScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setFocusPolicy(Qt::NoFocus);

    makeSure = new QPushButton(this);
    makeSure->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(232,232,232);border-radius:3px;}"
                            "QPushButton:hover{border-color:green;background:#bee7fd;}");
    makeSure->setFocusPolicy(Qt::NoFocus);
    makeSure->setText(tr("sure"));
    connect(makeSure, SIGNAL(clicked()), this, SLOT(close()));


    minButton = new EPushButton(this);
    minButton->setPixName(":/min");
    minButton->setToolTip(tr("minimize"));
    connect(minButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

    closeButton = new EPushButton(this);
    closeButton->setPixName(":/close");
    closeButton->setToolTip(tr("close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    //connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(slotValueChanged(int)));
    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemClicked(QTreeWidgetItem*, int)));
    slotItemClicked(treeWidget->topLevelItem(0), 0);
}

void SettingPanel::initQTreeWidget()
{
    QTreeWidgetItem *settingItem = new QTreeWidgetItem(treeWidget);
    settingItem->setIcon(0, QIcon(QPixmap (":/setting.png")));
    settingItem->setText(0, tr("settings"));
    QTreeWidgetItem *settingItem_one = new QTreeWidgetItem(settingItem);
    settingItem_one->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_one->setText(0, tr("function"));
    QTreeWidgetItem *settingItem_two = new QTreeWidgetItem(settingItem);
    settingItem_two->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_two->setText(0, tr("rightmenu"));
    QTreeWidgetItem *settingItem_three = new QTreeWidgetItem(settingItem);
    settingItem_three->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_three->setText(0, tr("updatesetup"));
    QTreeWidgetItem *settingItem_four = new QTreeWidgetItem(settingItem);
    settingItem_four->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_four->setText(0, tr("startmunu"));
    QTreeWidgetItem *settingItem_five = new QTreeWidgetItem(settingItem);
    settingItem_five->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_five->setText(0, tr("userexperience"));
    QTreeWidgetItem *settingItem_six = new QTreeWidgetItem(settingItem);
    settingItem_six->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_six->setText(0, tr("cloundplan"));
    QTreeWidgetItem *settingItem_seven = new QTreeWidgetItem(settingItem);
    settingItem_seven->setIcon(0, QIcon(QPixmap (":/point.png")));
    settingItem_seven->setText(0, tr("netcloudplan"));

    QTreeWidgetItem *popupItem = new QTreeWidgetItem(treeWidget);
    popupItem->setIcon(0, QIcon(QPixmap (":/popwindow.png")));
    popupItem->setText(0, tr("popup"));
    QTreeWidgetItem *popupItem_one = new QTreeWidgetItem(popupItem);
    popupItem_one->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_one->setText(0, tr("defendpop"));
    QTreeWidgetItem *popupItem_two = new QTreeWidgetItem(popupItem);
    popupItem_two->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_two->setText(0, tr("onlinebuysafe"));
    QTreeWidgetItem *popupItem_three = new QTreeWidgetItem(popupItem);
    popupItem_three->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_three->setText(0, tr("mailsafe"));
    QTreeWidgetItem *popupItem_four = new QTreeWidgetItem(popupItem);
    popupItem_four->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_four->setText(0, tr("chatsafe"));
    QTreeWidgetItem *popupItem_five = new QTreeWidgetItem(popupItem);
    popupItem_five->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_five->setText(0, tr("downloadsafe"));
    QTreeWidgetItem *popupItem_six = new QTreeWidgetItem(popupItem);
    popupItem_six->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_six->setText(0, tr("repairsafe"));
    QTreeWidgetItem *popupItem_seven = new QTreeWidgetItem(popupItem);
    popupItem_seven->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_seven->setText(0, tr("accounttask"));
    QTreeWidgetItem *popupItem_eigth = new QTreeWidgetItem(popupItem);
    popupItem_eigth->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_eigth->setText(0, tr("clearrubish"));
    QTreeWidgetItem *popupItem_nine = new QTreeWidgetItem(popupItem);
    popupItem_nine->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_nine->setText(0, tr("autostartinfo"));
    QTreeWidgetItem *popupItem_ten = new QTreeWidgetItem(popupItem);
    popupItem_ten->setIcon(0, QIcon(QPixmap (":/point.png")));
    popupItem_ten->setText(0, tr("drivertips"));

    QTreeWidgetItem *startItem = new QTreeWidgetItem(treeWidget);
    startItem->setIcon(0, QIcon(QPixmap (":/start.png")));
    startItem->setText(0, tr("start"));

    QTreeWidgetItem *defendItem = new QTreeWidgetItem(treeWidget);
    defendItem->setIcon(0, QIcon(QPixmap (":/defend.png")));
    defendItem->setText(0, tr("defend"));
    QTreeWidgetItem *defendItem_one = new QTreeWidgetItem(defendItem);
    defendItem_one->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_one->setText(0, tr("htmldefend"));
    QTreeWidgetItem *defendItem_two = new QTreeWidgetItem(defendItem);
    defendItem_two->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_two->setText(0, tr("videodefend"));
    QTreeWidgetItem *defendItem_three = new QTreeWidgetItem(defendItem);
    defendItem_three->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_three->setText(0, tr("searchdefend"));
    QTreeWidgetItem *defendItem_four = new QTreeWidgetItem(defendItem);
    defendItem_four->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_four->setText(0, tr("networkdefend"));
    QTreeWidgetItem *defendItem_five = new QTreeWidgetItem(defendItem);
    defendItem_five->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_five->setText(0, tr("cameradefend"));
    QTreeWidgetItem *defendItem_six = new QTreeWidgetItem(defendItem);
    defendItem_six->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_six->setText(0, tr("driverdefend"));
    QTreeWidgetItem *defendItem_seven = new QTreeWidgetItem(defendItem);
    defendItem_seven->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_seven->setText(0, tr("chatdefend"));
    QTreeWidgetItem *defendItem_eigth = new QTreeWidgetItem(defendItem);
    defendItem_eigth->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_eigth->setText(0, tr("downloaddefend"));
    QTreeWidgetItem *defendItem_nine = new QTreeWidgetItem(defendItem);
    defendItem_nine->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_nine->setText(0, tr("udiskdefend"));
    QTreeWidgetItem *defendItem_ten = new QTreeWidgetItem(defendItem);
    defendItem_ten->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_ten->setText(0, tr("unsafedefend"));
    QTreeWidgetItem *defendItem_eleven = new QTreeWidgetItem(defendItem);
    defendItem_eleven->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_eleven->setText(0, tr("applydefend"));
    QTreeWidgetItem *defendItem_twelve = new QTreeWidgetItem(defendItem);
    defendItem_twelve->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_twelve->setText(0, tr("ieadsdefend"));
    QTreeWidgetItem *defendItem_thirteen = new QTreeWidgetItem(defendItem);
    defendItem_thirteen->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_thirteen->setText(0, tr("developmode"));
    QTreeWidgetItem *defendItem_fourteen = new QTreeWidgetItem(defendItem);
    defendItem_fourteen->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_fourteen->setText(0, tr("selfdefend"));
    QTreeWidgetItem *defendItem_fifteen = new QTreeWidgetItem(defendItem);
    defendItem_fifteen->setIcon(0, QIcon(QPixmap (":/point.png")));
    defendItem_fifteen->setText(0, tr("autodefend"));

    QTreeWidgetItem *repairItem = new QTreeWidgetItem(treeWidget);
    repairItem->setIcon(0, QIcon(QPixmap (":/repair.png")));
    repairItem->setText(0, tr("repair"));
    QTreeWidgetItem *repairItem_one = new QTreeWidgetItem(repairItem);
    repairItem_one->setIcon(0, QIcon(QPixmap (":/point.png")));
    repairItem_one->setText(0, tr("patchpath"));
    QTreeWidgetItem *repairItem_two = new QTreeWidgetItem(repairItem);
    repairItem_two->setIcon(0, QIcon(QPixmap (":/point.png")));
    repairItem_two->setText(0, tr("patchinstall"));
    QTreeWidgetItem *repairItem_three = new QTreeWidgetItem(repairItem);
    repairItem_three->setIcon(0, QIcon(QPixmap (":/point.png")));
    repairItem_three->setText(0, tr("othersetup"));
}

void SettingPanel::initScrollAreaWidget(QTreeWidgetItem *item)
{
    scrollArea->takeWidget();
    widgetScrollArea = new QWidget(this);
    widgetScrollArea->setStyleSheet("background:transparent;");
    scrollArea->setWidget(widgetScrollArea);
    functionBox = NULL;
    rightmenuBox = NULL;
    updatesetupBox = NULL;
    startmunuBox = NULL;
    userexperienceBox = NULL;
    cloundplanBox = NULL;
    netcloudplanBox = NULL;
    defendpopBox = NULL;
    onlinebuysafeBox = NULL;
    mailsafeBox = NULL;
    chatsafeBox = NULL;
    downloadsafeBox = NULL;
    repairsafeBox = NULL;
    accounttaskBox = NULL;
    clearrubishBox = NULL;
    autostartinfoBox = NULL;
    drivertipsBox = NULL;
    startBox = NULL;
    if (item->text(0) == tr("settings")) {
        initSettingsWidget();
    }
    else if (item->text(0) == tr("popup")) {
        initPopupWidget();
    }
    else if (item->text(0) == tr("start")) {
        initStartWidget();
    }
    else if (item->text(0) == tr("defend")) {
        initDefendWidget();
    }
    else if (item->text(0) == tr("repair")) {
        initRepairWidget();
    }
}

void SettingPanel::initSettingsWidget()
{
    /************settingsBox**************/
    functionBox = new EGroupBox(widgetScrollArea);
    functionBox->setTitle(tr("function"));
    functionBox->setSelected(true);
    functionBox->show();
    QLabel *label = new QLabel(functionBox);
    label->setText(tr("please goto mytools to manager if customing function"));
    label->setGeometry(15, 25, 500, 30);
    label->show();
    QPushButton *second = new QPushButton(functionBox);
    second->setStyleSheet("QPushButton{border:1px solid lightgray;background:rgb(230,230,230);border-radius:3px;}"
                          "QPushButton:hover{border-color:green;background:#bee7fd;}");
    second->setFocusPolicy(Qt::NoFocus);
    second->setText(tr("goto manager"));
    second->setGeometry(350, 25, 60, 25);
    second->show();
    QCheckBox *third = new QCheckBox(functionBox);
    third->setFocusPolicy(Qt::NoFocus);
    third->setChecked(true);
    third->setText(tr("hide the wall"));
    third->setGeometry(15, 55, 500, 30);
    third->show();
    functionBox->setGeometry(0, 0, 560, 95);
    /************rightmenuBox**************/
    rightmenuBox = new EGroupBox(widgetScrollArea);
    rightmenuBox->setTitle(tr("rightmenu"));
    rightmenuBox->show();
    QCheckBox *rfirst = new QCheckBox(rightmenuBox);
    rfirst->setFocusPolicy(Qt::NoFocus);
    rfirst->setChecked(true);
    rfirst->setText(tr("fuser add to rightmenu"));
    rfirst->setGeometry(15, 25, 500, 30);
    rfirst->show();
    QCheckBox *rsecond = new QCheckBox(rightmenuBox);
    rsecond->setFocusPolicy(Qt::NoFocus);
    rsecond->setText(tr("forcedelete add to rightmenu"));
    rsecond->setGeometry(15, 55, 500, 30);
    rsecond->show();
    QCheckBox *rthird = new QCheckBox(rightmenuBox);
    rthird->setFocusPolicy(Qt::NoFocus);
    rthird->setText(tr("cloudkill add to rightmenu"));
    rthird->setGeometry(15, 85, 500, 30);
    rthird->show();
    QCheckBox *rforth = new QCheckBox(rightmenuBox);
    rforth->setFocusPolicy(Qt::NoFocus);
    rforth->setText(tr("manager add to rightmenu"));
    rforth->setGeometry(15, 115, 500, 30);
    rforth->show();
    QCheckBox *rfive = new QCheckBox(rightmenuBox);
    rfive->setFocusPolicy(Qt::NoFocus);
    rfive->setChecked(true);
    rfive->setText(tr("deepclean add to rightmenu"));
    rfive->setGeometry(15, 145, 500, 30);
    rfive->show();
    rightmenuBox->setGeometry(0, 110, 560, 185);
    /************updatesetupBox**************/
    updatesetupBox = new EGroupBox(widgetScrollArea);
    updatesetupBox->setTitle(tr("updatesetup"));
    updatesetupBox->show();
    QRadioButton *firstRadio = new QRadioButton(updatesetupBox);
    firstRadio->setFocusPolicy(Qt::NoFocus);
    firstRadio->setChecked(true);
    firstRadio->setText(tr("auto update program"));
    firstRadio->setGeometry(15, 25, 500, 30);
    firstRadio->show();
    QRadioButton *secondRadio = new QRadioButton(updatesetupBox);
    secondRadio->setFocusPolicy(Qt::NoFocus);
    secondRadio->setText(tr("do not aotu update program"));
    secondRadio->setGeometry(15, 55, 500, 30);
    secondRadio->show();
    QCheckBox *uthird = new QCheckBox(updatesetupBox);
    uthird->setFocusPolicy(Qt::NoFocus);
    uthird->setChecked(true);
    uthird->setText(tr("do not update when game"));
    uthird->setGeometry(15, 85, 500, 30);
    uthird->show();
    QCheckBox *uthird2 = new QCheckBox(updatesetupBox);
    uthird2->setFocusPolicy(Qt::NoFocus);
    uthird2->setChecked(true);
    uthird2->setText(tr("do not update when 3G"));
    uthird2->setGeometry(300, 85, 500, 30);
    uthird2->show();
    QCheckBox *uforth = new QCheckBox(updatesetupBox);
    uforth->setFocusPolicy(Qt::NoFocus);
    uforth->setChecked(true);
    uforth->setText(tr("accelerate upgrading by P2P or P2S"));
    uforth->setGeometry(15, 115, 500, 30);
    uforth->show();
    QCheckBox *uforth2 = new QCheckBox(updatesetupBox);
    uforth2->setFocusPolicy(Qt::NoFocus);
    uforth2->setChecked(true);
    uforth2->setText(tr("check update when using function"));
    uforth2->setGeometry(300, 115, 500, 30);
    uforth2->show();
    updatesetupBox->setGeometry(0, 310, 560, 145);
    /************startmunuBox**************/
    startmunuBox = new EGroupBox(widgetScrollArea);
    startmunuBox->setTitle(tr("startmunu"));
    startmunuBox->show();
    QCheckBox *sfirst = new QCheckBox(startmunuBox);
    sfirst->setFocusPolicy(Qt::NoFocus);
    sfirst->setChecked(true);
    sfirst->setText(tr("auto start defender when starting system"));
    sfirst->setGeometry(15, 25, 500, 30);
    sfirst->show();
    startmunuBox->setGeometry(0, 470, 560, 55);
    /************userexperienceBox**************/
    userexperienceBox = new EGroupBox(widgetScrollArea);
    userexperienceBox->setTitle(tr("userexperience"));
    userexperienceBox->show();
    QCheckBox *ufirst = new QCheckBox(userexperienceBox);
    ufirst->setFocusPolicy(Qt::NoFocus);
    ufirst->setChecked(true);
    ufirst->setText(tr("take in the plan of user experience"));
    ufirst->setGeometry(15, 25, 500, 30);
    ufirst->show();
    userexperienceBox->setGeometry(0, 540, 560, 55);
    /************cloundplanBox**************/
    cloundplanBox = new EGroupBox(widgetScrollArea);
    cloundplanBox->setTitle(tr("cloundplan"));
    cloundplanBox->show();
    QCheckBox *cfirst = new QCheckBox(cloundplanBox);
    cfirst->setFocusPolicy(Qt::NoFocus);
    cfirst->setChecked(true);
    cfirst->setText(tr("take part in cloud plan"));
    cfirst->setGeometry(15, 25, 500, 30);
    cfirst->show();
    QPushButton *csecond = new QPushButton(cloundplanBox);
    csecond->setFlat(true);
    csecond->setStyleSheet("QPushButton{border:0px;background:transparent;color:#2297E5;font-family:arial;font-size:13px;font-weight:normal;}"
                           "QPushButton:hover{border-color:green;color:#14922D}"
                           );
    csecond->setFocusPolicy(Qt::NoFocus);
    csecond->setText(tr("check the white papers"));
    csecond->setGeometry(180, 25, 500, 25);
    csecond->show();
    cloundplanBox->setGeometry(0, 610, 560, 55);
    /************netcloudplanBox**************/
    netcloudplanBox = new EGroupBox(widgetScrollArea);
    netcloudplanBox->setTitle(tr("netcloudplan"));
    netcloudplanBox->show();
    QLabel *nlabel = new QLabel(netcloudplanBox);
    nlabel->setFont(QFont("arial", 12, QFont::Normal));
    nlabel->setStyleSheet("color:#9C9C9C");
    nlabel->setText(tr("stop the dangerous website"));
    nlabel->setGeometry(38, 25, 500, 30);
    nlabel->show();
    QCheckBox *nsecond = new QCheckBox(netcloudplanBox);
    nsecond->setFocusPolicy(Qt::NoFocus);
    nsecond->setChecked(true);
    nsecond->setText(tr("take part in website cloud plan"));
    nsecond->setGeometry(15, 55, 500, 30);
    nsecond->show();
    netcloudplanBox->setGeometry(0, 680, 560, 85);

    widgetScrollArea->resize(560, 10+680+85+310);
}

void SettingPanel::initPopupWidget()
{
    /************defendpopBox**************/
    defendpopBox = new EGroupBox(widgetScrollArea);
    defendpopBox->setTitle(tr("defendpop"));
    defendpopBox->setSelected(true);
    defendpopBox->show();
    QRadioButton *intellRadio = new QRadioButton(defendpopBox);
    intellRadio->setFocusPolicy(Qt::NoFocus);
    intellRadio->setChecked(true);
    intellRadio->setText(tr("intelligence mode"));
    intellRadio->setGeometry(15, 25, 500, 30);
    intellRadio->show();
    QRadioButton *handRadio = new QRadioButton(defendpopBox);
    handRadio->setFocusPolicy(Qt::NoFocus);
    handRadio->setText(tr("hand mode"));
    handRadio->setGeometry(15, 55, 500, 30);
    handRadio->show();
    QRadioButton *autoRadio = new QRadioButton(defendpopBox);
    autoRadio->setFocusPolicy(Qt::NoFocus);
    autoRadio->setText(tr("auto mode"));
    autoRadio->setGeometry(15, 85, 500, 30);
    autoRadio->show();
    defendpopBox->setGeometry(0, 0, 560, 115);
    /************onlinebuysafeBox**************/
    onlinebuysafeBox = new EGroupBox(widgetScrollArea);
    onlinebuysafeBox->setTitle(tr("onlinebuysafe"));
    onlinebuysafeBox->show();
    QCheckBox *ofirst = new QCheckBox(onlinebuysafeBox);
    ofirst->setFocusPolicy(Qt::NoFocus);
    ofirst->setChecked(true);
    ofirst->setText(tr("scanning tips when buying"));
    ofirst->setGeometry(15, 25, 500, 30);
    ofirst->show();
    QCheckBox *osecond = new QCheckBox(onlinebuysafeBox);
    osecond->setFocusPolicy(Qt::NoFocus);
    osecond->setChecked(true);
    osecond->setText(tr("providing tips when enter"));
    osecond->setGeometry(300, 25, 500, 30);
    osecond->show();
    QCheckBox *othird = new QCheckBox(onlinebuysafeBox);
    othird->setFocusPolicy(Qt::NoFocus);
    othird->setText(tr("tips when logout"));
    othird->setGeometry(15, 55, 500, 30);
    othird->show();
    onlinebuysafeBox->setGeometry(0, 130, 560, 85);
    /************mailsafeBox**************/
    mailsafeBox = new EGroupBox(widgetScrollArea);
    mailsafeBox->setTitle(tr("mailsafe"));
    mailsafeBox->show();
    QCheckBox *mfirst = new QCheckBox(mailsafeBox);
    mfirst->setFocusPolicy(Qt::NoFocus);
    mfirst->setChecked(true);
    mfirst->setText(tr("tips when entering mail"));
    mfirst->setGeometry(15, 25, 500, 30);
    mfirst->show();
    QCheckBox *msecond = new QCheckBox(mailsafeBox);
    msecond->setFocusPolicy(Qt::NoFocus);
    msecond->setChecked(true);
    msecond->setText(tr("tips when having link in mail"));
    msecond->setGeometry(300, 25, 500, 30);
    msecond->show();
    mailsafeBox->setGeometry(0, 230, 560, 55);
    /************chatsafeBox**************/
    chatsafeBox = new EGroupBox(widgetScrollArea);
    chatsafeBox->setTitle(tr("chatsafe"));
    chatsafeBox->show();
    QCheckBox *cfirst = new QCheckBox(chatsafeBox);
    cfirst->setFocusPolicy(Qt::NoFocus);
    cfirst->setText(tr("tips when scanning the received file"));
    cfirst->setGeometry(15, 25, 500, 30);
    cfirst->show();
    QCheckBox *csecond = new QCheckBox(chatsafeBox);
    csecond->setFocusPolicy(Qt::NoFocus);
    csecond->setChecked(true);
    csecond->setText(tr("tips when the unkowned file"));
    csecond->setGeometry(15, 55, 500, 30);
    csecond->show();
    QCheckBox *cthird = new QCheckBox(chatsafeBox);
    cthird->setFocusPolicy(Qt::NoFocus);
    cthird->setChecked(true);
    cthird->setText(tr("tips when the combined file"));
    cthird->setGeometry(15, 85, 500, 30);
    cthird->show();
    chatsafeBox->setGeometry(0, 300, 560, 115);
    /************downloadsafeBox**************/
    downloadsafeBox = new EGroupBox(widgetScrollArea);
    downloadsafeBox->setTitle(tr("downloadsafe"));
    downloadsafeBox->show();
    QCheckBox *dfirst = new QCheckBox(downloadsafeBox);
    dfirst->setFocusPolicy(Qt::NoFocus);
    dfirst->setText(tr("tips when downloading file"));
    dfirst->setGeometry(15, 25, 500, 30);
    dfirst->show();
    QCheckBox *dsecond = new QCheckBox(downloadsafeBox);
    dsecond->setFocusPolicy(Qt::NoFocus);
    dsecond->setChecked(true);
    dsecond->setText(tr("tips when downloading unkowned file"));
    dsecond->setGeometry(15, 55, 500, 30);
    dsecond->show();
    QCheckBox *dthird = new QCheckBox(downloadsafeBox);
    dthird->setFocusPolicy(Qt::NoFocus);
    dthird->setChecked(true);
    dthird->setText(tr("tips when downloading combined file"));
    dthird->setGeometry(15, 85, 500, 30);
    dthird->show();
    downloadsafeBox->setGeometry(0, 430, 560, 115);
    /************repairsafeBox**************/
    repairsafeBox = new EGroupBox(widgetScrollArea);
    repairsafeBox->setTitle(tr("repairsafe"));
    repairsafeBox->show();
    QRadioButton *firstRadio = new QRadioButton(repairsafeBox);
    firstRadio->setFocusPolicy(Qt::NoFocus);
    firstRadio->setText(tr("close popup,auto repair"));
    firstRadio->setGeometry(15, 25, 500, 30);
    firstRadio->show();
    QRadioButton *secondRadio = new QRadioButton(repairsafeBox);
    secondRadio->setFocusPolicy(Qt::NoFocus);
    secondRadio->setChecked(true);
    secondRadio->setText(tr("popup tips to repair"));
    secondRadio->setGeometry(15, 55, 500, 30);
    secondRadio->show();
    QRadioButton *thirdRadio = new QRadioButton(repairsafeBox);
    thirdRadio->setFocusPolicy(Qt::NoFocus);
    thirdRadio->setText(tr("close popup,not repair"));
    thirdRadio->setGeometry(15, 85, 500, 30);
    thirdRadio->show();
    repairsafeBox->setGeometry(0, 560, 560, 115);
    /************accounttaskBox**************/
    accounttaskBox = new EGroupBox(widgetScrollArea);
    accounttaskBox->setTitle(tr("accounttask"));
    accounttaskBox->show();
    QCheckBox *afirst = new QCheckBox(accounttaskBox);
    afirst->setFocusPolicy(Qt::NoFocus);
    afirst->setText(tr("display the value when finishing task"));
    afirst->setGeometry(15, 25, 500, 30);
    afirst->show();
    QCheckBox *asecond = new QCheckBox(accounttaskBox);
    asecond->setFocusPolicy(Qt::NoFocus);
    asecond->setChecked(true);
    asecond->setText(tr("tips when growing up"));
    asecond->setGeometry(15, 55, 500, 30);
    asecond->show();
    accounttaskBox->setGeometry(0, 690, 560, 85);
    /************clearrubishBox**************/
    clearrubishBox = new EGroupBox(widgetScrollArea);
    clearrubishBox->setTitle(tr("clearrubish"));
    clearrubishBox->show();
    QCheckBox *bfirst = new QCheckBox(clearrubishBox);
    bfirst->setFocusPolicy(Qt::NoFocus);
    bfirst->setText(tr("oen tips when free time"));
    bfirst->setGeometry(15, 25, 500, 30);
    bfirst->show();
    QLabel *bsecond = new QLabel(clearrubishBox);
    bsecond->setText(tr("tips frequency"));
    bsecond->setGeometry(15, 60, 500, 30);
    bsecond->show();
    QGroupBox *groupRadioButton = new QGroupBox(clearrubishBox);
    groupRadioButton->setStyleSheet("background:transparent;border:none");
    groupRadioButton->show();
    QRadioButton *bthirdRadio = new QRadioButton(groupRadioButton);
    bthirdRadio->setFocusPolicy(Qt::NoFocus);
    bthirdRadio->setChecked(true);
    bthirdRadio->setText(tr("every day"));
    bthirdRadio->setGeometry(0, 0, 80, 30);
    bthirdRadio->show();
    QRadioButton *bthirdRadio2 = new QRadioButton(groupRadioButton);
    bthirdRadio2->setFocusPolicy(Qt::NoFocus);
    bthirdRadio2->setText(tr("every two days"));
    bthirdRadio2->setGeometry(100, 0, 80, 30);
    bthirdRadio2->show();
    QRadioButton *bthirdRadio3 = new QRadioButton(groupRadioButton);
    bthirdRadio3->setFocusPolicy(Qt::NoFocus);
    bthirdRadio3->setText(tr("every three days"));
    bthirdRadio3->setGeometry(200, 0, 80, 30);
    bthirdRadio3->show();
    QRadioButton *bthirdRadio4 = new QRadioButton(groupRadioButton);
    bthirdRadio4->setFocusPolicy(Qt::NoFocus);
    bthirdRadio4->setText(tr("every week"));
    bthirdRadio4->setGeometry(300, 0, 80, 30);
    bthirdRadio4->show();
    groupRadioButton->setGeometry(15, 90, 500, 30);
    QLabel *bforth = new QLabel(clearrubishBox);
    bforth->setText(tr("tips standard"));
    bforth->setGeometry(15, 125, 500, 30);
    bforth->show();
    QGroupBox *groupRadioButton2 = new QGroupBox(clearrubishBox);
    groupRadioButton2->setStyleSheet("background:transparent;border:none");
    groupRadioButton2->show();
    QRadioButton *bforthRadio = new QRadioButton(groupRadioButton2);
    bforthRadio->setFocusPolicy(Qt::NoFocus);
    bforthRadio->setChecked(true);
    bforthRadio->setText(tr("100M"));
    bforthRadio->setGeometry(0, 0, 80, 30);
    bforthRadio->show();
    QRadioButton *bforthRadio2 = new QRadioButton(groupRadioButton2);
    bforthRadio2->setFocusPolicy(Qt::NoFocus);
    bforthRadio2->setChecked(true);
    bforthRadio2->setText(tr("300M"));
    bforthRadio2->setGeometry(100, 0, 80, 30);
    bforthRadio2->show();
    QRadioButton *bforthRadio3 = new QRadioButton(groupRadioButton2);
    bforthRadio3->setFocusPolicy(Qt::NoFocus);
    bforthRadio3->setChecked(true);
    bforthRadio3->setText(tr("500M"));
    bforthRadio3->setGeometry(200, 0, 80, 30);
    bforthRadio3->show();
    QRadioButton *bforthRadio4 = new QRadioButton(groupRadioButton2);
    bforthRadio4->setFocusPolicy(Qt::NoFocus);
    bforthRadio4->setChecked(true);
    bforthRadio4->setText(tr("1G"));
    bforthRadio4->setGeometry(300, 0, 80, 30);
    bforthRadio4->show();
    groupRadioButton2->setGeometry(15, 155, 500, 30);
    clearrubishBox->setGeometry(0, 790, 560, 185);
    /************autostartinfoBox**************/
    autostartinfoBox = new EGroupBox(widgetScrollArea);
    autostartinfoBox->setTitle(tr("autostartinfo"));
    autostartinfoBox->show();
    QRadioButton *afirstRadio = new QRadioButton(autostartinfoBox);
    afirstRadio->setFocusPolicy(Qt::NoFocus);
    afirstRadio->setText(tr("tips when adding start item"));
    afirstRadio->setGeometry(15, 25, 500, 30);
    afirstRadio->show();
    QRadioButton *asecondRadio = new QRadioButton(autostartinfoBox);
    asecondRadio->setFocusPolicy(Qt::NoFocus);
    asecondRadio->setChecked(true);
    asecondRadio->setText(tr("not tips when adding start item"));
    asecondRadio->setGeometry(15, 55, 500, 30);
    asecondRadio->show();
    QRadioButton *athirdRadio = new QRadioButton(autostartinfoBox);
    athirdRadio->setFocusPolicy(Qt::NoFocus);
    athirdRadio->setText(tr("not tips, auto run"));
    athirdRadio->setGeometry(15, 85, 500, 30);
    athirdRadio->show();
    autostartinfoBox->setGeometry(0, 990, 560, 115);
    /************autostartinfoBox**************/
    drivertipsBox = new EGroupBox(widgetScrollArea);
    drivertipsBox->setTitle(tr("drivertips"));
    drivertipsBox->show();
    QCheckBox *tfirst = new QCheckBox(drivertipsBox);
    tfirst->setFocusPolicy(Qt::NoFocus);
    tfirst->setChecked(true);
    tfirst->setText(tr("start the tips of hardware drivers"));
    tfirst->setGeometry(15, 25, 500, 30);
    tfirst->show();
    drivertipsBox->setGeometry(0, 1120, 560, 55);

    widgetScrollArea->resize(560, 10+1120+55+340);
}

void SettingPanel::initStartWidget()
{
    /************startBox**************/
    startBox = new EGroupBox(widgetScrollArea);
    startBox->setTitle(tr("start"));
    startBox->setSelected(true);
    startBox->show();
    QCheckBox *rfirst = new QCheckBox(startBox);
    rfirst->setFocusPolicy(Qt::NoFocus);
    rfirst->setChecked(true);
    rfirst->setText(tr("giving the time of strting"));
    rfirst->setGeometry(15, 25, 500, 30);
    rfirst->show();
    QCheckBox *rsecond = new QCheckBox(startBox);
    rsecond->setFocusPolicy(Qt::NoFocus);
    rsecond->setChecked(true);
    rsecond->setText(tr("intelligence waiting"));
    rsecond->setGeometry(15, 55, 500, 30);
    rsecond->show();
    QCheckBox *rthird = new QCheckBox(startBox);
    rthird->setFocusPolicy(Qt::NoFocus);
    rthird->setChecked(true);
    rthird->setText(tr("display special skin during festival"));
    rthird->setGeometry(15, 85, 500, 30);
    rthird->show();
    QCheckBox *rforth = new QCheckBox(startBox);
    rforth->setFocusPolicy(Qt::NoFocus);
    rforth->setChecked(true);
    rforth->setText(tr("display hot news"));
    rforth->setGeometry(15, 115, 500, 30);
    rforth->show();
    QCheckBox *rfive = new QCheckBox(startBox);
    rfive->setFocusPolicy(Qt::NoFocus);
    rfive->setChecked(true);
    rfive->setText(tr("display weather forecast"));
    rfive->setGeometry(15, 145, 500, 30);
    rfive->show();
    QCheckBox *rsix = new QCheckBox(startBox);
    rsix->setFocusPolicy(Qt::NoFocus);
    rsix->setChecked(true);
    rsix->setText(tr("display recommendation"));
    rsix->setGeometry(15, 175, 500, 30);
    rsix->show();
    QCheckBox *rseven = new QCheckBox(startBox);
    rseven->setFocusPolicy(Qt::NoFocus);
    rseven->setChecked(true);
    rseven->setText(tr("record the time of staring"));
    rseven->setGeometry(15, 205, 500, 30);
    rseven->show();
    QCheckBox *reight = new QCheckBox(startBox);
    reight->setFocusPolicy(Qt::NoFocus);
    reight->setChecked(true);
    reight->setText(tr("take part in the investigation of time"));
    reight->setGeometry(15, 235, 500, 30);
    reight->show();
    startBox->setGeometry(0, 0, 560, 265);
    widgetScrollArea->resize(560, 10+265);
}

void SettingPanel::initDefendWidget()
{

}

void SettingPanel::initRepairWidget()
{

}

void SettingPanel::childItemChanged(QTreeWidgetItem *item)
{
    QPoint widgetPos;
    setAllSelectedFalse();
    if (item->parent()->text(0) == tr("settings")) {
        if (item->text(0) == tr("function")) {
            functionBox->setSelected(true);
            widgetPos = functionBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("rightmenu")) {
            rightmenuBox->setSelected(true);
            widgetPos = rightmenuBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
        else if (item->text(0) == tr("updatesetup")) {
            updatesetupBox->setSelected(true);
            widgetPos = updatesetupBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
        else if (item->text(0) == tr("startmunu")) {
            startmunuBox->setSelected(true);
            widgetPos = startmunuBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
        else if (item->text(0) == tr("userexperience")) {
            userexperienceBox->setSelected(true);
            widgetPos = userexperienceBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
        else if (item->text(0) == tr("cloundplan")) {
            cloundplanBox->setSelected(true);
            widgetPos = cloundplanBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
        else if (item->text(0) == tr("netcloudplan")) {
            netcloudplanBox->setSelected(true);
            widgetPos = netcloudplanBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y() - 70);
        }
    }
    else if (item->parent()->text(0) == tr("popup")) {
        if (item->text(0) == tr("defendpop")) {
            defendpopBox->setSelected(true);
            widgetPos = defendpopBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("onlinebuysafe")) {
            onlinebuysafeBox->setSelected(true);
            widgetPos = onlinebuysafeBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("mailsafe")) {
            mailsafeBox->setSelected(true);
            widgetPos = mailsafeBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("chatsafe")) {
            chatsafeBox->setSelected(true);
            widgetPos = chatsafeBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("downloadsafe")) {
            downloadsafeBox->setSelected(true);
            widgetPos = downloadsafeBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("repairsafe")) {
            repairsafeBox->setSelected(true);
            widgetPos = repairsafeBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("accounttask")) {
            accounttaskBox->setSelected(true);
            widgetPos = accounttaskBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("clearrubish")) {
            clearrubishBox->setSelected(true);
            widgetPos = clearrubishBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("autostartinfo")) {
            autostartinfoBox->setSelected(true);
            widgetPos = autostartinfoBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
        else if (item->text(0) == tr("drivertips")) {
            drivertipsBox->setSelected(true);
            widgetPos = drivertipsBox->pos();
            scrollArea->verticalScrollBar()->setSliderPosition(widgetPos.y());
        }
    }
    else if (item->parent()->text(0) == tr("start")) {

    }
    else if (item->parent()->text(0) == tr("defend")) {

    }
    else if (item->parent()->text(0) == tr("repair")) {

    }
}

void SettingPanel::setAllSelectedFalse()
{
    if (functionBox) functionBox->setSelected(false);
    if (rightmenuBox) rightmenuBox->setSelected(false);
    if (updatesetupBox) updatesetupBox->setSelected(false);
    if (startmunuBox) startmunuBox->setSelected(false);
    if (userexperienceBox) userexperienceBox->setSelected(false);
    if (cloundplanBox) cloundplanBox->setSelected(false);
    if (netcloudplanBox) netcloudplanBox->setSelected(false);

    if (defendpopBox) defendpopBox->setSelected(false);
    if (onlinebuysafeBox) onlinebuysafeBox->setSelected(false);
    if (mailsafeBox) mailsafeBox->setSelected(false);
    if (chatsafeBox) chatsafeBox->setSelected(false);
    if (downloadsafeBox) downloadsafeBox->setSelected(false);
    if (repairsafeBox) repairsafeBox->setSelected(false);
    if (accounttaskBox) accounttaskBox->setSelected(false);
    if (clearrubishBox) clearrubishBox->setSelected(false);
    if (autostartinfoBox) autostartinfoBox->setSelected(false);
    if (drivertipsBox) drivertipsBox->setSelected(false);
}

void SettingPanel::slotItemClicked(QTreeWidgetItem *item, int column)
{
    int index = 0;
    signFlag = true;
    int count = treeWidget->topLevelItemCount();
    for (; index < count; index++) {
        if (item == treeWidget->topLevelItem(index)) {
            break;
        }
    }
    if (index == count) {
        childItemChanged(item);
        return;
    }
    initScrollAreaWidget(item);       //top item change

    for (index = 0; index < count; index++) {
        QTreeWidgetItem *topItem = treeWidget->topLevelItem(index);
        if (item != topItem) {
            treeWidget->collapseItem(topItem);
        }
        else {
            if (item->isExpanded()) {
                if (item->childCount() != 0) {
                    item->setSelected(false);
                }
                treeWidget->collapseItem(item);
            }
            else {
                treeWidget->expandItem(item);
                if (item->childCount() != 0) {
                    signFlag = false;
                    treeWidget->setCurrentItem(item->child(0));
                }
            }
        }
    }
}

void SettingPanel::slotValueChanged(int value)
{
    if (!signFlag) {
        setAllSelectedFalse();
        if (treeWidget->currentItem()->text(0) == tr("settings") ||
            treeWidget->currentItem()->text(0) == tr("popup")    ||
            treeWidget->currentItem()->text(0) == tr("start")    ||
            treeWidget->currentItem()->text(0) == tr("defend")   ||
            treeWidget->currentItem()->text(0) == tr("repair")
            ) {
                treeWidget->expandItem(treeWidget->currentItem());
                if (treeWidget->currentItem()->childCount() > 0) {
                    treeWidget->setCurrentItem(treeWidget->currentItem()->child(0));
                }
                else {
                    return;
                }
        }
        if (treeWidget->currentItem()->parent()->text(0) == tr("settings")) {
            QRect rect= functionBox->visibleRegion().boundingRect();
            if (!(functionBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                functionBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(0));
                return;
            }
            rect = rightmenuBox->visibleRegion().boundingRect();
            if (!(rightmenuBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                rightmenuBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(1));
                return;
            }
            rect = updatesetupBox->visibleRegion().boundingRect();
            if (!(updatesetupBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                updatesetupBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(2));
                return;
            }
            rect = startmunuBox->visibleRegion().boundingRect();
            if (!(startmunuBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                startmunuBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(3));
                return;
            }
            rect = userexperienceBox->visibleRegion().boundingRect();
            if (!(userexperienceBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                userexperienceBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(4));
                return;
            }
            rect = cloundplanBox->visibleRegion().boundingRect();
            if (!(cloundplanBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                cloundplanBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(5));
                return;
            }
            rect = netcloudplanBox->visibleRegion().boundingRect();
            if (!(netcloudplanBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                netcloudplanBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(0)->child(6));
                return;
            }
        }
        else if (treeWidget->currentItem()->parent()->text(0) == tr("popup")) {
            QRect rect= defendpopBox->visibleRegion().boundingRect();
            if (!(defendpopBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                defendpopBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(0));
                return;
            }
            rect= onlinebuysafeBox->visibleRegion().boundingRect();
            if (!(onlinebuysafeBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                onlinebuysafeBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(1));
                return;
            }
            rect= mailsafeBox->visibleRegion().boundingRect();
            if (!(mailsafeBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                mailsafeBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(2));
                return;
            }
            rect= chatsafeBox->visibleRegion().boundingRect();
            if (!(chatsafeBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                chatsafeBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(3));
                return;
            }
            rect= downloadsafeBox->visibleRegion().boundingRect();
            if (!(downloadsafeBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                downloadsafeBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(4));
                return;
            }
            rect= repairsafeBox->visibleRegion().boundingRect();
            if (!(repairsafeBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                repairsafeBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(5));
                return;
            }
            rect= accounttaskBox->visibleRegion().boundingRect();
            if (!(accounttaskBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                accounttaskBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(6));
                return;
            }
            rect= clearrubishBox->visibleRegion().boundingRect();
            if (!(clearrubishBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                clearrubishBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(7));
                return;
            }
            rect= autostartinfoBox->visibleRegion().boundingRect();
            if (!(autostartinfoBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                autostartinfoBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(8));
                return;
            }
            rect= drivertipsBox->visibleRegion().boundingRect();
            if (!(drivertipsBox->visibleRegion() - QRegion(rect.x(), rect.y(), rect.width(), 50)).isEmpty() ) {
                drivertipsBox->setSelected(true);
                treeWidget->setCurrentItem(treeWidget->topLevelItem(1)->child(9));
                return;
            }
        }
        else if (treeWidget->currentItem()->parent()->text(0) == tr("start")) {

        }
        else if (treeWidget->currentItem()->parent()->text(0) == tr("defend")) {

        }
        else if (treeWidget->currentItem()->parent()->text(0) == tr("repair")) {

        }
    }
    signFlag = false;
}

SettingPanel::~SettingPanel()
{

}

void SettingPanel::resizeEvent(QResizeEvent *event)
{
    treeWidget->setGeometry(0, 35, 190, 500 - 35 - 40);
    scrollArea->setGeometry(202, 50, this->width() - 204, this->height() - 90);
    makeSure->setGeometry(width() - 102, height() - 30, 80, 22);
    minButton->move(width() - 27 - closeButton->width(), 0);
    closeButton->move(width() - 27, 0);
    move((QApplication::desktop()->width() - width())/2,  (QApplication::desktop()->height() - height())/2);
    QWidget::resizeEvent(event);
}

void SettingPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), backGroundPix);
    painter.setFont(QFont("arial", 10, QFont::Bold));
    painter.setPen(QColor("#FFFFFF"));
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawText(QRectF(24, 8, 100, 35), tr("setupcenter"));
    painter.drawRect(QRectF(0, 35, width(), height() - 35));

    painter.setPen(QColor("#D9D9D9"));
    painter.drawLine(190, 35, 190, height() - 40);
    painter.drawLine(0, height() - 40, width(), height() - 40);
    QWidget::paintEvent(event);
}

void SettingPanel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && rectMove.contains(event->pos())) {
        mousePress = true;
    }
    movePoint = event->globalPos() - pos();
    QWidget::mousePressEvent(event);
}

void SettingPanel::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    QWidget::mouseReleaseEvent(event);
}

void SettingPanel::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress) {
        QPoint movePos = event->globalPos();
        move(movePos - movePoint);
    }
    QWidget::mouseMoveEvent(event);
}
