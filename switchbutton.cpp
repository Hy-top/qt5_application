/******************************************************************************
  文 件 名   : switchbutton.cpp
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#include "switchbutton.h"

/* 说明:自定义开关按钮控件实现文件
 * 功能:用来控制配置文件的开关设置
 */
SwitchButton::SwitchButton(QWidget *parent): QPushButton(parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    isCheck = false;
    styleOn = "background-image: url(:/image/btncheckon.png); border: 0px;";
    styleOff = "background-image: url(:/image/btncheckoff.png); border: 0px;";

    setFocusPolicy(Qt::NoFocus);
    setFixedSize(87, 28); //不允许变化大小
    setStyleSheet(styleOff);//设置当前样式
    connect(this, SIGNAL(clicked()), this, SLOT(ChangeOnOff()));
}

void SwitchButton::ChangeOnOff()
{
    if (isCheck) {

        setStyleSheet(styleOff);
        isCheck = false;
    }
    else {
        setStyleSheet(styleOn);
        isCheck = true;
    }
    emit checked(isCheck);
}

//设置当前选中状态
void SwitchButton::SetCheck(bool isCheck)
{
    if (this->isCheck != isCheck) {
        this->isCheck  = !isCheck;
        ChangeOnOff();
    }
}
