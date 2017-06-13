#ifndef ZAVCATH_H
#define ZAVCATH_H

#include <QWidget>

namespace Ui {
class ZavCath;
}

class ZavCath : public QWidget
{
    Q_OBJECT

public:
    explicit ZavCath(QWidget *parent = 0);
    ~ZavCath();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ZavCath *ui;
};

#endif // ZAVCATH_H
