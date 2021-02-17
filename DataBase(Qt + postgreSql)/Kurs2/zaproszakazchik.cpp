#include "zaproszakazchik.h"
#include "ui_zaproszakazchik.h"

ZaprosZakazchik::ZaprosZakazchik(QWidget *parent,int i) :
    QDialog(parent),
    ui(new Ui::ZaprosZakazchik)
{
        ui->setupUi(this);
        QSqlQuery query1;
        if(i==1)
        {
            ui->info->show();
            ui->comboBox->show();
            ui->info2->hide();
            ui->TEXT->hide();
            QString  str1 = "SELECT id, ФИО FROM Заказчик ORDER BY ФИО";
            ui->INFO->setText("Выберите ФИО заказчика");
            ui->info->setText("ФИО");
            if (!query1.exec(str1))
            {
                qDebug() <<  query1.lastError().text();
            }
            while(query1.next())
            {
                ui->comboBox->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
            }
        }
        if(i==2)
        {
            ui->info->show();
            ui->comboBox->show();
            ui->info2->hide();
            ui->TEXT->hide();
            QString  str1 = "SELECT id, ФИО FROM Менеджер ORDER BY ФИО";
            ui->INFO->setText("Выберите ФИО менеджера");
            ui->info->setText("ФИО");
            if (!query1.exec(str1))
            {
                qDebug() <<  query1.lastError().text();
            }
            while(query1.next())
            {
                ui->comboBox->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
            }
        }
        if(i==3)
        {
            //здесь должен быть тип
        }
        if(i==4)
        {
            ui->INFO->setText("Введите название компании");
            ui->info2->setText("Название");
            ui->info->hide();
            ui->comboBox->hide();
            ui->info2->show();
            ui->TEXT->show();
        }
        if(i==5)
        {
            ui->INFO->setText("Введите Бухгалтера");
            ui->info2->setText("ФИО");
            ui->info->hide();
            ui->comboBox->hide();
            ui->info2->show();
            ui->TEXT->show();
        }
        if(i==6)
        {
            ui->INFO->setText("Введите Директора");
            ui->info2->setText("ФИО");
            ui->info->hide();
            ui->comboBox->hide();
            ui->info2->show();
            ui->TEXT->show();
        }
        if(i==7)
        {
            ui->info->show();
            ui->comboBox->show();
            ui->info2->hide();
            ui->TEXT->hide();
            QString  str1 = "SELECT id, НазваниеКомпании FROM Поставщик ORDER BY НазваниеКомпании";
            ui->INFO->setText("Выберите название компании");
            ui->info->setText("ФИО");
            if (!query1.exec(str1))
            {
                qDebug() <<  query1.lastError().text();
            }
            while(query1.next())
            {
                ui->comboBox->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
            }
        }
        if(i==8)
        {
            ui->INFO->setText("Введите номер договора");
            ui->info2->setText("Номер");
            ui->info->hide();
            ui->comboBox->hide();
            ui->info2->show();
            ui->TEXT->show();
        }
        if(i==9)
        {

        }

}

ZaprosZakazchik::~ZaprosZakazchik()
{
    delete ui;
}

int ZaprosZakazchik::Metod1()
{
    return(ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());
}

QString ZaprosZakazchik::Metod2()
{
    return (ui->TEXT->text());
}

int ZaprosZakazchik::Metod3()
{
    return (ui->TEXT->text().toInt());
}
