#include "RightClick.h"
#include <QFile>
#include <QXmlStreamAttributes>
#include <QDomDocument>



RightClick::RightClick(QWidget *parent) : QDialog(parent), ui(new Ui::RightClick) {
    ui->setupUi(this);


}

RightClick::~RightClick() {
delete ui;
}
