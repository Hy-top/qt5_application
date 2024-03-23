/******************************************************************************
  文 件 名   : music.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "audio_drv.h"

extern "C"
{
    #include "hy_fun_gen.h"
}

namespace Ui {
class Music;
}

class Music : public QWidget
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = 0);
    ~Music();

protected slots:
    void myTimerUpdate(void);

private slots:
    void on_pushButton_start_playback_clicked();

    void on_pushButton_stop_playback_clicked();

    void on_pushButton_vol_add_clicked();

    void on_pushButton_vol_sub_clicked();

    void on_pushButton_btExit_clicked();

    void on_beep_Btn_clicked();

private:
    Ui::Music *ui;
    QTimer *myTimer;
    audio_drv *mAudio_drv;
    int vol_val;
    bool beep_flag = false;
};

#endif // MUSIC_H
