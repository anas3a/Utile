#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <login.h>
#include <QMessageBox>
#include <QDialog>
#include <QAbstractButton>
#include <QSqlQuery>
#include <login.h>
#include <dbclass.h>
#include <confirmation.h>

namespace Ui {
class checkout;
}

class checkout : public QDialog
{
    Q_OBJECT

public:
    explicit checkout(QWidget *parent = nullptr);
    ~checkout();

    void blockseat();

    void ticketPriceManage();

private slots:
   void sbuttonClicked(QAbstractButton* b);

   void on_logoutbutton_clicked();

   void on_rewardbutton_clicked();

   void on_paybutton_clicked();

private:

    Ui::checkout *ui;
    QList<QAbstractButton*> clickedseats;
    int netprice = 0;
    int seatcount = 0;
    int discount = 0;
    int total = 0;
    int rewardfinal;
    QString xseats = "";
    QString soldseats;
    bool flag = false;
};

#endif // CHECKOUT_H
