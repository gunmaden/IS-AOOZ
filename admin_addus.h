#ifndef ADMIN_ADDUS_H
#define ADMIN_ADDUS_H

#include <QWidget>

namespace Ui {
class Admin_addus;
}

class Admin_addus : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_addus(QWidget *parent = 0);
    ~Admin_addus();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Admin_addus *ui;
};

#endif // ADMIN_ADDUS_H
