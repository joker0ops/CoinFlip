#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
// 在pro文件中添加multimedia模块后方可添加此头文件
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    // 重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
