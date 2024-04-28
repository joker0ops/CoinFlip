#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QString Img);
    // 记录正反标志、x坐标和y坐标
    bool Flag;
    int posX;
    int posY;
    // 改变标志，执行翻转效果
    void changeFlag();
    // 正面翻转反面定时器
    QTimer *timer1;
    // 反面翻转正面定时器
    QTimer *timer2;
    int min = 1;
    int max = 8;
    // 判断是否在翻转动画的过程中，如果是的话则禁用其他点击事件
    bool isAnimation = false;
    // 添加胜利标志，如果关卡成功通过则禁用所有金币的点击事件
    bool isWin = false;
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYCOIN_H
