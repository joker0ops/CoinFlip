#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int LevelIndex, QWidget *parent = nullptr);
    int LevelIndex;
    void paintEvent(QPaintEvent *);
    // 维护金币坐标
    // 注意坐标信息一定要放到成员变量中而不是构造函数中，防止构造函数执行结束后释放成员变量导致指针访问越界
    MyCoin* CoinMap[4][4];
signals:
    void BackBtnPressed();
};

#endif // PLAYSCENE_H
