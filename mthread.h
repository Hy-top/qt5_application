/******************************************************************************
  文 件 名   : mthread.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef MTHREAD_H
#define MTHREAD_H

#include <QFile>
#include <QThread>
#include <QWidget>

class mThread : public QThread
{
    Q_OBJECT
public:
    mThread(QWidget *parent = NULL);
    void run();

public:
    void file_test(void);
    void set_file_test_enable(int en);
    void file_del(void);
    int fileCompare(QString File1, QString File2);
    QString getFileMd5(QString filename);

public:
    int g_file_test;
    int show_color_timeout_flag;
    QFile *update_log_file;
    QFile *wntest_file;
    int file_error_cnt;
    int file_len;

signals:
    void setfile_error_cnt(int file_cnt);

};

#endif // MTHREAD_H
