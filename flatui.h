/******************************************************************************
  文 件 名   : flatui.h
  版 本 号   : V1.1
  作    者   : wilbur王
  生成日期   : 2023.8.7
  功能描述   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/

#ifndef FLATUI_H
#define FLATUI_H

/**
 * 1:按钮样式设置
 * 2:文本框样式设置
 * 3:进度条样式
 * 4:滑块条样式
 * 5:单选框样式
 * 6:滚动条样式
 * 7:可自由设置对象的高度宽度大小等
 * 8:自带默认参数值
 */

#include <QObject>

class QPushButton;
class QLineEdit;
class QProgressBar;
class QSlider;
class QRadioButton;
class QCheckBox;
class QScrollBar;
class QTextEdit;
#ifdef quc
#    if (QT_VERSION < QT_VERSION_CHECK(5, 7, 0))
#        include <QtDesigner/QDesignerExportWidget>
#    else
#        include <QtUiPlugin/QDesignerExportWidget>
#    endif

class QDESIGNER_WIDGET_EXPORT FlatUI : public QObject
#else
class FlatUI : public QObject
#endif

{
    Q_OBJECT
public:
    static FlatUI* Instance();
    explicit FlatUI(QObject* parent = 0);

private:
    static QScopedPointer<FlatUI> self;

public:
    //设置按钮样式
    static QString setPushButtonQss0(QPushButton* btn,                              //按钮对象
                                     int radius = 5,                                //圆角半径
                                     int padding = 5,                               //间距
                                     const QString& normalColor = "#34495E",        //正常颜色
                                     const QString& normalTextColor = "#FFFFFF",    //文字颜色
                                     const QString& hoverColor = "#4E6D8C",         //悬停颜色
                                     const QString& hoverTextColor = "#F0F0F0",     //悬停文字颜色
                                     const QString& pressedColor = "#2d3E50",       //按下颜色
                                     const QString& pressedTextColor = "#B8C6D1");  //按下文字颜色
    //设置按钮样式
    static QString setPushButtonQss1(QPushButton* btn,                              //按钮对象
                                     int radius = 5,                                //圆角半径
                                     int padding = 5,                               //间距
                                     const QString& normalColor = "#3C9FD6",        //正常颜色
                                     const QString& normalTextColor = "#000000",    //文字颜色
                                     const QString& hoverColor = "#359DD5",         //悬停颜色
                                     const QString& hoverTextColor = "#F0F0F0",     //悬停文字颜色
                                     const QString& pressedColor = "#2C96CF",       //按下颜色
                                     const QString& pressedTextColor = "#B8C6D1");  //按下文字颜色

    //设置文本框样式
    static QString setLineEditQss(QLineEdit* txt,                          //文本框对象
                                  int radius = 5,                          //圆角半径
                                  int borderWidth = 2,                     //边框大小
                                  const QString& normalColor = "#DCE4EC",  //正常颜色
                                  const QString& focusColor = "#34495E");  //选中颜色

    //设置文本框样式
    static QString setTextEditQss(QTextEdit* txt,                          //文本框对象
                                  int radius = 3,                          //圆角半径
                                  int borderWidth = 1,                     //边框大小
                                  const QString& normalColor = "#DCE4EC",  //正常颜色
                                  const QString& focusColor = "#34495E");  //选中颜色

    //设置进度条样式
    static QString setProgressQss(QProgressBar* bar,
                                  int barHeight = 28,                       //进度条高度
                                  int barRadius = 25,                       //进度条半径
                                  int fontSize = 9,                        //文字字号
                                  const QString& normalColor = "#34495E",  //正常颜色
                                  const QString& chunkColor = "#E74C3C");  //进度颜色

    //设置滑块条样式
    static QString setSliderQss(QSlider* slider,                               //滑动条对象
                                int sliderHeight = 18,                          //滑动条高度
                                const QString& normalColor = "#E8EDF2",        //正常颜色
                                const QString& grooveColor = "#3C9FD6",        //滑块颜色
                                const QString& handleBorderColor = "#1ABC9C",  //指示器边框颜色
                                const QString& handleColor = "#FFFFFF");       //指示器颜色
    //设置复选框样式
    static QString setCheckBoxQss(QCheckBox* rbtn,
                                  int padding = 5,
                                  int indicatorRadius = 5,                 //指示器圆角角度
                                  const QString& normalColor = "#34495E",  //正常颜色
                                  const QString& checkColor = "#1ABC9C");  //选中颜色
    //设置单选框样式
    static QString setRadioButtonQss(QRadioButton* rbtn,                      //单选框对象
                                     int indicatorRadius = 8,                 //指示器圆角角度
                                     const QString& normalColor = "#34495E",  //正常颜色
                                     const QString& checkColor = "#1ABC9C");  //选中颜色

    //设置滚动条样式
    static QString setScrollBarQss(QWidget* scroll,                                 //滚动条对象
                                   int radius = 6,                                  //圆角角度
                                   int min = 120,                                   //指示器最小长度
                                   int max = 12,                                    //滚动条最大长度
                                   const QString& bgColor = "#606060",              //背景色
                                   const QString& handleNormalColor = "#34495E",    //指示器正常颜色
                                   const QString& handleHoverColor = "#1ABC9C",     //指示器悬停颜色
                                   const QString& handlePressedColor = "#E74C3C");  //指示器按下颜色
};

#endif  // FLATUI_H
