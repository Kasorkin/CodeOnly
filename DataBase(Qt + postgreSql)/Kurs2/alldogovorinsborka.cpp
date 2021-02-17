#include "alldogovorinsborka.h"
#include "ui_alldogovorinsborka.h"
#include "newdogovorinsborkadlg.h"
#include "vievdogovorinsporkadlg.h"
#include "ui_zaproszakazchik.h"
#include "zaproszakazchik.h"

#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QPrinter>


AllDogovorInSborka::AllDogovorInSborka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllDogovorInSborka)
{
    ui->setupUi(this);

    mdl=new QSqlRelationalTableModel();
    mdl->setTable("ДоговорНаСборку");
    mdl->setRelation(6,QSqlRelation("Менеджер","id","ФИО"));
    mdl->setRelation(5,QSqlRelation("Заказчик","id","ФИО"));
    mdl->setRelation(7,QSqlRelation("Счет","id","НомерСчета"));
    mdl->select();
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView->setModel(mdl);
    ui->tableView->setColumnWidth(1, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(6, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(7, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(3, ui->tableView->width()/16);
    ui->tableView->setColumnWidth(4, ui->tableView->width()/16);
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));
    mdl->setHeaderData(1, Qt::Horizontal, tr("НомерДоговора"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("ДатаЗаключения"));
    mdl->setHeaderData(5, Qt::Horizontal, tr("Заказчик"));
    mdl->setHeaderData(6, Qt::Horizontal, tr("Менеджер"));
    mdl->setHeaderData(7, Qt::Horizontal, tr("НомерСчета"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("Оплачено"));
    mdl->setHeaderData(4, Qt::Horizontal, tr("Доставлено"));
    ui->tableView->horizontalHeader()->moveSection( 5 , 3 );
    ui->tableView->horizontalHeader()->moveSection( 6 , 4 );
    ui->tableView->horizontalHeader()->moveSection( 7 , 5 );
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //Замена делегата на более удобный
                                                                                //Пригодится в случае редактирования данных напрямую через таблицу
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Но не в этом случае:)

    QSqlQuery query,query1,query2;
    QString  str = "SELECT * FROM Менеджер";       //Запрос на получение всех данных из таблицы
    QString  str1 = "SELECT * FROM Заказчик";
    QString  str2 = "SELECT * FROM Счет";
    if (!query.exec(str)||!query1.exec(str1)||!query2.exec(str2))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
        qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        qDebug() <<  query1.lastError().text();
        qDebug() <<  query2.lastError().text();
    }
    if(query.size()<1||query1.size()<1||query2.size()<1)                          //Если количество строк в запросе меньше 1
    {
        ui->Add->setEnabled(false);          //Значит надо запретить добавлять новых животных!
    }
    ui->Zapros1->addItem("Оплаченные",QVariant(0));
    ui->Zapros1->addItem("Неоплаченные",QVariant(1));
    ui->Zapros1->addItem("Доставленые",QVariant(2));
    ui->Zapros1->addItem("Недоставленные",QVariant(3));
    ui->Zapros1->addItem("По заказчику",QVariant(4));
    ui->Zapros1->addItem("По менеджеру",QVariant(5));
    ui->Zapros1->addItem("Не запрашивать",QVariant(6));
}

void AllDogovorInSborka::on_Go1_clicked()
{
    if(ui->Zapros1->currentIndex()==0)
    {
        QString str = QString("Оплачено = true");
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
    }
    if(ui->Zapros1->currentIndex()==1)
    {
        QString str = QString("Оплачено = false");
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
    }
    if(ui->Zapros1->currentIndex()==2)
    {
        QString str = QString("Доставлено = true");
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
    }
    if(ui->Zapros1->currentIndex()==3)
    {
        QString str = QString("Доставлено = false");
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        //qDebug() << ;
    }
    if(ui->Zapros1->currentIndex()==4)
    {
        ZaprosZakazchik Dlg(this,1);
        Dlg.setModal(true);
        Dlg.exec();
        int str1=Dlg.Metod1();
        qDebug() <<  str1;
        QString str = QString("ДоговорНаСборку.Заказчик = %1").arg(str1);
        qDebug() <<  str;
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        qDebug() << mdl->lastError().text();
    }
    if(ui->Zapros1->currentIndex()==5)
    {
        ZaprosZakazchik Dlg(this,2);
        Dlg.setModal(true);
        Dlg.exec();
        int str1=Dlg.Metod1();
        qDebug() <<  str1;
        QString str = QString("ДоговорНаСборку.Менеджер = %1").arg(str1);
        qDebug() <<  str;
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        qDebug() << mdl->lastError().text();
    }
    if(ui->Zapros1->currentIndex()==6)
    {
         mdl->setFilter(0);
    }
}

AllDogovorInSborka::~AllDogovorInSborka()
{
    delete ui;
    delete mdl;
}

void AllDogovorInSborka::on_Exit_clicked()
{
    accept();
}

void AllDogovorInSborka::on_Add_clicked()
{
   newDogovorInSborkadlg Dlg;                       //Создание диалога для добавления записи
   Dlg.setModal(true);                     //Диалог должен быть модальным чтобы не исчез слишком быстро
   if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
   {

       newDogovorInSborkadlg::NewEl el = Dlg.addel();   //Получение структуры со значениями полей записи
       if(el.DgNumber!=0)
       {
           ui->tableView->setColumnWidth(1, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(6, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(7, ui->tableView->width()/6);
           ui->tableView->setColumnWidth(3, ui->tableView->width()/16);
           ui->tableView->setColumnWidth(4, ui->tableView->width()/16);
           ui->tableView->horizontalHeader()->moveSection( 5 , 3 );
           ui->tableView->horizontalHeader()->moveSection( 6 , 4 );
           ui->tableView->horizontalHeader()->moveSection( 7 , 5 );
           mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
           mdl->setData(mdl->index(mdl->rowCount()-1, 1), el.DgNumber);  //Установка значений полей из структуры
           mdl->setData(mdl->index(mdl->rowCount()-1, 2), el.DgDate);
           mdl->setData(mdl->index(mdl->rowCount()-1, 5), el.DgZakazchic);
           mdl->setData(mdl->index(mdl->rowCount()-1, 6), el.DgManager);
           mdl->setData(mdl->index(mdl->rowCount()-1, 7), el.DgChet);
           mdl->setData(mdl->index(mdl->rowCount()-1, 3), el.DgOpl);
           mdl->setData(mdl->index(mdl->rowCount()-1, 4), el.DgDost);
           mdl->submitAll();                       //Подтверждение добавления поля
           qDebug() << mdl->lastError().text();
       }
   }
}

void AllDogovorInSborka::on_Delete_clicked()  //Кнопка "Удалить"
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

void AllDogovorInSborka::on_Redact_clicked()    //Кнопка "Редактировать"
{
int curRec=ui->tableView->currentIndex().row();
VievDogovorInSporkaDlg Dlg(mdl,this,curRec);                       //Создание диалога для просмотра записей
Dlg.setModal(true);
Dlg.exec();
}

