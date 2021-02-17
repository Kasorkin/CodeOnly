#include "vievchetfrommaindlg.h"
#include "ui_vievchetfrommaindlg.h"
#include "Validator.h"

VievChetfrommainDlg::VievChetfrommainDlg(QWidget *parent,int currec) :
    QDialog(parent),
    ui(new Ui::VievChetfrommainDlg)
{
    ui->setupUi(this);
    StrValidator  *v=new StrValidator(ui->NumberCh);       //создание объекта, который займётся проверкой
    ui->NumberCh->setValidator(v);                        //подключение этого объекта к полю
    StrValidator *s=new StrValidator(ui->SumCh);       //создание объекта, который займётся проверкой
    ui->SumCh->setValidator(s);

    if(currec<0)        //Если в главной форме не была выбрана запись, то выбрать первую
        currec=0;
     record3 = qobject_cast<MainWindow*>(parent)->getmodel()->record(currec); //Получить запись из модели, необходимо явное преобразование типов
     ui->NumberCh->setText(record3.value("НомерСчета").toString());
     ui->SumCh->setText(record3.value("СуммаОплаты").toString());
     recnmb3=currec;                                                      //Номер выбранной записи для навигации
     if (currec==0)                                                     //Если выбрана первая запись - отключить кнопку "Предыдущий"
            ui->Last->setEnabled(false);
     if(qobject_cast<MainWindow*>(parent)->getmodel()->rowCount()<=currec+1)     //Если последняя запись - то кнопку "Следующий"
            ui->Next->setEnabled(false);
     if(record3.value("Оплата").toBool()==true)
     {
         ui->OplCh->setChecked(true);
     } else ui->OplCh->setChecked(false);
}


VievChetfrommainDlg::~VievChetfrommainDlg()
{
    delete ui;
}

int VievChetfrommainDlg::getRecNmb3()
{
   return recnmb3;
}

void VievChetfrommainDlg::on_Last_clicked()   //Кнопка "Предыдущий"
{
   //Сохранение всех изменений в модель (не в саму БД!)
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,1),ui->NumberCh->text().toInt());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,2),ui->SumCh->text().toInt());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,3),ui->OplCh->isChecked());
    recnmb3--;   //Уменьшаем номер записи, проверка что он не ноль уже была проведена
    record3 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb3);   //Переход к предыдущей записи и отображение её полей
    ui->NumberCh->setText(record3.value("НомерСчета").toString());
    ui->SumCh->setText(record3.value("СуммаОплаты").toString());
    if(record3.value("Оплата").toBool()==true)
    {
        ui->OplCh->setChecked(true);
    } else ui->OplCh->setChecked(false);
    if(recnmb3==0)
        ui->Last->setEnabled(false);
    ui->Next->setEnabled(true);
 }

void VievChetfrommainDlg::on_Next_clicked()   //Кнопка "Следующий"
{
   //Аналогично переходу на предыдущую запись
   qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,1),ui->NumberCh->text().toInt());
   qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,2),ui->SumCh->text().toInt());
   qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,3),ui->OplCh->isChecked());
   recnmb3++;
   record3 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb3);
   ui->NumberCh->setText(record3.value("НомерСчета").toString());
   ui->SumCh->setText(record3.value("СуммаОплаты").toString());
   if(record3.value("Оплата").toBool()==true)
   {
       ui->OplCh->setChecked(true);
   } else ui->OplCh->setChecked(false);
   if(recnmb3==qobject_cast<MainWindow*>(parent())->getmodel()->rowCount()-1)
       ui->Next->setEnabled(false);
   ui->Last->setEnabled(true);

}

void VievChetfrommainDlg::on_Accept_clicked()   //Кнопка "Сохранить"
{
   QMessageBox msgBox; //Стоит спросить уверен ли пользователь
   QString str=QString("Уверены что хотите сохранить изменения о видах?");//.arg(ui->anNameEdit->text());
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
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,1),ui->NumberCh->text().toInt());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,2),ui->SumCh->text().toInt());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb3,3),ui->OplCh->isChecked());
       //Применение изменений
       qobject_cast<MainWindow*>(parent())->getmodel()->submitAll();

       //Отключение кнопок сохранить и отменить
       ui->Accept->setEnabled(false);
       ui->Decline->setEnabled(false);
       ui->Last->setEnabled(false);
       ui->Next->setEnabled(false);
   }
}

bool VievChetfrommainDlg::on_Decline_clicked() //Кнопка "Отмена"
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
       qobject_cast<MainWindow*>(parent())->getmodel()->revertAll();
       //Сброс значений полей формы к изначальным
       record3 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb3);
       ui->NumberCh->setText(record3.value("НомерСчета").toString());
       ui->SumCh->setText(record3.value("СуммаОплаты").toString());
       if(record3.value("Оплата").toBool()==true)
       {
           ui->OplCh->setChecked(true);
       } else ui->OplCh->setChecked(false);
      //Изменений нет, кнопки больше не нужны
      return true;
   }
   return false;
}

void VievChetfrommainDlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}
