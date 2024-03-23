/******************************************************************************
  文 件 名   : colortest.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef COLORTEST_H
#define COLORTEST_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include <QDateTime>

namespace Ui {
class ColorTest;
}

class ColorTest : public QWidget
{
    Q_OBJECT

public:
    explicit ColorTest(QWidget *parent = 0);
    ~ColorTest();

private slots:

    void on_close_Btn_clicked();

    void on_run_Btn_clicked();

protected slots:
    void myTimerUpdate(void);

public slots:
    void timer_handle(void);

private:
    Ui::ColorTest *ui;
    QTimer *m_timer;
    QTimer *myTimer;
    bool run_flag = false;
};

#endif // COLORTEST_H
