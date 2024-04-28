#include "levelselectwindow.h"
// 导入QString引入Qt类型字符串转换
#include <QString>
// 引入QLable实现文字导入
#include <QLabel>
// 引入QTimer实现按键延时
#include <QTimer>
// 引入QDebug实现命令行日志输出
#include <QDebug>
// 引入QPainter头文件以添加画家
#include <QPainter>
// 引入QMenuBar头文件以添加窗口菜单项
#include<QMenuBar>
#include<QSound>
#include "playscene.h"
#include "mypushbutton.h"
LevelSelectWindow::LevelSelectWindow(QWidget *parent) : QMainWindow(parent){
    // 设置窗口大小
    this->setFixedSize(320,588);
    // 设置窗口图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置窗口标题
    this->setWindowTitle("木木龙帮你翻金币");
    // 未添加该窗口的UI界面，手动添加窗口菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);
    // 创建开始菜单
    QMenu *startMenu = bar->addMenu("开始");
    // 创建退出项菜单
    QAction *quitAction = startMenu->addAction("退出");
    // 点击退出，实现退出游戏
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
        QSound *BackSound = new QSound(":/res/BackButtonSound.wav", this);
        BackSound->play();
        QTimer::singleShot(500, this, [=](){
            // 关闭当前页面
            this->close();
            // 触发自定义信号
            emit this->BackBtnPressed();
        });
    });
    for(int i=0; i<20; i++){
        MyPushButton *LevelBtn = new MyPushButton(":/res/LevelIcon.png");
        LevelBtn->setParent(this);
        LevelBtn->move(25+(i%4)*70, 130+(i/4)*70);
        QLabel *label = new QLabel;
        label->setParent(this);
        // 注意这里字符串宽高要设置成按钮的宽高
        label->setFixedSize(LevelBtn->width(), LevelBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+(i%4)*70, 130+(i/4)*70);
        // 设置上下左右居中?
        label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        // 鼠标事件穿透?
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        connect(LevelBtn, &MyPushButton::clicked, [=](){
            QSound *ChooseSound = new QSound(":/res/TapButtonSound.wav", this);
            ChooseSound->play();
            if(pScene == NULL){
                this->hide();
                pScene = new PlayScene(i+1);
                // 设置pScene场景的打开位置为当前位置，放在show()前
                pScene->setGeometry(this->geometry());
                pScene->show();
                // PlayScene返回按钮的监听槽
                connect(pScene, &PlayScene::BackBtnPressed, [=](){
                    // 设置返回后场景的打开位置为pScene场景的位置
                    this->setGeometry(pScene->geometry());
                    this->show();
                    // 删除该scene并将指针指向空？
                    delete pScene;
                    pScene = NULL;
                });
            }
        });
    }
}

void LevelSelectWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载背景图片
    pix.load(":/res/OtherSceneBg.png");
    // 绘制背景图
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载大标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
