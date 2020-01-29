#ifndef SET_BCM_H
#define SET_BCM_H

#include <QDialog>

namespace Ui {
class Set_bcm;
}

class Set_bcm : public QDialog
{
    Q_OBJECT

public:
    explicit Set_bcm(QWidget *parent = nullptr);
    ~Set_bcm();

private slots:
    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Set_bcm *ui;
};

#endif // SET_BCM_H
