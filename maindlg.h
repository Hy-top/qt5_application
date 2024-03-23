/******************************************************************************
  文 件 名   : maindlg.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include <QTimer>
#include "can_drv.h"
#include "cansendthread.h"
#include "canreceivethread.h"
#include "page1.h"
#include "colortest.h"
#include "rtc.h"
#include "autoimage.h"
#include "touch.h"

namespace Ui {
class MainDlg;
}

class MainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MainDlg(QWidget *parent = 0);
    ~MainDlg();
    int g_write_file_test;

private slots:

    void on_touch_Btn_clicked();

    void on_FM_Btn_clicked();

    void on_bt_Btn_clicked();

    void on_color_btn_clicked();

    void on_AHD_Btn_clicked();

    void on_WiFi_Btn_clicked();

    void on_File_Btn_clicked();

    void on_time_Btn_clicked();

    void on_SN_Btn_clicked();

    void on_face_Btn_clicked();

    void on_ahd2_Btn_clicked();

    void on_voice_Btn_clicked();

    void on_health_Btn_clicked();

    void on_backlight_Btn_clicked();

    void on_warn_Btn_clicked();

    void on_app_Btn_clicked();

    void on_fm3_Btn_clicked();

    void on_video2_Btn_clicked();

    void on_bt2_Btn_clicked();

    void on_map_Btn_clicked();

    void on_Set_Btn_clicked();

    void on_Music_Btn_clicked();

    void on_canBtn_clicked();

private:
    Ui::MainDlg *ui;
    QTimer *myTimer;
    page1 *page_1 = NULL;
    Rtc *page_rtc = NULL;
    AutoImage *page_autoimg = NULL;
    Touch *page_touch = NULL;

    // canbus - can0
    CAN_Drv* mCan1;
    CanSendThread* mCan1SendThread;
    CanReceiveThread* mCan1ReceiveThread;

    // canbus - can1
    CAN_Drv* mCan2;
    CanSendThread* mCan2SendThread;
    CanReceiveThread* mCan2ReceiveThread;

    ColorTest *m_color = NULL;

    //Projection *m_project = NULL;

protected slots:
    void myTimerUpdate(void);


};

#endif // MAINDLG_H
