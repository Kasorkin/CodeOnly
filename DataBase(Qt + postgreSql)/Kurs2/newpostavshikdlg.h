#ifndef NEWPOSTAVSHIKDLG_H
#define NEWPOSTAVSHIKDLG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class NewPostavshikdlg;
}

class NewPostavshikdlg : public QDialog
{
    Q_OBJECT

public:
    explicit NewPostavshikdlg(QWidget *parent = nullptr);
    ~NewPostavshikdlg();
    struct NewEq{
        QString PostNameCompany,PostDirector,PostBuhgalter;
        int PostRequisits,PostTip;
    };
    NewEq addel();
private:
    Ui::NewPostavshikdlg *ui;
};

#endif // NEWPOSTAVSHIKDLG_H
