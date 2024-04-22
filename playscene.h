#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlayScene(QWidget *parent = nullptr);
    explicit PlayScene(int LevelIndex, QWidget *parent = nullptr);
    int LevelIndex;
    void paintEvent(QPaintEvent *);
signals:
    void BackBtnPressed();
};

#endif // PLAYSCENE_H
