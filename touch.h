#ifndef TOUCH_H
#define TOUCH_H

#include <QWidget>

namespace Ui {
class Touch;
}

class Touch : public QWidget
{
    Q_OBJECT

public:
    explicit Touch(QWidget *parent = 0);
    ~Touch();
    
private slots:
    void on_pushButton_clicked();

    void on_close_Btn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_clear_Btn_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_close_fing_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

private:
    Ui::Touch *ui;

    int clicked_1_num = 0;
    int clicked_2_num = 0;
    int clicked_3_num = 0;
    int clicked_4_num = 0;
    int clicked_5_num = 0;
    int clicked_6_num = 0;
    int clicked_7_num = 0;
    int clicked_8_num = 0;
    int clicked_9_num = 0;
    int clicked_10_num = 0;
    int clicked_11_num = 0;
    int clicked_12_num = 0;
    int clicked_13_num = 0;
    int clicked_14_num = 0;
    int clicked_15_num = 0;
    int clicked_16_num = 0;
    int clicked_17_num = 0;
    int clicked_18_num = 0;
    int clicked_19_num = 0;
    int clicked_20_num = 0;
    int clicked_21_num = 0;
    int clicked_22_num = 0;
    int clicked_23_num = 0;
    int clicked_24_num = 0;
    int clicked_25_num = 0;
};

#endif // TOUCH_H
