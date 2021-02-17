#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool CreateConnection();
    QSqlTableModel *getmodel();

private slots:
    void on_Exit_clicked();

    void on_Delete_clicked();

    void on_Redact_clicked();

    void on_Add_clicked();

    void on_Test_clicked();

    void on_PostProduct_clicked();

    void on_Manager_clicked();

    void on_DogovorInSborka_clicked();

    void on_Chet_clicked();

    void on_DogovorInPostavka_clicked();

    void on_Postavshik_clicked();

    void on_Sborka_clicked();

    void Start();

    void on_Go_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *mdl;
};
#endif // MAINWINDOW_H
