#include "admin_delus.h"
#include "ui_admin_delus.h"
#include "admin_users.h"

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>


QStringList userFIO, userId;
QSqlQueryModel typesModel;

Admin_delus::Admin_delus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_delus)
{
    ui->setupUi(this);
    userFIO.clear();
    userId.clear();
    ui->comboBox->clear();
    QString s = QString("SELECT * FROM \"view1\" ");

    typesModel.setQuery(s);
    for (int i=0;i<typesModel.rowCount();i++){
        userFIO<<typesModel.record(i).value("ФИО").toString();
        userId<<typesModel.record(i).value("id пользователя").toString();
    }
    ui->comboBox->addItems(userFIO);
}

Admin_delus::~Admin_delus()
{
    delete ui;
}

void Admin_delus::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Внимание!", "Вы действительно хотите удалить эту запись?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {

          QSqlQuery qqq;
          QString sql=(QString ("DELETE "
                                "FROM \"Users\" "
                                "WHERE id_user = '%1'").arg(userId.at(ui->comboBox->currentIndex())));
          qDebug()<<sql;
          qqq.exec(sql);
          ui->comboBox->clear();

          QMessageBox::information(this, "Успешно!", "Пользователь был успешно удален");

          Admin_users *w2 = new Admin_users();
          w2->setWindowTitle("Ведение справочника пользователей");
          w2->show();
          close();
      }

}

void Admin_delus::on_pushButton_2_clicked()
{
    Admin_users *w2 = new Admin_users();
    w2->setWindowTitle("Ведение справочника пользователей");
    w2->show();
    close();
}
