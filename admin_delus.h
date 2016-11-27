#ifndef ADMIN_DELUS_H
#define ADMIN_DELUS_H

#include <QWidget>

namespace Ui {
class Admin_delus;
}

class Admin_delus : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_delus(QWidget *parent = 0);
    ~Admin_delus();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Admin_delus *ui;
};

#endif // ADMIN_DELUS_H
