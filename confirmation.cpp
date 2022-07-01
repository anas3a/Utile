#include "confirmation.h"
#include "ui_confirmation.h"
#include "checkout.h"

confirmation::confirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmation)
{
    ui->setupUi(this);
}

confirmation::~confirmation()
{
    delete ui;
}

void confirmation::on_okbutton_clicked()
{
    //Going to selection page

    selection *selectwindow;
    selectwindow = new selection(this);
    this->hide();
    selectwindow->show();
}
