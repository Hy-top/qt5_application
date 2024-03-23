/******************************************************************************
  文 件 名   : filerw.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef FILERW_H
#define FILERW_H

#include <QWidget>
#include "mthread.h"
#include <QTimer>
#include <QDateTime>

namespace Ui {
class FileRw;
}

class FileRw : public QWidget
{
    Q_OBJECT

public:
    explicit FileRw(QWidget *parent = 0);
    ~FileRw();
    int g_write_file_test;
    void restart_count();

private slots:
    void on_closeBtn_clicked();

    void on_file_rw_Btn_clicked();

    void on_Cpu_Btn_clicked();

protected slots:
    void myTimerUpdate(void);

public slots:
    void file_errorSlot(int file_cnt);

private:
    Ui::FileRw *ui;
    mThread *g_mThread = NULL;
    QTimer *myTimer;
    int stress_ram;
};

#endif // FILERW_H
