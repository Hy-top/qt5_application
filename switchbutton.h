/******************************************************************************
  文 件 名   : switchbutton.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>

/* 说明:自定义开关按钮控件头文件
 * 功能:用来控制配置文件的开关设置
 */
class SwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = 0);

    //获取当前选中状态
    bool GetCheck() const {
        return isCheck;
    }

    //设置当前选中状态
    void SetCheck(bool isCheck);

private:
    bool isCheck;
    QString styleOn;
    QString styleOff;

signals:
    void checked(bool);
private slots:
    void ChangeOnOff();

};

#endif //SWITCHBUTTON_H
