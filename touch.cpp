/******************************************************************************
  文 件 名   : touch.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2024.3.23
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "touch.h"
#include "ui_touch.h"
#include "flatui.h"

Touch::Touch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Touch)
{
    ui->setupUi(this);
    FlatUI::setPushButtonQss0(ui->clear_Btn);
    FlatUI::setPushButtonQss0(ui->close_Btn);
    FlatUI::setPushButtonQss0(ui->close_fing);
    ui->close_fing->hide();
}

Touch::~Touch()
{
    delete ui;
}

void Touch::on_close_Btn_clicked()
{
    this->close();
}

void Touch::on_clear_Btn_clicked()
{
    clicked_1_num = 0;
    clicked_2_num = 0;
    clicked_3_num = 0;
    clicked_4_num = 0;
    clicked_5_num = 0;
    clicked_6_num = 0;
    clicked_7_num = 0;
    clicked_8_num = 0;
    clicked_9_num = 0;
    clicked_10_num = 0;
    clicked_11_num = 0;
    clicked_12_num = 0;
    clicked_13_num = 0;
    clicked_14_num = 0;
    clicked_15_num = 0;
    clicked_16_num = 0;
    clicked_17_num = 0;
    clicked_18_num = 0;
    clicked_19_num = 0;
    clicked_20_num = 0;
    clicked_21_num = 0;
    clicked_22_num = 0;
    clicked_23_num = 0;
    clicked_24_num = 0;
    clicked_25_num = 0;
    ui->label->setText("A:0");
    ui->label_2->setText("B:0");
    ui->label_3->setText("C:0");
    ui->label_4->setText("D:0");
    ui->label_5->setText("E:0");
    ui->label_6->setText("F:0");
    ui->label_7->setText("G:0");
    ui->label_8->setText("H:0");
    ui->label_9->setText("I:0");
    ui->label_10->setText("J:0");
    ui->label_11->setText("K:0");
    ui->label_12->setText("L:0");
    ui->label_13->setText("M:0");
    ui->label_14->setText("N:0");
    ui->label_15->setText("O:0");
    ui->label_16->setText("P:0");
    ui->label_17->setText("Q:0");
    ui->label_18->setText("R:0");
    ui->label_19->setText("S:0");
    ui->label_20->setText("T:0");
    ui->label_21->setText("U:0");
    ui->label_22->setText("V:0");
    ui->label_23->setText("W:0");
    ui->label_24->setText("X:0");
    ui->label_25->setText("Y:0");
}

void Touch::on_pushButton_clicked()
{
    clicked_1_num++;
    ui->label->setText("A:" + QString::number(clicked_1_num));
}

void Touch::on_pushButton_2_clicked()
{
    clicked_2_num++;
    ui->label_2->setText("B:" + QString::number(clicked_2_num));
}

void Touch::on_pushButton_3_clicked()
{
    clicked_3_num++;
    ui->label_3->setText("C:" + QString::number(clicked_3_num));
}

void Touch::on_pushButton_4_clicked()
{
    clicked_4_num++;
    ui->label_4->setText("D:" + QString::number(clicked_4_num));
}

void Touch::on_pushButton_5_clicked()
{
    clicked_5_num++;
    ui->label_5->setText("E:" + QString::number(clicked_5_num));
}

void Touch::on_pushButton_6_clicked()
{
    clicked_6_num++;
    ui->label_6->setText("F:" + QString::number(clicked_6_num));
}

void Touch::on_pushButton_7_clicked()
{
    clicked_7_num++;
    ui->label_7->setText("G:" + QString::number(clicked_7_num));
}

void Touch::on_pushButton_8_clicked()
{
    clicked_8_num++;
    ui->label_8->setText("H:" + QString::number(clicked_8_num));
}

void Touch::on_pushButton_9_clicked()
{
    clicked_9_num++;
    ui->label_9->setText("I:" + QString::number(clicked_9_num));
}

void Touch::on_pushButton_10_clicked()
{
    clicked_10_num++;
    ui->label_10->setText("J:" + QString::number(clicked_10_num));
}

void Touch::on_pushButton_11_clicked()
{
    clicked_11_num++;
    ui->label_11->setText("K:" + QString::number(clicked_11_num));
}

void Touch::on_pushButton_12_clicked()
{
    clicked_12_num++;
    ui->label_12->setText("L:" + QString::number(clicked_12_num));
}

void Touch::on_pushButton_13_clicked()
{
    clicked_13_num++;
    ui->label_13->setText("M:" + QString::number(clicked_13_num));
}

void Touch::on_pushButton_14_clicked()
{
    clicked_14_num++;
    ui->label_14->setText("N:" + QString::number(clicked_14_num));
}

void Touch::on_pushButton_15_clicked()
{
    clicked_15_num++;
    ui->label_15->setText("O:" + QString::number(clicked_15_num));
}

void Touch::on_pushButton_16_clicked()
{
    clicked_16_num++;
    ui->label_16->setText("P:" + QString::number(clicked_16_num));
}

void Touch::on_pushButton_17_clicked()
{
    clicked_17_num++;
    ui->label_17->setText("Q:" + QString::number(clicked_17_num));
}

void Touch::on_pushButton_18_clicked()
{
    clicked_18_num++;
    ui->label_18->setText("R:" + QString::number(clicked_18_num));
}

void Touch::on_pushButton_19_clicked()
{
    clicked_19_num++;
    ui->label_19->setText("S:" + QString::number(clicked_19_num));
}

void Touch::on_pushButton_20_clicked()
{
    clicked_20_num++;
    ui->label_20->setText("T:" + QString::number(clicked_20_num));
}

void Touch::on_pushButton_21_clicked()
{
    clicked_21_num++;
    ui->label_21->setText("U:" + QString::number(clicked_21_num));
}

void Touch::on_pushButton_22_clicked()
{
    clicked_22_num++;
    ui->label_22->setText("V:" + QString::number(clicked_22_num));
}

void Touch::on_pushButton_23_clicked()
{
    clicked_23_num++;
    ui->label_23->setText("W:" + QString::number(clicked_23_num));
}

void Touch::on_pushButton_24_clicked()
{
    clicked_24_num++;
    ui->label_24->setText("X:" + QString::number(clicked_24_num));
}

void Touch::on_pushButton_25_clicked()
{
    clicked_25_num++;
    ui->label_25->setText("Y:" + QString::number(clicked_25_num));
}


void Touch::on_close_fing_clicked()
{
    ui->close_fing->hide();

    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_5->show();
    ui->pushButton_6->show();
}
