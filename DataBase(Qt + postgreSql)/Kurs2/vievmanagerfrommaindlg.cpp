#include "vievmanagerfrommaindlg.h"
#include "ui_vievmanagerfrommaindlg.h"
#include <QObject>

vievManagerfrommaindlg::vievManagerfrommaindlg(QWidget *parent,int currec) :
    QDialog(parent),
    ui(new Ui::vievManagerfrommaindlg)
{
    ui->setupUi(this);
    if(currec<0)        //Если в главной форме не была выбрана запись, то выбрать первую
        currec=0;
     record = qobject_cast<MainWindow*>(parent)->getmodel()->record(currec); //Получить запись из модели, необходимо явное преобразование типов
     ui->FIO->setText(record.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
     recnmb=currec;                                                      //Номер выбранной записи для навигации
     if (currec==0)                                                     //Если выбрана первая запись - отключить кнопку "Предыдущий"
            ui->Last->setEnabled(false);
     if(qobject_cast<MainWindow*>(parent)->getmodel()->rowCount()<=currec+1)     //Если последняя запись - то кнопку "Следующий"
            ui->Next->setEnabled(false);
}

vievManagerfrommaindlg::~vievManagerfrommaindlg()
{
    delete ui;
}

int vievManagerfrommaindlg::getRecNmb()
{
   return recnmb;
}

void vievManagerfrommaindlg::on_Last_clicked()   //Кнопка "Предыдущий"
{
   //Сохранение всех изменений в модель (не в саму БД!)
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb,1),ui->FIO->text());
    recnmb--;   //Уменьшаем номер записи, проверка что он не ноль уже была проведена
    record = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb);   //Переход к предыдущей записи и отображение её полей
    ui->FIO->setText(record.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
    if(recnmb==0)
        ui->Last->setEnabled(false);
    ui->Next->setEnabled(true);
 }

void vievManagerfrommaindlg::on_Next_clicked()   //Кнопка "Следующий"
{
   //Аналогично переходу на предыдущую запись
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb,1),ui->FIO->text());
   recnmb++;
   record = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb);
    ui->FIO->setText(record.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
   if(recnmb==qobject_cast<MainWindow*>(parent())->getmodel()->rowCount()-1)
       ui->Next->setEnabled(false);
   ui->Last->setEnabled(true);

}

void vievManagerfrommaindlg::on_Accept_clicked()   //Кнопка "Сохранить"
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
 qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb,1),ui->FIO->text());
       //Применение изменений
   qobject_cast<MainWindow*>(parent())->getmodel()->submitAll();

       //Отключение кнопок сохранить и отменить
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
   ui->Last->setEnabled(false);
   ui->Next->setEnabled(false);
   }
}

bool vievManagerfrommaindlg::on_Decline_clicked() //Кнопка "Отмена"
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
       record = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb);
      ui->FIO->setText(record.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
      //Изменений нет, кнопки больше не нужны
      return true;
   }
   return false;
}

void vievManagerfrommaindlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}
