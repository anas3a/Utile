#include "checkout.h"
#include "ui_checkout.h"
#include "confirmation.h"

checkout::checkout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkout)
{
    //Initial setup of admin page

    ui->setupUi(this);
    ui->namelabel->setText(sname);
    ui->pointshow->setNum(sreward);
    ui->bnamelabel->setText(busname);
    ui->bfromlabel->setText(from);
    ui->btolabel->setText(to);
    ui->baseprice->setNum(fare);
    ui->dtimelabel->setText(dtime);
    ui->seat->connect(ui->seat, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(sbuttonClicked(QAbstractButton*)));
    blockseat();
}

checkout::~checkout()
{
    delete ui;
}

void checkout::blockseat()
{
    //Blocking previously sold tickets on that date

    dbclass db;
    db.connect();
    QSqlQuery query;
    query.prepare("SELECT * FROM seat WHERE id = '"+id+"' AND date = '"+ddate+"'");
    query.exec();
    query.next();
    soldseats = query.value(2).toString();
    QList<QAbstractButton *> list = ui->seat->buttons();
    for (int i = 0; i < list.size(); i++)
    {
        QAbstractButton *busseat = list[i];
        QString cseat = list[i]->text();
        if (soldseats.contains(cseat))
        {
            busseat->setDisabled(true);
            busseat->setStyleSheet("background: red");
        }
    }
    db.disconnect();
}

void checkout::sbuttonClicked(QAbstractButton* busseat)
{
    //If customer click any seat button

    if (clickedseats.size() == 5)
    {
        QMessageBox::warning(this, "Seat", "A user can purchase maximum 5 seats.");
        return;
    }

    busseat->setStyleSheet("background: LawnGreen");
    QFont font = busseat->font();
    font.setBold(true);
    busseat->setFont(font);
    QString flagseat = busseat->text();
    if (xseats.contains(flagseat))
        flag = true;

    QString seats;
    clickedseats.append(busseat);
    for (int i = 0; i < clickedseats.size(); i++)
    {
        seats += clickedseats.at(i)->text();
        seats += " ";
    }
    if (flag == false)
    {
        seatcount++;
        checkout::ticketPriceManage();
        ui->bseatlabel->setText(seats);
        xseats = seats;
    }
    flag = false;
}

void checkout::ticketPriceManage()
{
    //Calculating and showing ticket price and information

    netprice = fare * seatcount;
    total = netprice - discount;

    ui->baseprice->setNum(fare);
    ui->ticketctlabel->setNum(seatcount);
    ui->netlabel->setNum(netprice);
    ui->discountlabel->setNum(discount);
    ui->totallabel->setNum(total);
}

void checkout::on_logoutbutton_clicked()
{
    //log out

    this->hide();
    login *loginwindow;
    loginwindow = new login(this);
    loginwindow->show();
}

void checkout::on_rewardbutton_clicked()
{
    //reward point management

        if (sreward  <= netprice)
        {
            discount = sreward;
            rewardfinal = 0;
            ui->pointshow->setNum(0);
        }
        else
        {
            discount = netprice;
            rewardfinal = sreward - discount;
            ui->pointshow->setNum(rewardfinal);
        }
        checkout::ticketPriceManage();
}

void checkout::on_paybutton_clicked()
{
    //Things when pay button is clicked

    if (netprice == 0)
    {
        QMessageBox::warning(this, "info", "You didn't select any seat!");
        return;
    }

    //Adding info to history table of database.
    dbclass db1;
    db1.connect();

    QSqlQuery query;
    QString stotal = QString::number(total);
    if (total > 0)
        rewardfinal += total / 10;
    sreward = rewardfinal;
    QString qreward = QString::number(rewardfinal);
    QDateTime datetime = QDateTime::currentDateTime();
    QString ptime = datetime.toString();

    query.prepare("INSERT INTO history (uname, bname, bfrom, bto, dtime, ptime, charge, date, seats) VALUES ('"+sname+"', '"+busname+"', '"+from+"', '"+to+"', '"+dtime+"','"+ptime+"', '"+stotal+"', '"+ddate+"', '"+xseats+"')");
    query.exec();
    db1.disconnect();


    //Updating sold bus seat list to database.
    dbclass db3;
    db3.connect();
    QSqlQuery query2, query3, query4;
    query3.exec("SELECT * FROM seat WHERE id = '"+id+"' AND date = '"+ddate+"'");
    if (query3.next())
    {
        QString seatd = xseats + soldseats;
        query4.exec("UPDATE seat SET seats = '"+seatd+"' WHERE id = '"+id+"' AND date = '"+ddate+"'");
    }
    else
    {
        query2.prepare("INSERT INTO seat (id, date, seats) VALUES ('"+id+"' , '"+ddate+"', '"+xseats+"')");
        query2.exec();
    }
    db3.disconnect();


    //Updating reward point of a user.
    dbclass db2;
    db2.connect();
    QSqlQuery query1;
    query1.prepare("UPDATE user SET reward = '"+qreward+"' WHERE email ='"+semail+"'");
    query1.exec();
    db2.disconnect();

    //Going to confirmation page
    confirmation *confirmationwindow;
    confirmationwindow = new confirmation(this);
    confirmationwindow->show();
    this->hide();
}




