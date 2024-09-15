#ifndef CCSMTR_RIGHTCLICKDIALOG_H
#define CCSMTR_RIGHTCLICKDIALOG_H

#include <QDialog>
#include "ui_RightClick.h"

class RightClick : public QDialog {
Q_OBJECT

public:
    explicit RightClick(QWidget *parent = nullptr);

    ~RightClick() override;


private:
    Ui_RightClick *ui;

};

#endif //CCSMTR_RIGHTCLICKDIALOG_H