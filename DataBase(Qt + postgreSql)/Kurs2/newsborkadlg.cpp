#include "newsborkadlg.h"
#include "ui_newsborkadlg.h"

NewSborkaDlg::NewSborkaDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSborkaDlg)
{
    ui->setupUi(this);
    QSqlQuery query,query1,query2,query3,query4,query5,query6,query7,query8,query9,query10,query11,query12,query13;
    QString  str = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Корпус\'";       //Запрос на получение всех данных из таблицы species
    QString  str2 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'МатеринскаяПлата\'";
    QString  str3 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Процессор\'";
    QString  str4 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'ЖесткийДиск\'";
    QString  str5 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'ОперативнаяПамять\'";
    QString  str6 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'СистемаОхлаждения\'";
    QString  str7 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'БлокПитания\'";
    QString  str8 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Видеокарта\'";
    QString  str9 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Дисковод\'";
    QString  str10 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Картридер\'";
    QString  str11 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Аудиокарта\'";
    QString  str12 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'TV-карта\'";
    QString  str13 = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'СпутниковаяКарта\'";
    QString  str1 = "SELECT id,НомерДоговора FROM ДоговорНаСборку ORDER BY НомерДоговора";    //"SELECT id, Тип FROM ПоставляемаяПродукция ORDER BY Тип"

          if(!query.exec(str)||!query1.exec(str1)||!query2.exec(str2)||!query3.exec(str3)||!query4.exec(str4)||!query5.exec(str5)||!query6.exec(str6)||!query7.exec(str7)||!query8.exec(str8)||!query9.exec(str9)||!query10.exec(str10)||!query11.exec(str11)||!query12.exec(str12)||!query13.exec(str13)){
           qDebug() <<  query.lastError().text();
           qDebug() <<  query1.lastError().text();
           qDebug() <<  query2.lastError().text();
           qDebug() <<  query3.lastError().text();
           qDebug() <<  query4.lastError().text();
           qDebug() <<  query5.lastError().text();
           qDebug() <<  query6.lastError().text();
           qDebug() <<  query7.lastError().text();
           qDebug() <<  query8.lastError().text();
           qDebug() <<  query9.lastError().text();
           qDebug() <<  query10.lastError().text();
           qDebug() <<  query11.lastError().text();
           qDebug() <<  query12.lastError().text();
           qDebug() <<  query13.lastError().text();
    }
            while(query.next())         //Проход по строкам запроса
           {
               ui->SKorpus->addItem(query.value(2).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
           }
           while(query2.next())
           {
               ui->SMaterinka->addItem(query2.value(2).toString(),query2.value(0));
           }
           while(query3.next())
           {
               ui->SProcess->addItem(query3.value(2).toString(),query3.value(0));
           }
           while(query4.next())
           {
               ui->SDisk->addItem(query4.value(2).toString(),query4.value(0));
           }
           while(query5.next())
           {
               ui->SOperativa->addItem(query5.value(2).toString(),query5.value(0));
           }
           while(query6.next())
           {
               ui->SSystemOhl->addItem(query6.value(2).toString(),query6.value(0));
           }
           while(query7.next())
           {
               ui->SPitanie->addItem(query7.value(2).toString(),query7.value(0));
           }
           while(query8.next())
           {
               ui->SVideo->addItem(query8.value(2).toString(),query8.value(0));
           }
           while(query9.next())
           {
               ui->SDiskovod->addItem(query9.value(2).toString(),query9.value(0));
           }
           while(query10.next())
           {
               ui->SKartrider->addItem(query10.value(2).toString(),query10.value(0));
           }
           while(query11.next())
           {
               ui->SAudio->addItem(query11.value(2).toString(),query11.value(0));
           }
           while(query12.next())
           {
               ui->STV->addItem(query12.value(2).toString(),query12.value(0));
           }
           while(query13.next())
           {
               ui->SKarta->addItem(query13.value(2).toString(),query13.value(0));
           }
           while(query1.next())         //Проход по строкам запроса
           {
               ui->SNumber->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
           }
}
NewSborkaDlg::~NewSborkaDlg()
{
    delete ui;
}

NewSborkaDlg::NewEl NewSborkaDlg::addel()
{
   NewEl el;
   el.Korpus=ui->SKorpus->itemData(ui->SKorpus->currentIndex()).toInt();
   el.Plata=ui->SMaterinka->itemData(ui->SMaterinka->currentIndex()).toInt();
   el.Processor=ui->SProcess->itemData(ui->SProcess->currentIndex()).toInt();
   el.Disk=ui->SDisk->itemData(ui->SDisk->currentIndex()).toInt();
   el.Operativa=ui->SOperativa->itemData(ui->SOperativa->currentIndex()).toInt();
   el.SystemCold=ui->SSystemOhl->itemData(ui->SSystemOhl->currentIndex()).toInt();
   el.Energy=ui->SPitanie->itemData(ui->SPitanie->currentIndex()).toInt();
   el.Number=ui->SNumber->itemData(ui->SNumber->currentIndex()).toInt();
   //
   el.Video=ui->SVideo->itemData(ui->SVideo->currentIndex()).toInt();
   el.Diskovod=ui->SDiskovod->itemData(ui->SDiskovod->currentIndex()).toInt();
   el.Kartrider=ui->SKartrider->itemData(ui->SKartrider->currentIndex()).toInt();
   el.Audio=ui->SAudio->itemData(ui->SAudio->currentIndex()).toInt();
   el.TV=ui->STV->itemData(ui->STV->currentIndex()).toInt();
   el.SPKarta=ui->SKarta->itemData(ui->SKarta->currentIndex()).toInt();
   return el;
}
