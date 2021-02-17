#include "vievpostproductiondlg.h"
#include "ui_vievpostproductiondlg.h"

vievPostProductiondlg::vievPostProductiondlg(QWidget *parent,int currec) :
    QDialog(parent),
    ui(new Ui::vievPostProductiondlg)
{
    ui->setupUi(this);
    if(currec<0)        //Если в главной форме не была выбрана запись, то выбрать первую
        currec=0;
     record2 = qobject_cast<MainWindow*>(parent)->getmodel()->record(currec); //Получить запись из модели, необходимо явное преобразование типов
     ui->TIP->setText(record2.value("Тип").toString());           //Присвоить необходимые значения виджетам формы
     ui->MODEL->setText(record2.value("Модель").toString());
     recnmb2=currec;                                                      //Номер выбранной записи для навигации
     if (currec==0)                                                     //Если выбрана первая запись - отключить кнопку "Предыдущий"
            ui->Last->setEnabled(false);
     if(qobject_cast<MainWindow*>(parent)->getmodel()->rowCount()<=currec+1)     //Если последняя запись - то кнопку "Следующий"
            ui->Next->setEnabled(false);
}

vievPostProductiondlg::~vievPostProductiondlg()
{
    delete ui;
}

int vievPostProductiondlg::getRecNmb2()
{
   return recnmb2;
}

void vievPostProductiondlg::on_Last_clicked()   //Кнопка "Предыдущий"
{
   //Сохранение всех изменений в модель (не в саму БД!)
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,1),ui->TIP->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,2),ui->MODEL->text());
    recnmb2--;   //Уменьшаем номер записи, проверка что он не ноль уже была проведена
    record2 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb2);   //Переход к предыдущей записи и отображение её полей
    ui->TIP->setText(record2.value("Тип").toString());           //Присвоить необходимые значения виджетам формы
    ui->MODEL->setText(record2.value("Модель").toString());
    if(recnmb2==0)
        ui->Last->setEnabled(false);
    ui->Next->setEnabled(true);
 }

void vievPostProductiondlg::on_Next_clicked()   //Кнопка "Следующий"
{
   //Аналогично переходу на предыдущую запись
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,1),ui->TIP->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,2),ui->MODEL->text());
   recnmb2++;
   record2 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb2);
   ui->TIP->setText(record2.value("Тип").toString());           //Присвоить необходимые значения виджетам формы
   ui->MODEL->setText(record2.value("Модель").toString());
   if(recnmb2==qobject_cast<MainWindow*>(parent())->getmodel()->rowCount()-1)
       ui->Next->setEnabled(false);
   ui->Last->setEnabled(true);

}

void vievPostProductiondlg::on_Accept_clicked()   //Кнопка "Сохранить"
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
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,1),ui->TIP->text());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb2,2),ui->MODEL->text());
       //Применение изменений
   qobject_cast<MainWindow*>(parent())->getmodel()->submitAll();

       //Отключение кнопок сохранить и отменить
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
   ui->Last->setEnabled(false);
   ui->Next->setEnabled(false);
   }
}

bool vievPostProductiondlg::on_Decline_clicked() //Кнопка "Отмена"
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
       record2 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb2);
       ui->TIP->setText(record2.value("Тип").toString());           //Присвоить необходимые значения виджетам формы
       ui->MODEL->setText(record2.value("Модель").toString());
      //Изменений нет, кнопки больше не нужны
      return true;
   }
   return false;
}

void vievPostProductiondlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}
