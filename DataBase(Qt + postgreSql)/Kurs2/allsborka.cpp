#include "allsborka.h"
#include "ui_allsborka.h"
#include "newsborkadlg.h"
#include "vievsborkadlg.h"

AllSborka::AllSborka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSborka)
{
    ui->setupUi(this);
    ui->Osn->setEnabled(false);
    mdl=new QSqlRelationalTableModel();
    mdl->setTable("Сборка");
    //Для удобства комментирования, каждый параметр объявлен как QString
    //На практике их можно писать сразу в виде текста, не используя переменные
    mdl->setRelation(1,QSqlRelation("ПоставляемаяПродукция","id","Модель"));   //Первый параметр - столбец, который связывается. Второй - чем заменить
    mdl->setRelation(2,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(3,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(4,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(5,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(6,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(7,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(8,QSqlRelation("ДоговорНаСборку","id","НомерДоговора"));
    mdl->setRelation(9,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(10,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(11,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(12,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(13,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->setRelation(14,QSqlRelation("ПоставляемаяПродукция","id","Модель"));
    mdl->select();                                          //Загрузка данных из таблицы в модель
    mdl->setEditStrategy(QSqlTableModel::OnManualSubmit);   //Обновление БД только при вызове метода Submit

    ui->tableView->setModel(mdl);
    ui->tableView->setColumnWidth(1, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(2, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(3, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(4, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(5, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(6, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(7, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(8, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(9, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(10, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(11, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(12, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(13, ui->tableView->width()/6);
    ui->tableView->setColumnWidth(14, ui->tableView->width()/6);
    mdl->setHeaderData(0, Qt::Horizontal, tr("id"));        //Подписи к столбцам
    mdl->setHeaderData(1, Qt::Horizontal, tr("Корпус"));
    mdl->setHeaderData(2, Qt::Horizontal, tr("МатеринскаяПлата"));
    mdl->setHeaderData(3, Qt::Horizontal, tr("Процессор"));
    mdl->setHeaderData(4, Qt::Horizontal, tr("ЖесткийДиск"));
    mdl->setHeaderData(5, Qt::Horizontal, tr("ОперативнаяПамять"));
    mdl->setHeaderData(6, Qt::Horizontal, tr("СистемаОхлаждения"));
    mdl->setHeaderData(7, Qt::Horizontal, tr("БлокПитания"));
    mdl->setHeaderData(8, Qt::Horizontal, tr("НомерДоговора"));
    mdl->setHeaderData(9, Qt::Horizontal, tr("Видеокарта"));
    mdl->setHeaderData(10, Qt::Horizontal, tr("Дисковод"));
    mdl->setHeaderData(11, Qt::Horizontal, tr("Картридер"));
    mdl->setHeaderData(12, Qt::Horizontal, tr("Аудиокарта"));
    mdl->setHeaderData(13, Qt::Horizontal, tr("TV-карта"));
    mdl->setHeaderData(14, Qt::Horizontal, tr("СпутниковаяКарта"));
    ui->tableView->horizontalHeader()->moveSection( 8 , 1 );
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(9);
    ui->tableView->hideColumn(10);
    ui->tableView->hideColumn(11);
    ui->tableView->hideColumn(12);
    ui->tableView->hideColumn(13);
    ui->tableView->hideColumn(14);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //Замена делегата на более удобный
                                                                                //Пригодится в случае редактирования данных напрямую через таблицу
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query,query1;
    QString  str = "SELECT * FROM ПоставляемаяПродукция";
    QString  str1 = "SELECT * FROM ДоговорНаСборку";
    if (!query.exec(str)||!query1.exec(str1))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
        qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
        qDebug() <<  query1.lastError().text();
    }
    if(query.size()<1||query1.size()<1)
    {
        ui->Add->setEnabled(false);
    }
}
void AllSborka::on_Osn_clicked()
{
   ui->Osn->setEnabled(false);
   ui->Dop->setEnabled(true);
   ui->tableView->hideColumn(9);
   ui->tableView->hideColumn(10);
   ui->tableView->hideColumn(11);
   ui->tableView->hideColumn(12);
   ui->tableView->hideColumn(13);
   ui->tableView->hideColumn(14);
   ui->tableView->showColumn(1);
   ui->tableView->showColumn(2);
   ui->tableView->showColumn(3);
   ui->tableView->showColumn(4);
   ui->tableView->showColumn(5);
   ui->tableView->showColumn(6);
   ui->tableView->showColumn(7);
}

void AllSborka::on_Dop_clicked()
{
    ui->Osn->setEnabled(true);
    ui->Dop->setEnabled(false);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(6);
    ui->tableView->hideColumn(7);
    ui->tableView->showColumn(9);
    ui->tableView->showColumn(10);
    ui->tableView->showColumn(11);
    ui->tableView->showColumn(12);
    ui->tableView->showColumn(13);
    ui->tableView->showColumn(14);
}

AllSborka::~AllSborka()
{
    delete ui;
}

void AllSborka::on_Exit_clicked()
{
    accept();
}

void AllSborka::on_Add_clicked()
{
   NewSborkaDlg Dlg;                       //Создание диалога для добавления записи
   Dlg.setModal(true);                     //Диалог должен быть модальным чтобы не исчез слишком быстро
   if(Dlg.exec() == QDialog::Accepted)     //Если пользователь выбрал кнопку Ок
   {
       NewSborkaDlg::NewEl el = Dlg.addel();   //Получение структуры со значениями полей записи
       ui->tableView->setColumnWidth(1, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(2, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(3, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(4, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(5, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(6, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(7, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(8, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(9, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(10, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(11, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(12, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(13, ui->tableView->width()/6);
       ui->tableView->setColumnWidth(14, ui->tableView->width()/6);
           ui->tableView->horizontalHeader()->moveSection( 8 , 1 );
           mdl->insertRows(mdl->rowCount(),1);     //Добавление новой записи в конец таблицы
           mdl->setData(mdl->index(mdl->rowCount()-1, 1), el.Korpus);  //Установка значений полей из структуры
           mdl->setData(mdl->index(mdl->rowCount()-1, 2), el.Plata);
           mdl->setData(mdl->index(mdl->rowCount()-1, 3), el.Processor);
           mdl->setData(mdl->index(mdl->rowCount()-1, 4), el.Disk);
           mdl->setData(mdl->index(mdl->rowCount()-1, 5), el.Operativa);
           mdl->setData(mdl->index(mdl->rowCount()-1, 6), el.SystemCold);
           mdl->setData(mdl->index(mdl->rowCount()-1, 7), el.Energy);
           mdl->setData(mdl->index(mdl->rowCount()-1, 8), el.Number);
           mdl->setData(mdl->index(mdl->rowCount()-1, 9), el.Video);
           mdl->setData(mdl->index(mdl->rowCount()-1, 10), el.Diskovod);
           mdl->setData(mdl->index(mdl->rowCount()-1, 11), el.Kartrider);
           mdl->setData(mdl->index(mdl->rowCount()-1, 12), el.Audio);
           mdl->setData(mdl->index(mdl->rowCount()-1, 13), el.TV);
           mdl->setData(mdl->index(mdl->rowCount()-1, 14), el.SPKarta);
           mdl->submitAll();                       //Подтверждение добавления поля
           qDebug() << mdl->lastError().text();
   }
}

void AllSborka::on_Redact_clicked()    //Кнопка "Редактировать"
{
    int curRec=ui->tableView->currentIndex().row();
    VievSborkaDlg Dlg(mdl,this,curRec);                       //Создание диалога для просмотра записей
    Dlg.setModal(true);
    Dlg.exec();
}

void AllSborka::on_Delete_clicked()  //Кнопка "Удалить"
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


