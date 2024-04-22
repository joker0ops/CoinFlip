#include "mycoin.h"
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
}
