#include "newpostproductiondlg.h"
#include "ui_newpostproductiondlg.h"

newPostProductiondlg::newPostProductiondlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newPostProductiondlg)
{
    ui->setupUi(this);
}

newPostProductiondlg::~newPostProductiondlg()
{
    delete ui;
}
newPostProductiondlg::NewEs newPostProductiondlg::addel()
{
   NewEs es;                           //Объявление структуры
   es.Tip=ui->Tip->text();
   es.Model=ui->Model->text();   //Имя берётся из Line Edit
   return es;          //Структура с данными возвращается в основную форму
}
