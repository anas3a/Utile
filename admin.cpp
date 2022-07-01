#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    //Initial setup of admin page

    ui->setupUi(this);
    ui->fromcombo->addItem("From");
    ui->fromcombo->addItem("Dhaka");
    ui->fromcombo->addItem("Chittagong");
    ui->fromcombo->addItem("Sylhet");
    ui->fromcombo->addItem("Khulna");
    ui->fromcombo->addItem("Rajshahi");
    ui->fromcombo->addItem("Barishal");

    ui->tocombo->addItem("To");
    ui->tocombo->addItem("Chittagong");
    ui->tocombo->addItem("Dhaka");
    ui->tocombo->addItem("Sylhet");
    ui->tocombo->addItem("Khulna");
    ui->tocombo->addItem("Rajshahi");
    ui->tocombo->addItem("Barishal");

    ui->typecombo->addItem("AC");
    ui->typecombo->addItem("Non AC");

    ui->tabWidget->setStyleSheet("QTabBar::tab { min-height: 30px; min-width: 300px; }");

    showbustable();
    on_plistbutton_clicked();
}

admin::~admin()
{
    delete ui;
}

void admin::showbustable()
{
    //Showing bus list table in bus management tab

    dbclass db3;
    db3.connect();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM bus");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("BUS Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("From"));
    model->setHeaderData(2, Qt::Horizontal, tr("To"));
    model->setHeaderData(3, Qt::Horizontal, tr("Fare (BDT)"));
    model->setHeaderData(4, Qt::Horizontal, tr("AC/Non AC"));
    model->setHeaderData(5, Qt::Horizontal, tr("Departure Time"));
    model->setHeaderData(6, Qt::Horizontal, tr("BUS ID"));
    ui->bustable->setModel(model);
    ui->bustable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    db3.disconnect();
}

void admin::on_logoutbutton_clicked()
{
   // Loging out

   this->hide();
   login *loginwindow;
   loginwindow = new login(this);
   loginwindow->show();
}

void admin::on_ulistbutton_clicked()
{
    //Show user list table in history tab

    dbclass db1;
    db1.connect();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM user");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("User Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Contact Number"));
    model->setHeaderData(2, Qt::Horizontal, tr("Email ID"));
    model->setHeaderData(3, Qt::Horizontal, tr("Password"));
    model->setHeaderData(4, Qt::Horizontal, tr("Current Reward Point"));
    ui->datatable->setModel(model);
    ui->datatable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    db1.disconnect();
}

void admin::on_blistbutton_clicked()
{
    //Show bus list table in history tab

    dbclass db2;
    db2.connect();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM bus");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("BUS Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("From"));
    model->setHeaderData(2, Qt::Horizontal, tr("To"));
    model->setHeaderData(3, Qt::Horizontal, tr("Fare (BDT)"));
    model->setHeaderData(4, Qt::Horizontal, tr("AC / Non AC"));
    model->setHeaderData(5, Qt::Horizontal, tr("Departure Time"));
    model->setHeaderData(6, Qt::Horizontal, tr("BUS ID"));
    ui->datatable->setModel(model);
    ui->datatable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    db2.disconnect();
}

void admin::on_plistbutton_clicked()
{
    //Show purchase history table in history tab

    dbclass db3;
    db3.connect();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT * FROM history");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("User Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("BUS Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("From"));
    model->setHeaderData(3, Qt::Horizontal, tr("To"));
    model->setHeaderData(4, Qt::Horizontal, tr("Departure Time"));
    model->setHeaderData(5, Qt::Horizontal, tr("Purchasing Time"));
    model->setHeaderData(6, Qt::Horizontal, tr("Total Payment"));
    model->setHeaderData(7, Qt::Horizontal, tr("Departure Date"));
    model->setHeaderData(8, Qt::Horizontal, tr("Seat Taken"));
    ui->datatable->setModel(model);
    ui->datatable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    db3.disconnect();
}

void admin::on_addbusbutton_clicked()
{
    //Adding new bus to database

    dbclass db;
    db.connect();

    QString ac;
    QString bname = ui->busnameedit->text();
    QString ifrom = ui->fromcombo->currentText();
    QString ito = ui->tocombo->currentText();
    QString bfare = ui->busfareedit->text();
    QTime time = ui->timeset->time();
    QString stime = time.toString();
    ac = ui->typecombo->currentText();

    if (bname == "" || bfare == "" || ifrom == "From" || ito == "To")
        QMessageBox::warning(this, "BUS", "Unsuccessful! \nPlease provide valid info.");
    else
    {
        QSqlQuery *query = new QSqlQuery;
        query->prepare("INSERT INTO bus (name, bfrom, bto, fare, ac, time) VALUES ('"+bname+"', '"+ifrom+"', '"+ito+"', '"+bfare+"', '"+ac+"', '"+stime+"')");
        query->exec();
    }

    db.disconnect();
    showbustable();
}


void admin::on_lineEdit_textChanged(const QString &arg1)
{
    //live search in history tab

    dbclass db;
    db.connect();

    QString sline = arg1;
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT * FROM history WHERE uname LIKE '%"+sline+"%' OR bname LIKE '%"+sline+"%' OR bfrom LIKE '%"+sline+"%' OR bto LIKE '%"+sline+"%'");
    query->exec();
    model->setQuery(*query);
    model->setHeaderData(0, Qt::Horizontal, tr("User Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("BUS Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("From"));
    model->setHeaderData(3, Qt::Horizontal, tr("To"));
    model->setHeaderData(4, Qt::Horizontal, tr("Departure Time"));
    model->setHeaderData(5, Qt::Horizontal, tr("Purchasing Time"));
    model->setHeaderData(6, Qt::Horizontal, tr("Total Payment"));
    model->setHeaderData(7, Qt::Horizontal, tr("Departure Date"));
    model->setHeaderData(8, Qt::Horizontal, tr("Seat Taken"));
    ui->datatable->setModel(model);
    ui->datatable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    db.disconnect();
}


void admin::on_deletebusbutton_clicked()
{
    //Delete bus from databse

    dbclass db3;
    db3.connect();

    QSqlQuery query1;
    query1.prepare("DELETE FROM bus WHERE id = '"+deletebusid+"'");
    query1.exec();
    db3.disconnect();
    showbustable();
}

void admin::on_bustable_clicked(const QModelIndex &index)
{
    //selecting bus from table to delete

    int x = index.row();
    deletebusid = index.sibling(x, 6).data().toString();   
}
