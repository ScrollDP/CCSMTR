#ifndef CCSMTR_RIGHTCLICKDIALOG_H
#define CCSMTR_RIGHTCLICKDIALOG_H

#include <QDialog>
#include "ui_RightClick.h"
#include "../Rails/Rails.h"

class RightClick : public QDialog {
Q_OBJECT

public:
    explicit RightClick(QWidget *parent = nullptr);

    ~RightClick() override;
    void loadTurnout(int id);
    bool saveTurnout();

private:
    Ui_RightClick *ui;

};

#endif //CCSMTR_RIGHTCLICKDIALOG_H