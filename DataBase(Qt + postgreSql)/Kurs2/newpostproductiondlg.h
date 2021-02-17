#ifndef NEWPOSTPRODUCTIONDLG_H
#define NEWPOSTPRODUCTIONDLG_H

#include <QDialog>

namespace Ui {
class newPostProductiondlg;
}

class newPostProductiondlg : public QDialog
{
    Q_OBJECT

public:
    explicit newPostProductiondlg(QWidget *parent = nullptr);
    ~newPostProductiondlg();
    struct NewEs{
        QString Tip,Model;
    };
    NewEs addel();

private slots:

private:
    Ui::newPostProductiondlg *ui;
};

#endif // NEWPOSTPRODUCTIONDLG_H
