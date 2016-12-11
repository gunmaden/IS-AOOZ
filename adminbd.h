#ifndef ADMINBD_H
#define ADMINBD_H

#include <QWidget>

namespace Ui {
class AdminBD;
}

class AdminBD : public QWidget
{
    Q_OBJECT

public:
    explicit AdminBD(QWidget *parent = 0);
    ~AdminBD();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminBD *ui;
};

#endif // ADMINBD_H
