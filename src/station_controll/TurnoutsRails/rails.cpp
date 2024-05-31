#include "rails.h"

rails::rails() {
    setupScene();
}

rails::~rails() {
    delete railsSceneGraphic;
}

void rails::setupScene() {

    //horna lava cast
    //initial rail
    addLine(0, 0, 120, 0, Qt::darkGray);

    //under 45 degree and 80 pixels long and make end longer by 20 pixels
    addTurnoutToScene(120, 0, Qt::red, 0, false, false, false);
    //imaginary turnout switch
    addTurnoutToScene(120, 0, Qt::yellow, 0, true, false, false);
    //under 45 degree and 40 pixels long
    addTurnoutToScene(120, 80, Qt::blue, 0, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(120, 80, Qt::yellow, 0, true, true, false);
    //turnout like this: addLineToScene(160, 40, 200, 0, Qt::red);
    addTurnoutToScene(280, 80, Qt::red, 0, false, false, true);
    //imaginary turnout switch
    addTurnoutToScene(280, 80, Qt::yellow, 0, true, false, true);
    //turnout opsite of addLineWithTurn(120, 0, 160, 40, Qt::red, 20, 0);
    addTurnoutToScene(280, 0, Qt::blue, 0, false, true, true);
    //imaginary turnout switch
    addTurnoutToScene(280, 0, Qt::yellow, 0, true, true, true);



    //turnout Left 40 pixels long 45 degree north
    addTurnoutToScene(280, 0, Qt::green, 0, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(280, 0, Qt::yellow, 0, true, true, false);

    //turnout Left 45 degree north after this: addLineWithTurn(280, 0, 240, 40, Qt::green, 0, 180);
    addTurnoutToScene(360, -40, Qt::darkCyan, 315, false, true, false);
    //imaginary turnout switch straight line
    addTurnoutToScene(360, -40, Qt::yellow, 315, true, true, false);
    //turnout right after imaginary line
    addTurnoutToScene(440, -120, Qt::green, 315, false, false, false);
    //imaginary turnout switch
    addTurnoutToScene(440, -120, Qt::yellow, 315, true, false, false);
    //add straight line 40 pixels long after turnout
    addLine(520, -200, 560, -240, Qt::darkGray); //kolaj obluk ku kolaji 6

    //straight line 40 pixels long afterdarkCyan turnout
    addLine(400, -120, 400, -160, Qt::darkGray);
    //straight line
    addLine(400, -160, 560, -320, Qt::darkGray); //obluk ku kolaji 8
    //straight line
    addLine(560, -320, 880, -320, Qt::darkGray); //kolaj 8


    //straight line 40 pixels long
    addLine(560, -240, 880, -240, Qt::darkGray); //kolaj 6

    //straight line 40 pixels long
    addLine(520, -160, 880, -160, Qt::darkGray); //kolaj 4

    //rail 360 pixels long straight
    addLine(360, 0, 1850, 0, Qt::darkGray); //kolaj 2



    //dolna lava cast
    //initial rail under first one
    addLine(0, 80, 120, 80, Qt::darkGray);
    //straight line
    addLine(360, 80, 880, 80, Qt::darkGray); //kolaj 1
    //turnout line position start at 280
    addTurnoutToScene(280, 80, Qt::green, 0, false, false, false);
    //imaginary turnout switch
    addTurnoutToScene(280, 80, Qt::yellow, 0, true, false, false);
    //straight line under 45 degree
    addLine(360, 120, 440, 200, Qt::darkGray);
    //turnout left starting point 440,200
    addTurnoutToScene(440, 200, Qt::green, 45, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(440, 200, Qt::yellow, 45, true, true, false);
    //straight rail kolaj 4
    addLine(520, 240, 880, 240, Qt::darkGray); //kolaj 3

    //turnout left
    addTurnoutToScene(520, 280, Qt::green, 45, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(520, 280, Qt::yellow, 45, true, true, false);
    //cross turnout
    addTurnoutToScene(600, 360, Qt::darkCyan, 225, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(600, 360, Qt::yellow, 225, true, true, false);
    //turnout continue straight
    addTurnoutToScene(680, 440, Qt::green, 225, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(680, 440, Qt::yellow, 225, true, true, false);
    //turnout to odbocka
    addTurnoutToScene(600, 400, Qt::green, 180, false, true, false);
    //imaginary turnout switch
    addTurnoutToScene(600, 400, Qt::yellow, 180, true, true, false);
    //straight rail
    addLine(680, 320, 880, 320, Qt::darkGray); //kolaj 5
    //turnout ku kolaji 5 a 7
    addTurnoutToScene(600, 320, Qt::green, 0, false, false, false);
    //imaginary turnout switch
    addTurnoutToScene(600, 320, Qt::yellow, 0, true, false, false);
    //straight rail kolaj 7 obluk
    addLine(680, 360, 720,400, Qt::darkGray); //kolaj 7 obluk
    //straight rail kolaj 7
    addLine(720, 400, 880, 400, Qt::darkGray); //kolaj 7

    //straight rail
    addLine(680,440,720,480,Qt::darkGray); //kolaj 9 obluk
    //straight rail
    addLine(720,480,880,480,Qt::darkGray); //kolaj 9

    //straight rail odbočka
    addLine(520, 320, 0, 320, Qt::darkGray);
    addLine(520, 400, 80, 400, Qt::darkGray);
    //obluk
    addLine(520, 440, 480, 480, Qt::darkGray);
    addLine(480, 480, 80, 480, Qt::darkGray);









}

void rails::addTurnoutToScene(int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) const {
    // Convert angleTurnout from degrees to radians
    double angleTurnoutRad = angleTurnout * M_PI / 180;

    // Calculate the length of the first line
    double length1 = 40;
    if (angleTurnout == 45 || angleTurnout == 135 || angleTurnout == 225 || angleTurnout == 315) {
        length1 = sqrt(3200);
    }

    // Calculate the initial position of the first line
    int x1_initial, y1_initial;
    if (mirror) {
        x1_initial = x1 - length1 * cos(angleTurnoutRad);
        y1_initial = y1 - length1 * sin(angleTurnoutRad);
    } else {
        x1_initial = x1 + length1 * cos(angleTurnoutRad);
        y1_initial = y1 + length1 * sin(angleTurnoutRad);
    }

    // First part of the line: straight until the turn
    addLine(x1, y1, x1_initial, y1_initial, Qt::darkMagenta);

    // Calculate the direction of the first line segment
    double direction = angleTurnoutRad;

    // Calculate the new direction after the turn
    double newDirection;
    double length2 = 40;
    if (switchTurnout) {
        // If the turnout will switch, the second half will be straight
        newDirection = direction;
    } else if (flipped) {
        // If the turnout will be flipped, the default angle will be -45 degrees
        newDirection = direction - M_PI / 4;

    } else {
        // Otherwise, the default angle will be 45 degrees
        newDirection = direction + M_PI / 4;
    }

    // Calculate the length of the second line
    if (fabs(newDirection) == M_PI / 4 || fabs(newDirection) == 3 * M_PI / 4 || fabs(newDirection) == 5 * M_PI / 4 || fabs(newDirection) == 7 * M_PI / 4) {
        length2 = sqrt(3200);
        //qDebug() << "length2: " << length2;
    }

    // Calculate the end point of the second line segment
    int x2, y2;
    if (mirror) {
        x2 = x1_initial - length2 * cos(newDirection);
        y2 = y1_initial - length2 * sin(newDirection);
    } else {
        x2 = x1_initial + length2 * cos(newDirection);
        y2 = y1_initial + length2 * sin(newDirection);
    }

    // Second part of the line: after the turn
    addLine(x1_initial, y1_initial, x2, y2, color);
}



void rails::addLine(int x1, int y1, int x2, int y2, QColor color) const {
    auto *line = new QGraphicsLineItem(x1, y1, x2, y2);

    if (color == Qt::yellow){
        line->setPen(QPen(color, 3, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(1);
    } else {
        line->setPen(QPen(color, 10, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(0);
    }
    railsSceneGraphic->addItem(line);
}