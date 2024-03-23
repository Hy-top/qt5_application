/******************************************************************************
  文 件 名   : main.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "maindlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard")); //虚拟键盘
    qputenv("QT_IM_MODULE",QByteArray("tgtsml"));
    QApplication a(argc, argv);


    MainDlg w;
    w.show();
    return a.exec();
}
