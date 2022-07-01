#ifndef ADMIN_H
#define ADMIN_H

#include <QMessageBox>
#include <QDialog>
#include <login.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    void showbustable();

private slots:
    void on_logoutbutton_clicked();

    void on_ulistbutton_clicked();

    void on_blistbutton_clicked();

    void on_plistbutton_clicked();

    void on_addbusbutton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_deletebusbutton_clicked();

    void on_bustable_clicked(const QModelIndex &index);

private:
    Ui::admin *ui;
    QString deletebusid;
};

#endif // ADMIN_H
