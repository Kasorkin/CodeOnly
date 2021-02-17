#include "alldogovorinpostavka.h"
#include "ui_alldogovorinpostavka.h"
#include "newdogovorinpostavka.h"
#include "vievdogovorinpostavkadlg.h"
#include "ui_zaproszakazchik.h"
#include "zaproszakazchik.h"

#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QPrinter>



AllDogovorInPostavka::AllDogovorInPostavka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllDogovorInPostavka)
{
    ui->setupUi(this);
    mdl=new QSqlRelationalTableModel();
    mdl->setTable("ДоговорНаПоставку");
    mdl->setRelation(4,QSqlRelation("Поставщик","id","НазваниеКомпании"));
    mdl->setRelation(5,QSqlRelation("Менеджер","id","ФИО"));
    mdl->setRelation(6,QSqlRelation("ПоставляемаяПродукция","id","Тип"));
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit
    ui->tableView->setModel(mdl);
    ui->tableView->setColumnWidth(1, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(4, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
    ui->tableView->setColumnWidth(6, ui->tableView->width()/5);
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("НомерДоговора"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("ДатаЗаключения"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("ДатаИстечения"));
    mdl->setHeaderData(4, Qt::Horizontal, tr("Поставщик"));
    mdl->setHeaderData(5, Qt::Horizontal, tr("Менеджер"));
    mdl->setHeaderData(6, Qt::Horizontal, tr("ТипПродукции"));
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //Замена делегата на более удобный
                                                                                //Пригодится в случае редактирования данных напрямую через таблицу
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //Но не в этом случае:)

    QSqlQuery query,query1,query2;
    QString  str = "SELECT * FROM Поставщик";       //Запрос на получение всех данных из таблицы
    QString  str1 = "SELECT * FROM Менеджер";
    QString  str2 = "SELECT * FROM ПоставляемаяПродукция";
    if (!query.exec(str)||!query1.exec(str1)||!query2.exec(str2))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
        qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        qDebug() <<  query1.lastError().text();
        qDebug() <<  query2.lastError().text();
    }
    if(query.size()<1||query1.size()<1||query2.size()<1)
    {
        ui->Add->setEnabled(false);
    }
    ui->Zapros1->addItem("По номеру",QVariant(0));
    ui->Zapros1->addItem("По поставщику",QVariant(1));
    ui->Zapros1->addItem("По менеджеру",QVariant(2));
    ui->Zapros1->addItem("Не запрашивать",QVariant(3));
    ui->Zapros1->addItem("Печать",QVariant(4));
}

void AllDogovorInPostavka::on_Go1_clicked()
{
    if(ui->Zapros1->currentIndex()==0)
    {
        if(ui->Zapros1->currentIndex()==0)
        {
            ZaprosZakazchik  Dlg(this,8);
            Dlg.setModal(true);
            Dlg.exec();
            int str1=Dlg.Metod3();
            QString str= QString("НомерДоговора = '%1'").arg(str1);
            mdl ->setFilter(str);

        }
    }
    if(ui->Zapros1->currentIndex()==1)
    {
        ZaprosZakazchik Dlg(this,7);
        Dlg.setModal(true);
        Dlg.exec();
        int str1=Dlg.Metod1();
        qDebug() <<  str1;
        QString str = QString("Поставщик = %1").arg(str1);
        qDebug() <<  str;
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        qDebug() << mdl->lastError().text();
    }
    if(ui->Zapros1->currentIndex()==2)
    {
        ZaprosZakazchik Dlg(this,2);
        Dlg.setModal(true);
        Dlg.exec();
        int str1=Dlg.Metod1();
        qDebug() <<  str1;
        QString str = QString("Менеджер = %1").arg(str1);
        qDebug() <<  str;
        mdl->setFilter(str); //Фильтр ограничивает модель выбранным действием
        qDebug() << mdl->lastError().text();
    }
    if(ui->Zapros1->currentIndex()==3)
    {
         mdl->setFilter(0);
    }
    if(ui->Zapros1->currentIndex()==4)
    {
            QTextDocument doc;  //Формируемый документ
            QTextCursor cur(&doc);  //Указатель на текущее место в документе
            QSqlRecord record;
            QFont newFont("Times New Romanow", 14, QFont::StyleNormal, false);
            int curRec=ui->tableView->currentIndex().row();
            record=mdl->record(curRec);
          if(record.value("id")==0)
          {
              QMessageBox msgBox;
              QString str=QString("Вы не выбрали запись");
              msgBox.setText(str);
              msgBox.setWindowTitle("Ошибка");
              msgBox.setIcon(QMessageBox::Warning);
              msgBox.exec();
          }
          else
          {
              //шапка
              QTextCharFormat boldFormat;
              boldFormat.setFont(newFont);
              cur.insertText("                                  Договор на поставку ",boldFormat);   //Добавление обычного текста
              cur.insertText(record.value("id").toString());
              cur.insertText("\n\nНомер договора - ");
              cur.insertText(record.value("НомерДоговора").toString());
              cur.insertText("\nОписание: Договор на поставку продукции типа - ");
              cur.insertText(record.value(6).toString());
              cur.insertText("\nДанный договор заключенные мейжду представителем компании ");
              cur.insertText(record.value(4).toString());
              cur.insertText(" и менеджером ");
              cur.insertText(record.value(5).toString());
              cur.insertText("\nДата заключения договора: ");
              cur.insertText(record.value("ДатаЗаключения").toString());
              cur.insertText("\nДата заключения договора: ");
              cur.insertText(record.value("ДатаИстечения").toString());
              cur.insertText("\n\n\nПодпись представителя компании        __________ ");
              cur.insertText("\n\nПодпись менеджера                               __________ ");
               QTextDocumentWriter writer("test2.odt"); //Имя документа odt
               writer.setFormat("odf2");
               writer.write(&doc); //Сохранение документа

               QPrinter printer(QPrinter::HighResolution);
               printer.setOutputFileName("test2.pdf");
               printer.setOutputFormat(QPrinter::PdfFormat);
               doc.print(&printer);
          }

    }
}

AllDogovorInPostavka::~AllDogovorInPostavka()
{
    delete ui;
}

void AllDogovorInPostavka::on_Exit_clicked()
{
    accept();
}

void AllDogovorInPostavka::on_Add_clicked()
{
   newdogovorinPostavka Dlg;                       //Создание диалога для добавления записи
   Dlg.setModal(true);                     //Диалог должен быть модальным чтобы не исчез слишком быстро
   if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
   {

       newdogovorinPostavka::NewEl el = Dlg.addel();   //Получение структуры со значениями полей записи
       if(el.DgNumber!=0)                       //Если пользователь ввёл имя, проверку можно было бы добавить в диалог, но проще тут
       {
           ui->tableView->setColumnWidth(1, ui->tableView->width()/6);
           ui->tableView->setColumnWidth(4, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(5, ui->tableView->width()/5);
           ui->tableView->setColumnWidth(6, ui->tableView->width()/5);
           mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
           mdl->setData(mdl->index(mdl->rowCount()-1, 1), el.DgNumber);  //Установка значений полей из структуры
           mdl->setData(mdl->index(mdl->rowCount()-1, 2), el.DgDateZacl);
           mdl->setData(mdl->index(mdl->rowCount()-1, 3), el.DgDateIst);
           mdl->setData(mdl->index(mdl->rowCount()-1, 4), el.DgPost);
           mdl->setData(mdl->index(mdl->rowCount()-1, 5), el.DgManager);    //Так как третий столбец - фото, надо записывать пол в четвёртый
           mdl->setData(mdl->index(mdl->rowCount()-1, 6), el.DgTip);
           mdl->submitAll();                       //Подтверждение добавления поля
           qDebug() << mdl->lastError().text();
       }
   }
}

void AllDogovorInPostavka::on_Delete_clicked()  //Кнопка "Удалить"
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

void AllDogovorInPostavka::on_Redact_clicked()    //Кнопка "Редактировать"
{
int curRec=ui->tableView->currentIndex().row();
vievDogovorInPostavkaDlg Dlg(mdl,this,curRec);                       //Создание диалога для просмотра записей
Dlg.setModal(true);
Dlg.exec();
}
