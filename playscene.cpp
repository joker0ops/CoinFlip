#include "playscene.h"
#include "mypushbutton.h"
#include <QPropertyAnimation>
#include "dataconfig.h"
#include "mycoin.h"
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSound>
#include <QMenuBar>
#include <QPainter>

PlayScene::PlayScene(int LevelIndex, QWidget *parent) : QMainWindow(parent)
{
    this->LevelIndex = LevelIndex;
    const char* LevelENG[21] = {"NULL", "First", "Second", "Thrid", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth",
                                "Eleventh", "Twelfth", "Thirteenth", "Fourteenth", "Fifteenth", "Sixteenth", "Seventeenth", "Eighteenth", "Nineteenth", "Twentieth"};
    qDebug() << "The " + QString(LevelENG[this->LevelIndex]) + ".th Level has been created.";
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    // 创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    // 创建按钮菜单项
    QAction *quitAction = startMenu->addAction("退出");
    // 点击退出，退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });
    MyPushButton *BackBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    BackBtn->setParent(this);
    BackBtn->move((this->width()-BackBtn->width()), (this->height()-BackBtn->height()));
    // 点击返回
    connect(BackBtn, &MyPushButton::clicked, this, [=](){
        // 添加音效
        QSound *BackSound = new QSound(":/res/BackButtonSound.wav", this);
        BackSound->play();
        // qDebug() << "点击了返回按钮";
        // 触发自定义信号返回主界面
        // 延时200ms进行触发
        QTimer::singleShot(500, this, [=](){
            // 关闭当前页面
            this->close();
            // 触发自定义信号
            emit this->BackBtnPressed();
        });
    });
    // 显示当前关卡
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("Rockwell Extra Bold");
    font.setPointSize(18);
    label->setFont(font);
    // Qt下格式化字符串的写法
    QString str = QString("Level: %1").arg(LevelIndex);
    label->setText(str);
    // 设置大小和位置
    label->setGeometry(QRect(20, this->height() - 45, 160, 50));
    // 提前创建好胜利显示图片，等待胜利信号发出时调用
    QLabel* WinLabel = new QLabel;
    QPixmap WinPix;
    WinPix.load(":/res/LevelCompletedDialogBg.png");
    WinLabel->setGeometry(0, 0, WinPix.width(), WinPix.height());
    WinLabel->setPixmap(WinPix);
    WinLabel->setParent(this);
    WinLabel->move((this->width()-WinPix.width())*0.5, -WinPix.height());
    // 导入游戏数据，绘制初始地图
    dataConfig LevelData;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            // 绘制背景图片，为什么用Label？
            QLabel *label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+j*50, 200+i*50);
            MyCoin *coin;
            if(LevelData.mData[LevelIndex][i][j] == 1){
                coin = new MyCoin(":/res/Coin0001.png");
            }
            else{
                coin = new MyCoin(":/res/Coin0008.png");
            }
            coin->setParent(this);
            coin->move(59+j*50, 203+i*50);
            coin->posX = i;
            coin->posY = j;
            coin->Flag = LevelData.mData[LevelIndex][i][j];
            // 将当前金币记录进游戏地图
            CoinMap[i][j] = coin;
            // 用金币类实现点击金币出现翻转特效，注意这里要用posX和posY来对坐标进行维护，因为构造函数只执行一次，而槽函数在过程中要执行多次
            connect(coin, &MyCoin::clicked, [=](){
                qDebug() << "The " + QString::number(coin->posX+1) + " " + QString::number(coin->posY+1) + " has been clicked!";
                coin->changeFlag();
                QTimer::singleShot(300, this, [=](){
                    if(coin->posX+1<4)
                        CoinMap[coin->posX+1][coin->posY]->changeFlag();
                    if(coin->posX-1>=0)
                        CoinMap[coin->posX-1][coin->posY]->changeFlag();
                    if(coin->posY+1<4)
                        CoinMap[coin->posX][coin->posY+1]->changeFlag();
                    if(j-1>=0)
                        CoinMap[coin->posX][coin->posY-1]->changeFlag();
                    // 维护胜利标志，需要每次点击后重置标志的值，不能放到成员函数中
                    bool WinFlag = true;
                    for(int i=0; i<4; i++){
                        for(int j=0; j<4; j++){
                            if(CoinMap[i][j]->Flag == false){
                                WinFlag = false;
                                break;
                            }
                        }
                        if(!WinFlag)
                            break;
                    }
                    if(WinFlag){
                        for(int i=0; i<4; i++){
                            for(int j=0; j<4; j++){
                                // 将所有按钮的状态标记为胜利，不可再点击
                                CoinMap[i][j]->isWin = true;
                            }
                        }
                        qDebug() << "胜利!!!";
                        QSound *WinSound = new QSound(":/res/LevelWinSound.wav", this);
                        WinSound->play();
                        QPropertyAnimation *animation = new QPropertyAnimation(WinLabel, "geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(WinLabel->x(), WinLabel->y(), WinLabel->width(), WinLabel->height()));
                        animation->setEndValue(QRect(WinLabel->x(), WinLabel->y()+114, WinLabel->width(), WinLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *){
    // 加载背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
