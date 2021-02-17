#ifndef NEWSBORKADLG_H
#define NEWSBORKADLG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class NewSborkaDlg;
}

class NewSborkaDlg : public QDialog
{
    Q_OBJECT

public:
    explicit NewSborkaDlg(QWidget *parent = nullptr);
    ~NewSborkaDlg();
    struct NewEl{
        int Number,Korpus,Plata,Processor,Disk,Operativa,SystemCold,Energy,Video,Audio,TV,Kartrider,Diskovod,SPKarta;
    };
    NewEl addel();

private:
    Ui::NewSborkaDlg *ui;
};

#endif // NEWSBORKADLG_H
