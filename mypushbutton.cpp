#include "mypushbutton.h"
// 在声明中添加动画对象
#include <QPropertyAnimation>
#include <QDebug>
// 如果在函数声明中使用了默认参数，那么在函数定义中不能再使用默认参数否则将会视为重定义（默认参数只能出现一次，在哪出现都可以）
// explicit关键字也仅用于构造函数的声明中而不是构造函数的定义中
MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImg = normalImg;
    this->pressImg = pressImg;

    // 定义画家
    QPixmap pix;
    // 判断图片是否能够正确导入
    if(!pix.load(normalImg)){
        qDebug() << "图片加载失败";
        // 图片加载失败，直接退出
        return ;
    }
    // 设置自定义按钮的大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置自定义样式表——记住就行，这个是自定义样式最佳设置
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置按钮图标
    this->setIcon(pix);
    // 设置图标大小，为什么要加QSize？
    this->setIconSize(QSize(pix.width(),pix.height()));
}

// jump1函数定义按钮按下时的动作：下落
void MyPushButton::jump1(){
    // 创建动画对象,geometry表示一个控件的位置和大小，这个属性描述了一个对象相对于其父对象或容器的位置和边界框
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    // 设置时间间隔，单位毫秒
    animation1->setDuration(200);
    // 创建起始位置
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 创建结束位置
    animation1->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    // 设置缓和曲线，QEasingCurvE::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    // 开始执行动画
    animation1->start();
}

// jump2函数定义按钮按下时的动作：弹起
void MyPushButton::jump2(){
    QPropertyAnimation * animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(200);
    // 注意区别，弹回动作起始位置在y()+10
    animation2->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation2->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){
    // 首先判断按压图片是否为空，不为空则继续执行（注意！这里不能写为空则返回，因为会导致开始按钮无法触发QPushbutton的按压效果
    if(pressImg != NULL){
        QPixmap pix;
        bool ret = pix.load(pressImg);
        if(!ret){
            qDebug() << normalImg << "图片加载失败";
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        // 交给父类执行按下的事件？
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvnet(QMouseEvent *e){
    if(normalImg != NULL){
        QPixmap pix;
        bool ret = pix.load(normalImg);
        if(!ret){
            qDebug() << normalImg << "图片加载失败";
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        // 交给父类执行按下的事件？
    }
    return QPushButton::mousePressEvent(e);
}
