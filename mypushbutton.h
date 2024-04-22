#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit关键字防止以隐式类型转换的方式调用构造函数
    // 以隐式类型转换的方式调用构造函数会造成什么后果？有时可能导致程序以未知的错误运行，这样可以让代码更加清晰
    // explicit MyPushButton(QWidget *parent = nullptr);
    // 重写MyPushButton的构造函数，并让按下后的图片路径为空，使得改构造函数可同时应用于多个自定义按压按钮
    explicit MyPushButton(QString normalImg, QString pressImg="");
    // 创建两个成员属性用于保存普通状态下的按钮图片路径和按下后的按钮图片路径
    QString normalImg;
    QString pressImg;

    void jump1();
    void jump2();

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvnet(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
