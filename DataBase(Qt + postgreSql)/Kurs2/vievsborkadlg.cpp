#include "vievsborkadlg.h"
#include "ui_vievsborkadlg.h"
#include <QObject>

VievSborkaDlg::VievSborkaDlg(QSqlRelationalTableModel *model,QWidget *parent, int currec) :
    QDialog(parent),
    ui(new Ui::VievSborkaDlg)
{
    mdl=model;
    ui->setupUi(this);
    if(currec<0)
           currec=0;
       recnmb=currec;
       QSqlRecord record = mdl->record(currec);
       QSqlQuery query,query1,query2,query3,query4,query5,query6,query7,query8,query9,query10,query11,query12,query13;
      // QString  str = "SELECT id,Модель FROM ПоставляемаяПродукция ORDER BY Модель";
       QString  str = "SELECT * FROM ПоставляемаяПродукция WHERE Тип = \'Корпус\'";
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
       QString  str1 = "SELECT id,НомерДоговора FROM ДоговорНаСборку ORDER BY НомерДоговора";

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
          ui->SKorpus->setCurrentIndex(ui->SKorpus->findText(record.value(1).toString()));
          while(query2.next())
          {
              ui->SMaterinka->addItem(query2.value(2).toString(),query2.value(0));
          }
          ui->SMaterinka->setCurrentIndex(ui->SMaterinka->findText(record.value(2).toString()));
          while(query3.next())
          {
              ui->SProcess->addItem(query3.value(2).toString(),query3.value(0));
          }
          ui->SProcess->setCurrentIndex(ui->SProcess->findText(record.value(3).toString()));
          while(query4.next())
          {
              ui->SDisk->addItem(query4.value(2).toString(),query4.value(0));
          }
          ui->SDisk->setCurrentIndex(ui->SDisk->findText(record.value(4).toString()));
          while(query5.next())
          {
              ui->SOperativa->addItem(query5.value(2).toString(),query5.value(0));
          }
          ui->SOperativa->setCurrentIndex(ui->SOperativa->findText(record.value(5).toString()));
          while(query6.next())
          {
              ui->SSystemOhl->addItem(query6.value(2).toString(),query6.value(0));
          }
          ui->SSystemOhl->setCurrentIndex(ui->SSystemOhl->findText(record.value(6).toString()));
          while(query7.next())
          {
              ui->SPitanie->addItem(query7.value(2).toString(),query7.value(0));
          }
          ui->SPitanie->setCurrentIndex(ui->SPitanie->findText(record.value(7).toString()));
          //ДОПОЛНИТЕЛЬНО
          while(query8.next())
          {
              ui->SVideo->addItem(query8.value(2).toString(),query8.value(0));
          }
          ui->SVideo->setCurrentIndex(ui->SVideo->findText(record.value(9).toString()));
          while(query9.next())
          {
              ui->SDiskovod->addItem(query9.value(2).toString(),query9.value(0));
          }
          ui->SDiskovod->setCurrentIndex(ui->SDiskovod->findText(record.value(10).toString()));
          while(query10.next())
          {
              ui->SKartrider->addItem(query10.value(2).toString(),query10.value(0));
          }
          ui->SKartrider->setCurrentIndex(ui->SKartrider->findText(record.value(11).toString()));
          while(query11.next())
          {
              ui->SAudio->addItem(query11.value(2).toString(),query11.value(0));
          }
          ui->SAudio->setCurrentIndex(ui->SAudio->findText(record.value(12).toString()));
          while(query12.next())
          {
              ui->STV->addItem(query12.value(2).toString(),query12.value(0));
          }
          ui->STV->setCurrentIndex(ui->STV->findText(record.value(13).toString()));
          while(query13.next())
          {
              ui->SKarta->addItem(query13.value(2).toString(),query13.value(0));
          }
          ui->SKarta->setCurrentIndex(ui->SKarta->findText(record.value(14).toString()));
          while(query1.next())         //Проход по строкам запроса
          {
              ui->SNumber->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->SNumber->setCurrentIndex(ui->SNumber->findText(record.value(8).toString()));
}

void VievSborkaDlg::on_Accept_clicked()    //При нажатии на кнопку "Сохранить"
{
   QMessageBox msgBox; //Стоит спросить уверен ли пользователь
   QString str=QString("Уверены что хотите сохранить изменения о договоре на сборку?");//.arg(ui->anNameEdit->text());
   msgBox.setText(str);
   msgBox.setWindowTitle("Подтверждение");
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setInformativeText("Данная операция необратима!");
   QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole); //Для корректного перевода, кнопки добавлены вручную
   QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
   msgBox.setDefaultButton(pButtonNo);
   msgBox.exec();
   if(msgBox.clickedButton()==pButtonYes)  //Если пользователь решился сохранить
   {
       //Сохранение последних изменений в модель
       mdl->setData(mdl->index(recnmb,1),ui->SKorpus->itemData(ui->SKorpus->currentIndex()));
       mdl->setData(mdl->index(recnmb,2),ui->SMaterinka->itemData(ui->SMaterinka->currentIndex()));
       mdl->setData(mdl->index(recnmb,3),ui->SProcess->itemData(ui->SProcess->currentIndex()));
       mdl->setData(mdl->index(recnmb,4),ui->SDisk->itemData(ui->SDisk->currentIndex()));
       mdl->setData(mdl->index(recnmb,5),ui->SOperativa->itemData(ui->SOperativa->currentIndex()));
       mdl->setData(mdl->index(recnmb,6),ui->SSystemOhl->itemData(ui->SSystemOhl->currentIndex()));
       mdl->setData(mdl->index(recnmb,7),ui->SPitanie->itemData(ui->SPitanie->currentIndex()));
       mdl->setData(mdl->index(recnmb,8),ui->SNumber->itemData(ui->SNumber->currentIndex()));
       //Дополнительно
       mdl->setData(mdl->index(recnmb,9),ui->SVideo->itemData(ui->SVideo->currentIndex()));
       mdl->setData(mdl->index(recnmb,10),ui->SDiskovod->itemData(ui->SDiskovod->currentIndex()));
       mdl->setData(mdl->index(recnmb,11),ui->SKartrider->itemData(ui->SKartrider->currentIndex()));
       mdl->setData(mdl->index(recnmb,12),ui->SAudio->itemData(ui->SAudio->currentIndex()));
       mdl->setData(mdl->index(recnmb,13),ui->STV->itemData(ui->STV->currentIndex()));
       mdl->setData(mdl->index(recnmb,14),ui->SKarta->itemData(ui->SKarta->currentIndex()));
       //Применение изменений
   mdl->submitAll();
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
   }
}

bool VievSborkaDlg::on_Decline_clicked()  //При нажатии на кнопку "Отменить"
{
   //Уверен ли пользователь что хочет всё отменить?
   QMessageBox msgBox;
   QString str=QString("Уверены что хотите отменить внесённые изменения?");//.arg(ui->anNameEdit->text());
   msgBox.setText(str);
   msgBox.setWindowTitle("Подтверждение");
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setInformativeText("Данная операция необратима!");
   QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole); //Для корректного перевода, кнопки добавлены вручную
   QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
   msgBox.setDefaultButton(pButtonYes);        //А вот тут будем считать что пользователь уверен
   msgBox.exec();

   if(msgBox.clickedButton()==pButtonYes)  //Если пользователь решился сохранить
   {
      //Отмена изменений
      mdl->revertAll();
      //Сброс значений полей формы к изначальным
      QSqlRecord record = mdl->record(recnmb);
      return true;
   }
   return false;
}


void VievSborkaDlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}

VievSborkaDlg::~VievSborkaDlg()
{
    delete ui;
}
