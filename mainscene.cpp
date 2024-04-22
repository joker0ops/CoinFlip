#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QAction>
#include <QDebug>
// 引入QTimer以增加延时计时器
#include <QTimer>
#include <mypushbutton.h>
#include "levelselectwindow.h"

MainScene::MainScene(QWidget *parent): QMainWindow(parent), ui(new Ui::MainScene)
{
    ui->setupUi(this);
    // 固定主场景大小
    this->setFixedSize(320, 588);
    // 设置图标后，工具栏显示图标与底部任务栏图标相同
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置主场景窗口标题
    this->setWindowTitle("翻金币");
    // 设置退出按钮
    // 看之前的课程求解信号的发送者和信号机制，这里connect连接要放在ui->setupUI之后，保证先创建出对象再进行连接
    connect(ui->actionQuit, &QAction::triggered, [=](){
       this->close();
    });
    // 创建开始按钮，并写入构造函数需要的图片地址
    MyPushButton *StartBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    // 指定按钮的父级对象
    StartBtn->setParent(this);
    // 设置开始按钮的位置
    StartBtn->move(this->width()/2-StartBtn->width()/2, this->height()*0.7);
    // 点击开始按钮进入关卡选择页面，声明页面对象
    LevelSelectWindow *levelwindow = new LevelSelectWindow;
    connect(StartBtn, &MyPushButton::clicked, this, [=](){
        StartBtn->jump1();
        StartBtn->jump2();
        // qDebug() << "点击了开始按钮";
        // 添加延时器使得用户可以在看到开始按钮跳动后跳转到关卡选择页面，380是延时，this代表针对当前对象进行操作
        QTimer::singleShot(380, this, [=](){
            // 关闭当前页面
            this->hide();
            // 打开新页面
            levelwindow->show();
        });
    });
    connect(levelwindow, &LevelSelectWindow::BackBtnPressed, this, [=](){
        this->show();
    });
}

// 看之前的课程关于paintEvent的相关内容
void MainScene::paintEvent(QPaintEvent *){
    // 创建画家，指定绘图设备
    QPainter MuMuLong(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    // 在坐标位置绘制背景图，图片宽高为当前对象宽高
    MuMuLong.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 加载标题
    pix.load(":/res/Title.png");
    // 缩小图片（也可以在UI编辑界面直接进行缩放）
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    // 在坐标位置绘制标题图，图片宽高为重新设置的pix宽高（默认就是pix的宽高，可放可不放）
    MuMuLong.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

MainScene::~MainScene()
{
    delete ui;
}

