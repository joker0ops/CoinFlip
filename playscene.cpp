#include "playscene.h"
#include "mypushbutton.h"
#include "dataconfig.h"
#include "mycoin.h"
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QLabel>
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
    // 导入游戏数据，绘制初始地图
    MyCoin* CoinMap[4][4];
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
            // 用金币类实现点击金币出现翻转特效
            connect(coin, &MyCoin::clicked, [=](){
                qDebug() << "The " + QString(coin->posX) + " " + QString(coin->posY) + " has been clicked!";
                coin->changeFlag();
                if(i-1>=0){
                    CoinMap[i-1][j]->changeFlag();
                }
//                if(i+1<4){
//                    CoinMap[i+1][j]->changeFlag();
//                }
//                if(j-1>=0)
//                    CoinMap[i][j-1]->changeFlag();
//                if(j+1<4)
//                    CoinMap[i][j+1]->changeFlag();
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
