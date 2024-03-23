#include "autoimage.h"
#include "ui_autoimage.h"
#include <QImage>
#include <QDebug>

AutoImage::AutoImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoImage)
{
    ui->setupUi(this);
    img_num = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myTimerUpdate()));
    timer->start(500);
}

AutoImage::~AutoImage()
{
    delete ui;
}

/*** 用于定时器更新的服务函数 ***/
void AutoImage::myTimerUpdate()
{
    img_num++;
    if(img_num>=200)
    {
        img_num = 0;
    }
    QString str;
    char buff[24];
    sprintf(buff,"./image/test_img/%d.png",img_num);
    str = QString::fromLocal8Bit(buff,sizeof(buff));

    //qDebug()<<"image:"<<str;

    QImage img(str);
    ui->label->setPixmap(QPixmap::fromImage(img));
}

void AutoImage::on_close_Btn_clicked()
{
    this->hide();
}
