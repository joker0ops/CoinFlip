#include "mycoin.h"
#include <QTimer>
#include <QDebug>

MyCoin::MyCoin(QString Img){
    QPixmap pixmap;
    bool ret = pixmap.load(Img);
    if(!ret){
        qDebug() << Img << "图片加载失败";
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    // 初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pixmap;
        QString path = QString(":/res/Coin000%1").arg((this->min)++);
        if(!pixmap.load(path))
            qDebug() << "Failed to load" + path;
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        // 如果大于最大值则重置最小值并停止计时器
        if(this->min > this->max){
            this->min = 1;
            timer1->stop();
            this->isAnimation = false;
        }
    });
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pixmap;
        QString path = QString(":/res/Coin000%1").arg((this->max)--);
        if(!pixmap.load(path))
            qDebug() << "Failed to load" + path;
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        // 如果大于最大值则重置最小值并停止计时器
        if(this->max < this->min){
            this->max = 8;
            timer2->stop();
            this->isAnimation = false;
        }
    });
}

void MyCoin::changeFlag(){
    if(this->Flag){
        timer1->start(30);
        this->isAnimation = true;
        this->Flag = false;
    }
    else{
        timer2->start(30);
        this->isAnimation = true;
        this->Flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation)
        return;
    else
        return QPushButton::mousePressEvent(e);
}
