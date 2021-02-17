#include "zaprospostproduct.h"
#include "ui_zaprospostproduct.h"

ZaprosPostProduct::ZaprosPostProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZaprosPostProduct)
{
    ui->setupUi(this);
}

ZaprosPostProduct::~ZaprosPostProduct()
{
    delete ui;
}

QString ZaprosPostProduct::Metod()
{
    return(ui->TIP->text());
}
