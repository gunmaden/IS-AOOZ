#ifndef ADMIN_USERS_H
#define ADMIN_USERS_H

#include <QWidget>

namespace Ui {
class Admin_users;
}

class Admin_users : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_users(QWidget *parent = 0);
    ~Admin_users();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Admin_users *ui;
};

#endif // ADMIN_USERS_H
