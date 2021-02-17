#include "allpostavshic.h"
#include "ui_allpostavshic.h"
#include "newpostavshikdlg.h"
#include "vievpostavshikdlg.h"
#include "ui_zaproszakazchik.h"
#include "zaproszakazchik.h"

AllPostavshic::AllPostavshic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllPostavshic)
{
    ui->setupUi(this);
    mdl=new QSqlRelationalTableModel();
    mdl->setTable("Поставщик");

    mdl->setRelation(5,QSqlRelation("ПоставляемаяПродукция","id","Тип"));
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit

    ui->tableView->setModel(mdl);
    ui->tableView->setColumnWidth(1, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(2, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(3, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("НазваниеКомпании"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("Директор"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("Бухгалтер"));
    mdl->setHeaderData(4, Qt::Horizontal, tr("Реквизиты"));
    mdl->setHeaderData(5, Qt::Horizontal, tr("ТипПродукции"));
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //Замена делегата на более удобный
                                                                                //Пригодится в случае редактирования данных напрямую через таблицу
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Но не в этом случае:)

    QSqlQuery query;
    QString  str = "SELECT * FROM ПоставляемаяПродукция";
    if (!query.exec(str))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
        qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug

    }
    if(query.size()<1)
    {
        ui->Add->setEnabled(false);
    }
    ui->Zapros1->addItem("По компании",QVariant(0));
    ui->Zapros1->addItem("По бухгалтеру",QVariant(1));
    ui->Zapros1->addItem("По директору",QVariant(2));
    ui->Zapros1->addItem("Не запрашивать",QVariant(3));
}


void AllPostavshic::on_Go1_clicked()
{
     if(ui->Zapros1->currentIndex()==0)
     {
         ZaprosZakazchik Dlg(this,4);
         Dlg.setModal(true);
         Dlg.exec();
         QString str1=Dlg.Metod2();
         QString str= QString("НазваниеКомпании = '%1'").arg(str1);
         qDebug() <<  str1;
         mdl ->setFilter(str);
    }
     if(ui->Zapros1->currentIndex()==1)
     {
         ZaprosZakazchik Dlg(this,5);
         Dlg.setModal(true);
         Dlg.exec();
         QString str1=Dlg.Metod2();
         QString str= QString("Бухгалтер = '%1'").arg(str1);
         mdl ->setFilter(str);
    }
     if(ui->Zapros1->currentIndex()==2)
     {
         ZaprosZakazchik Dlg(this,6);
         Dlg.setModal(true);
         Dlg.exec();
         QString str1=Dlg.Metod2();
         QString str= QString("Директор = '%1'").arg(str1);
         mdl ->setFilter(str);
    }
    if(ui->Zapros1->currentIndex()==3)
    {
         mdl->setFilter(0);
    }
}

AllPostavshic::~AllPostavshic()
{
    delete ui;
}

void AllPostavshic::on_Exit_clicked()
{
    accept();
}

void AllPostavshic::on_Add_clicked()
{
   NewPostavshikdlg Dlg;                       //Создание диалога для добавления записи
   Dlg.setModal(true);                     //Диалог должен быть модальным чтобы не исчез слишком быстро
   if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
   {

       NewPostavshikdlg::NewEq eq = Dlg.addel();   //Получение структуры со значениями полей записи
       if(eq.PostNameCompany!="")
       {
           ui->tableView->setColumnWidth(1, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(2, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(3, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
           mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
           mdl->setData(mdl->index(mdl->rowCount()-1, 1), eq.PostNameCompany);  //Установка значений полей из структуры
           mdl->setData(mdl->index(mdl->rowCount()-1, 2), eq.PostDirector);
           mdl->setData(mdl->index(mdl->rowCount()-1, 3), eq.PostBuhgalter);
           mdl->setData(mdl->index(mdl->rowCount()-1, 4), eq.PostRequisits);
           mdl->setData(mdl->index(mdl->rowCount()-1, 5), eq.PostTip);
           mdl->submitAll();                       //Подтверждение добавления поля
           qDebug() << mdl->lastError().text();
       }
   }
}

void AllPostavshic::on_Delete_clicked()  //Кнопка "Удалить"
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

void AllPostavshic::on_Redact_clicked()    //Кнопка "Редактировать"
{
int curRec=ui->tableView->currentIndex().row();
VievPostavshikDlg Dlg(mdl,this,curRec);                       //Создание диалога для просмотра записей
Dlg.setModal(true);
Dlg.exec();
}
