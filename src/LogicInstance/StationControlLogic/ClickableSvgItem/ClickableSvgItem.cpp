#include "ClickableSvgItem.h"
#include <QSvgRenderer>
#include <QGraphicsScene>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

ClickableSvgItem::ClickableSvgItem(QGraphicsItem* parent)
        : QGraphicsSvgItem(parent) {
}

void ClickableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSvgItem::mousePressEvent(event);

    QString id = getElementIdAtPosition(event->pos());
    qDebug() << "Element ID retrieved:" << id;

    QRegularExpression re("^turnout_(\\d+)$");
    QRegularExpressionMatch match = re.match(id);
}

void ClickableSvgItem::loadGridLayout(const QString& layoutFilePath) {
    QDomDocument doc;
    QFile file(layoutFilePath);
    if (!file.exists()) {
        qWarning() << "Layout file does not exist:" << layoutFilePath;
        return;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open layout file:" << layoutFilePath << "Error:" << file.errorString();
        return;
    }
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse layout file:" << layoutFilePath;
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList elements = root.elementsByTagName("element");

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        QString type = element.attribute("type");
        QString id = element.attribute("id");
        int row = element.attribute("row").toInt();
        int col = element.attribute("col").toInt();

        QString svgFilePath;
        if (type == "turnout") {
            svgFilePath = "../layout/turnouts/turnout.svg";
        } else if (type == "rail") {
            svgFilePath = "../layout/rails/rail.svg";
        } else {
            continue;
        }

        QGraphicsSvgItem* svgItem = new QGraphicsSvgItem(svgFilePath);
        svgItem->setElementId(id);
        svgItem->setPos(col * 50, row * 50); // Adjust the position based on grid size

        if (scene()) {
            scene()->addItem(svgItem);
        } else {
            qWarning() << "Scene is null, cannot add item";
            delete svgItem;
        }
    }
}

void ClickableSvgItem::initialize() {
    loadGridLayout("../layout/layout.xml");
}

QString ClickableSvgItem::getElementIdAtPosition(const QPointF &position) {
    return QString();
}