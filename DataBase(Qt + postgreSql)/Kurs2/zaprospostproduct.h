#ifndef ZAPROSPOSTPRODUCT_H
#define ZAPROSPOSTPRODUCT_H

#include <QDialog>

namespace Ui {
class ZaprosPostProduct;
}

class ZaprosPostProduct : public QDialog
{
    Q_OBJECT

public:
    explicit ZaprosPostProduct(QWidget *parent = nullptr);
    ~ZaprosPostProduct();
    QString Metod();

private:
    Ui::ZaprosPostProduct *ui;
};

#endif // ZAPROSPOSTPRODUCT_H
