#ifndef GET_WIRELESS_DATA_H
#define GET_WIRELESS_DATA_H

#include <QDialog>

namespace Ui {
class Get_wireless_data;
}

class Get_wireless_data : public QDialog
{

public:
    explicit Get_wireless_data(QWidget *parent = nullptr);
    ~Get_wireless_data();
    Q_OBJECT
    Ui::Get_wireless_data *ui;
    void changetext();

private slots:
    void on_pushButton_clicked();

private:
};

#endif // GET_WIRELESS_DATA_H
