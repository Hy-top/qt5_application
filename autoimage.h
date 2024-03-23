#ifndef AUTOIMAGE_H
#define AUTOIMAGE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class AutoImage;
}

class AutoImage : public QWidget
{
    Q_OBJECT

public:
    explicit AutoImage(QWidget *parent = 0);
    ~AutoImage();

protected slots:
    void myTimerUpdate(void);

private slots:
    void on_close_Btn_clicked();

private:
    Ui::AutoImage *ui;
    QTimer *timer;
    int img_num;
};

#endif // AUTOIMAGE_H
