#include <QFile>
#include <QXmlStreamAttributes>
#include <QDomDocument>
#include "RightClick.h"


RightClick::RightClick(QWidget *parent) : QDialog(parent), ui(new Ui::RightClick) {
    ui->setupUi(this);

    //rails = new Rails();
    //save button pressed it will save
    connect(ui->SaveButton, &QPushButton::clicked, this, [=]() {
        this->saveTurnout();
        // Ensure rails is initialized
       /* if (rails == nullptr) {
            qDebug() << "rails is not initialized";
            return;
        }*/
        //rails->loadFromXmlTurnouts(railsAction->m_turnoutId, Rails::fileName);
    });
}

RightClick::~RightClick() {
delete ui;
}

void RightClick::loadTurnout(int id) {
    QFile file(Rails::fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString());
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "Cannot parse XML file: " << qPrintable(file.errorString());
        return;
    }
    file.close();

    QDomElement root = doc.firstChildElement("turnouts");
    QDomNodeList turnoutList = root.elementsByTagName("turnout");
    for (int i = 0; i < turnoutList.size(); ++i) {
        QDomElement turnoutElement = turnoutList.at(i).toElement();
        if (turnoutElement.attribute("id").toInt() == id) {
            int dccaddress = turnoutElement.firstChildElement("dccaddress").text().toInt();
            //load switch status
            int switchTurnout = turnoutElement.firstChildElement("switchTurnout").text().toInt();
            ui->TurnoutID->setText(QString::number(id));
            ui->AddressSet->setText(QString::number(dccaddress));
            if(switchTurnout == 1)
            {
                ui->SwitchCheckBox->setChecked(true);
            }
            else{
                ui->SwitchCheckBox->setChecked(false);
            }
            break;
        }
    }
}

bool RightClick::saveTurnout() {
    int id = ui->TurnoutID->toPlainText().toInt();
    int dccaddress = ui->AddressSet->toPlainText().toInt();

    QFile file(Rails::fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading: " << qPrintable(file.errorString());
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "Cannot parse XML file: " << qPrintable(file.errorString());
    }
    file.close();

    QDomElement root = doc.firstChildElement("turnouts");
    QDomNodeList turnoutList = root.elementsByTagName("turnout");
    for (int i = 0; i < turnoutList.size(); ++i) {
        QDomElement turnoutElement = turnoutList.at(i).toElement();
        if (turnoutElement.attribute("id").toInt() == id) {
            //save dccaddress as int
            turnoutElement.firstChildElement("dccaddress").firstChild().setNodeValue(QString::number(dccaddress));
            //save switch status as int
            if(ui->SwitchCheckBox->isChecked()){
                turnoutElement.firstChildElement("switchTurnout").firstChild().setNodeValue("1");
            }
            else{
                turnoutElement.firstChildElement("switchTurnout").firstChild().setNodeValue("0");
            }
            break;
        }
    }

    // If the file was successfully opened and the XML was successfully parsed
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << doc.toString();
        file.close();
        return true; // Return true if the save operation was successful
    }

    // If the file could not be opened or the XML could not be parsed
    qDebug() << "Cannot open file for writing: " << qPrintable(file.errorString());
    return false; // Return false if the save operation failed
}