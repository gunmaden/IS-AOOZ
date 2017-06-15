#ifndef SVODANALYZ_H
#define SVODANALYZ_H

#include <QWidget>
extern QString FIO,IDD, testId;
namespace Ui {
class SvodAnalyz;
}

class SvodAnalyz : public QWidget
{
    Q_OBJECT

public:
    explicit SvodAnalyz(QWidget *parent = 0);
    ~SvodAnalyz();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SvodAnalyz *ui;
};

#endif // SVODANALYZ_H
