#ifndef LEVELSELECTWINDOW_H
#define LEVELSELECTWINDOW_H

#include <QMainWindow>
#include <QSound>
#include "playscene.h"

class LevelSelectWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelSelectWindow(QWidget *parent = nullptr);
    // 重写绘图事件，添加背景
    void paintEvent(QPaintEvent *);
    // 声明游戏关卡界面，将游戏运行界面与关卡号绑定
    PlayScene *pScene = NULL;
signals:
    // 声明自定义信号，便于Back按钮触发以触发信号退回主界面
    void BackBtnPressed();
};

#endif // LEVELSELECTWINDOW_H
