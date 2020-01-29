#ifndef SET_ADVICE_H
#define SET_ADVICE_H

#include <QDialog>

namespace Ui {
class Set_devices;
}

class Set_devices : public QDialog
{

public:
    explicit Set_devices(QWidget *parent = nullptr);
    ~Set_devices();
        Q_OBJECT
        Ui::Set_devices *ui;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

private:
};

#endif // SET_ADVICE_H
