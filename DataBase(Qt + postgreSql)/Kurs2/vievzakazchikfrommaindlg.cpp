#include "vievzakazchikfrommaindlg.h"
#include "ui_vievzakazchikfrommaindlg.h"
#include "Validator.h"

vievZakazchikfrommaindlg::vievZakazchikfrommaindlg(QWidget *parent,int currec) :
    QDialog(parent),
    ui(new Ui::vievZakazchikfrommaindlg)
{
    ui->setupUi(this);
    StrValidator  *v=new StrValidator(ui->PASSPORT);       //создание объекта, который займётся проверкой
    ui->PASSPORT->setValidator(v);                        //подключение этого объекта к полю
    StrValidator *s=new StrValidator(ui->NUMBER);       //создание объекта, который займётся проверкой
    ui->NUMBER->setValidator(s);

    if(currec<0)        //Если в главной форме не была выбрана запись, то выбрать первую
        currec=0;
     record1 = qobject_cast<MainWindow*>(parent)->getmodel()->record(currec); //Получить запись из модели, необходимо явное преобразование типов
     ui->FIOZ->setText(record1.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
     ui->dateEdit->setDate(record1.value("ДатаРождения").toDate());
     ui->PASSPORT->setText(record1.value("Паспорт").toString());
     ui->NUMBER->setText(record1.value("НомерТелефона").toString());
     recnmb1=currec;                                                      //Номер выбранной записи для навигации
     if (currec==0)                                                     //Если выбрана первая запись - отключить кнопку "Предыдущий"
            ui->Last->setEnabled(false);
     if(qobject_cast<MainWindow*>(parent)->getmodel()->rowCount()<=currec+1)     //Если последняя запись - то кнопку "Следующий"
            ui->Next->setEnabled(false);
     //ui->Save->setEnabled(false);         //Пока нет изменений, не надо ничего сохранять и отменять
     //ui->Decline->setEnabled(false);
}

vievZakazchikfrommaindlg::~vievZakazchikfrommaindlg()
{
    delete ui;
}

int vievZakazchikfrommaindlg::getRecNmb1()
{
   return recnmb1;
}

void vievZakazchikfrommaindlg::on_Last_clicked()   //Кнопка "Предыдущий"
{
   //Сохранение всех изменений в модель (не в саму БД!)
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,1),ui->FIOZ->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,3),ui->dateEdit->date());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,2),ui->PASSPORT->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,4),ui->NUMBER->text());
    recnmb1--;   //Уменьшаем номер записи, проверка что он не ноль уже была проведена
    record1 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb1);   //Переход к предыдущей записи и отображение её полей
    ui->FIOZ->setText(record1.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
    ui->dateEdit->setDate(record1.value("ДатаРождения").toDate());
    ui->PASSPORT->setText(record1.value("Паспорт").toString());
    ui->NUMBER->setText(record1.value("НомерТелефона").toString());
    if(recnmb1==0)
        ui->Last->setEnabled(false);
    ui->Next->setEnabled(true);
 }

void vievZakazchikfrommaindlg::on_Next_clicked()   //Кнопка "Следующий"
{
   //Аналогично переходу на предыдущую запись
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,1),ui->FIOZ->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,3),ui->dateEdit->date());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,2),ui->PASSPORT->text());
    qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,4),ui->NUMBER->text());
   recnmb1++;
   record1 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb1);
   ui->FIOZ->setText(record1.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
   ui->dateEdit->setDate(record1.value("ДатаРождения").toDate());
   ui->PASSPORT->setText(record1.value("Паспорт").toString());
   ui->NUMBER->setText(record1.value("НомерТелефона").toString());
   if(recnmb1==qobject_cast<MainWindow*>(parent())->getmodel()->rowCount()-1)
       ui->Next->setEnabled(false);
   ui->Last->setEnabled(true);

}


void vievZakazchikfrommaindlg::on_Accept_clicked()   //Кнопка "Сохранить"
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
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,1),ui->FIOZ->text());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,3),ui->dateEdit->date());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,2),ui->PASSPORT->text());
       qobject_cast<MainWindow*>(parent())->getmodel()->setData(qobject_cast<MainWindow*>(parent())->getmodel()->index(recnmb1,4),ui->NUMBER->text());
       //Применение изменений
   qobject_cast<MainWindow*>(parent())->getmodel()->submitAll();

       //Отключение кнопок сохранить и отменить
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
   ui->Last->setEnabled(false);
   ui->Next->setEnabled(false);
   }
}

bool vievZakazchikfrommaindlg::on_Decline_clicked() //Кнопка "Отмена"
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
       record1 = qobject_cast<MainWindow*>(parent())->getmodel()->record(recnmb1);
       ui->FIOZ->setText(record1.value("ФИО").toString());           //Присвоить необходимые значения виджетам формы
       ui->dateEdit->setDate(record1.value("ДатаРождения").toDate());
       ui->PASSPORT->setText(record1.value("Паспорт").toString());
       ui->NUMBER->setText(record1.value("НомерТелефона").toString());
      //Изменений нет, кнопки больше не нужны
      return true;
   }
   return false;
}

void vievZakazchikfrommaindlg::on_Close_clicked()  //Кнопка "Выход"
{
       close();
}
