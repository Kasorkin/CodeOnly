#ifndef NEWMANAGER_H
#define NEWMANAGER_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class newManager;
}

class newManager : public QDialog
{
    Q_OBJECT

public:
    explicit newManager(QWidget *parent = nullptr);
    ~newManager();
    struct NewEl {
       QString FIO;
    };
    NewEl addel();

private slots:

private:
    Ui::newManager *ui;
};

#endif // NEWMANAGER_H
