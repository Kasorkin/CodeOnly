#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newmanager.h"
#include "ui_newmanager.h"
#include "vievmanagerfrommaindlg.h"
#include "ui_vievmanagerfrommaindlg.h"
#include "newzakazchikdlg.h"
#include "ui_newzakazchikdlg.h"
#include "vievzakazchikfrommaindlg.h"
#include "ui_vievzakazchikfrommaindlg.h"
#include "newpostproductiondlg.h"
#include "ui_newpostproductiondlg.h"
#include "vievpostproductiondlg.h"
#include "ui_vievpostproductiondlg.h"
#include "alldogovorinsborka.h"
#include "ui_newchetdlg.h"
#include "newchetdlg.h"
#include "alldogovorinpostavka.h"
#include "vievchetfrommaindlg.h"
#include "ui_vievchetfrommaindlg.h"
#include "allpostavshic.h"
#include "allsborka.h"
#include "zaprospostproduct.h"
#include "ui_zaprospostproduct.h"

#include "QComboBox"

short int P=1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!CreateConnection())     //Установка соединения с БД, оно будет существовать до завершения программы
    {
        exit(-1);       //Аварийное завершение работы при ошибке
    }
    mdl = new QSqlTableModel(this,QSqlDatabase::database()); //Подключение модели к БД
    Start();

}

void MainWindow::Start()
{
    ui->Info->setText("Менеджер");
    ui->Go->setEnabled(false);
    ui->Zapros->setEnabled(false);
    mdl->setTable("Менеджер");                                //Выбор таблицы
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    ui->tableView->setColumnWidth(1, ui->tableView->width()/3);
    mdl->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView->setModel(mdl);                           //Подключение таблицы к представлению
    ui->tableView->hideColumn(0);                           //Сокрытие столбца id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
}
void MainWindow::on_Sborka_clicked()
{
   AllSborka Dlg(this);
   Dlg.setModal(true);
   Dlg.exec();
}

void MainWindow::on_DogovorInSborka_clicked()
{
   AllDogovorInSborka Dlg(this);
   Dlg.setModal(true);
   Dlg.exec();
}

void MainWindow::on_DogovorInPostavka_clicked()
{
   AllDogovorInPostavka Dlg(this);
   Dlg.setModal(true);
   Dlg.exec();
}

void MainWindow::on_Postavshik_clicked()
{
   AllPostavshic Dlg(this);
   Dlg.setModal(true);
   Dlg.exec();
}

void MainWindow::on_Manager_clicked()
{
    ui->Zapros->clear();
    P=1;
    ui->Go->setEnabled(false);
    ui->Zapros->setEnabled(false);
    ui->Info->setText("Менеджер");
    mdl->setTable("Менеджер");                                //Выбор таблицы
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    ui->tableView->setColumnWidth(1, ui->tableView->width()/3);
    mdl->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView->setModel(mdl);                           //Подключение таблицы к представлению
    ui->tableView->hideColumn(0);                           //Сокрытие столбца id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
}

void MainWindow::on_Test_clicked()
{
    ui->Zapros->clear();
    P=2;
    ui->Go->setEnabled(false);
    ui->Zapros->setEnabled(false);
    ui->Info->setText("Заказчик");
    mdl->setTable("Заказчик");                                //Выбор таблицы
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("Паспорт"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("ДатаРождения"));
    mdl->setHeaderData(4, Qt::Horizontal, tr("НомерТелефона"));
    ui->tableView->setColumnWidth(1, ui->tableView->width()/3);
    ui->tableView->setColumnWidth(4, ui->tableView->width()/4);
    mdl->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView->setModel(mdl);                           //Подключение таблицы к представлению
    ui->tableView->hideColumn(0);                           //Сокрытие столбца id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
}

void MainWindow::on_PostProduct_clicked()
{
    ui->Zapros->clear();
    P=3;
    ui->Go->setEnabled(true);
    ui->Zapros->setEnabled(true);
    ui->Zapros->addItem("По типу",QVariant(0));
    ui->Zapros->addItem("Не запрашивать",QVariant(1));
    ui->Info->setText("Поставляемая Продукция");
    mdl->setTable("ПоставляемаяПродукция");                                //Выбор таблицы
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("Тип"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("Модель"));
    ui->tableView->setColumnWidth(1, ui->tableView->width()/4);
    ui->tableView->setColumnWidth(2, ui->tableView->width()/3);
    mdl->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView->setModel(mdl);                           //Подключение таблицы к представлению
    ui->tableView->hideColumn(0);                           //Сокрытие столбца id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
}

void MainWindow::on_Chet_clicked()
{
    ui->Zapros->clear();
    P=4;
    ui->Go->setEnabled(true);
    ui->Zapros->setEnabled(true);
    ui->Zapros->addItem("Оплаченные",QVariant(0));
    ui->Zapros->addItem("Неоплаченные",QVariant(1));
    ui->Zapros->addItem("Не запрашивать",QVariant(2));
    ui->Info->setText("Счет");
    mdl->setTable("Счет");                                //Выбор таблицы
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("НомерСчета"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("СуммаОплаты"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("Оплата"));
    ui->tableView->setColumnWidth(1, ui->tableView->width()/4);
    ui->tableView->setColumnWidth(2, ui->tableView->width()/4);
    mdl->sort(0,Qt::AscendingOrder);                        //Сортировать записи по возрастанию ключа, так как порядок записей часто меняется
    ui->tableView->setModel(mdl);                           //Подключение таблицы к представлению
    ui->tableView->hideColumn(0);                           //Сокрытие столбца id
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Отключение возможности редактировать данные напрямую
}

void MainWindow::on_Go_clicked()
{
    if(P==3)
    {
        if(ui->Zapros->currentIndex()==0)
        {
            ZaprosPostProduct Dlg(this);
            Dlg.setModal(true);
            Dlg.exec();
            QString str1=Dlg.Metod();
            QString str= QString("Тип = '%1'").arg(str1);
            mdl ->setFilter(str);

        }
        if(ui->Zapros->currentIndex()==1)
        {
             mdl->setFilter(0);
        }
    }
    if(P==4)
    {
        if(ui->Zapros->currentIndex()==0)
        {
            QString str = QString("Оплата = true");
            mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        }
        if(ui->Zapros->currentIndex()==1)
        {
            QString str = QString("Оплата = false");
            mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        }
        if(ui->Zapros->currentIndex()==2)
        {
             mdl->setFilter(0);
        }
    }
}
void MainWindow::on_Add_clicked()
{
    if(P==1)
    {
        newManager Dlg;
        Dlg.setModal(true);
        if(Dlg.exec()==QDialog::Accepted)
        {
            newManager::NewEl el = Dlg.addel();
            if(el.FIO!="")
            {
                ui->tableView->setColumnWidth(0, ui->tableView->width()/10);
                mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
                mdl->setData(mdl->index(mdl->rowCount()-1, 1), el.FIO);  //Установка значений полей из структуры
                mdl->submitAll();                       //Подтверждение добавления поля
            }
        }
    }
    if(P==2)
    {
        newZakazchikdlg Dlg;
        Dlg.setModal(true);
        if(Dlg.exec()==QDialog::Accepted)
        {
            newZakazchikdlg::NewEk ek = Dlg.addel();
            if(ek.Fio!="")
            {
                mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
                mdl->setData(mdl->index(mdl->rowCount()-1, 1), ek.Fio);  //Установка значений полей из структуры
                mdl->setData(mdl->index(mdl->rowCount()-1, 2), ek.Passport);
                mdl->setData(mdl->index(mdl->rowCount()-1, 3), ek.dateRosh);
                mdl->setData(mdl->index(mdl->rowCount()-1, 4), ek.NumberT);
                mdl->submitAll();                       //Подтверждение добавления поля
            }
        }
    }
    if(P==3)
    {
        newPostProductiondlg Dlg;
        Dlg.setModal(true);
        if(Dlg.exec()==QDialog::Accepted)
        {
            newPostProductiondlg::NewEs es = Dlg.addel();
            if(es.Tip!="")
            {
                mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
                mdl->setData(mdl->index(mdl->rowCount()-1, 1), es.Tip);  //Установка значений полей из структуры
                mdl->setData(mdl->index(mdl->rowCount()-1, 2), es.Model);
                mdl->submitAll();                       //Подтверждение добавления поля
            }
        }
    }
    if(P==4)
    {
        newChetdlg Dlg;
        Dlg.setModal(true);
        if(Dlg.exec()==QDialog::Accepted)
        {
            newChetdlg::NewEl4 el4 = Dlg.addel();
            if(el4.NumberChet!=0)
            {
                mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
                mdl->setData(mdl->index(mdl->rowCount()-1, 1), el4.NumberChet);  //Установка значений полей из структуры
                mdl->setData(mdl->index(mdl->rowCount()-1, 2), el4.Summ);
                mdl->setData(mdl->index(mdl->rowCount()-1, 3), el4.OplChet);
                mdl->submitAll();                       //Подтверждение добавления поля
            }
        }
    }
}


void MainWindow::on_Redact_clicked()
{
    int curRec=ui->tableView->currentIndex().row();       //Получение номера записи, выбранной в представлени
    if(P==1)
    {
        vievManagerfrommaindlg Dlg(this,curRec);
        Dlg.setModal(true);
        Dlg.exec();
        curRec=Dlg.getRecNmb();
        ui->tableView->selectRow(curRec);
    }
    if(P==2)
    {
        vievZakazchikfrommaindlg Dlg(this,curRec);
        Dlg.setModal(true);
        Dlg.exec();
        curRec=Dlg.getRecNmb1();
        ui->tableView->selectRow(curRec);
    }
    if(P==3)
    {
        vievPostProductiondlg Dlg(this,curRec);
        Dlg.setModal(true);
        Dlg.exec();
        curRec=Dlg.getRecNmb2();
        ui->tableView->selectRow(curRec);
    }
    if(P==4)
    {
        VievChetfrommainDlg Dlg(this,curRec);
        Dlg.setModal(true);
        Dlg.exec();
        curRec=Dlg.getRecNmb3();
        ui->tableView->selectRow(curRec);
    }

}

void MainWindow::on_Delete_clicked()  //Кнопка "Удалить"
{
   int curRec=ui->tableView->currentIndex().row(); //Получение номера текущей записи
   QMessageBox msgBox; //Стоит спросить пользователя уверен ли он
   QString str=QString("Уверены что хотите удалить запись \"%1\"?").arg(mdl->index(curRec,1).data().toString());
   msgBox.setText(str);
   msgBox.setWindowTitle("Подтверждение");
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setInformativeText("Данные будут удалены безвозвратно!");
   QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
   QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
   msgBox.setDefaultButton(pButtonNo);
   msgBox.exec();
   if(msgBox.clickedButton()==pButtonYes)
   {
       mdl->removeRows(curRec,1);  //Если уверен - удалить одну запись начиная с текущей выбранной
       mdl->submitAll();
   }
}

void MainWindow::on_Exit_clicked()
{
    this->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*POSTGRESQL*/
bool MainWindow::CreateConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");   //Драйвер PostreSQL
    db.setHostName("localhost");                            //Адрес сервера
    db.setDatabaseName("Kurs");                              //Имя БД
    db.setUserName("lavgustin");                             //Имя пользователя
    db.setPassword("");                       //Пароль пользователя
    db.setPort(5432);                                       //Номер порта
    if (!db.open()) {                                       //Создание связи
        QMessageBox msgBox;
        QString str=QString("Ошибка при открытии базы данных:");
        msgBox.setText(str);
        msgBox.setWindowTitle("Ошибка");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setInformativeText(db.lastError().text());
        msgBox.exec();                                      //При ошибке отображение сообщения
        return false;
    }
    return true;
}

QSqlTableModel* MainWindow::getmodel()
{
   return mdl;
}

