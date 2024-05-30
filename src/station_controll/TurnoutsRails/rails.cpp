#include "rails.h"

rails::rails() {
    setupScene();
}

rails::~rails() {
    delete railsSceneGraphic;
}

void rails::setupScene() {

    //horna cast
    //initial rail
    addLineToScene(0, 0, 120, 0, Qt::darkGray);

    //under 45 degree and 80 pixels long and make end longer by 20 pixels
    addLineWithTurnAngle(120, 0, 160, 40, Qt::red, 20, 0, 0);
    //imaginary turnout switch
    addLineWithTurnAngle(120, 0, 160, 0, Qt::yellow, 0, 0, 0);
    //under 45 degree and 40 pixels long
    addLineWithTurnAngle(120, 80, 160, 40, Qt::blue, 10, 0, 0);
    //imaginary turnout switch
    addLineWithTurnAngle(120, 80, 160, 80, Qt::yellow, 0, 0, 0);
    //turnout like this: addLineToScene(160, 40, 200, 0, Qt::red);
    addLineWithTurnAngleMirror(280, 80, 200, 0, Qt::red, 10, 0, 0);
    //imaginary turnout switch
    addLineWithTurnAngleMirror(280, 80, 200, 80, Qt::yellow, 0, 0, 0);
    //turnout opsite of addLineWithTurn(120, 0, 160, 40, Qt::red, 20, 0);
    addLineWithTurnAngleMirror(280, 0, 200, 80, Qt::blue, 10, 0, 0);
    //imaginary turnout switch
    addLineWithTurnAngleMirror(280, 0, 200, 0, Qt::yellow, 0, 0, 0);



    //turnout Left 40 pixels long 45 degree north
    //addLineWithTurnAngle(280, 0, 240, 40, Qt::green, 0, 180);
    //imaginary turnout switch
    //addLineWithTurnAngle(280, 0, 240, 0, Qt::yellow, 0, 180);

    //turnout Left 45 degree north after this: addLineWithTurn(280, 0, 240, 40, Qt::green, 0, 180);
    //addLineWithTurnAngle(320, 40, 280, 0, Qt::green, 0, 180);




    //addLineToScene(280, -40, 280, -80, Qt::green);
    //imaginary turnout switch under 45 degree
    //addLineToScene(280, -40, 320, -80, Qt::yellow);
    //40 pixels long rail 90 degree north
    //addLineToScene(280, -80, 280, -120, Qt::darkGray);
    //40 pixels long rail 45 degree north
    //addLineToScene(280, -120, 320, -160, Qt::darkGray);
    //straight line 40 pixels long
    //addLineToScene(320, -160, 600, -160, Qt::darkGray); //kolaj 7


    //turnout right north 40 pixels long 45 degree north
    //addLineToScene(320, -80, 360, -120, Qt::green);
    //imaginary turnout switch
    //addLineToScene(320, -80, 360, -80, Qt::yellow);
    //straight line 40 pixels long
    //addLineToScene(360, -120, 600, -120, Qt::darkGray); //kolaj 5

    //straight line 40 pixels long
    //addLineToScene(360, -80, 600, -80, Qt::darkGray); //kolaj 3

    //rail 280+600 pixels long straight
    //addLineToScene(280, 0, 880, 0, Qt::darkGray); //kolaj 1






    //dolna cast
    //initial rail under first one
    addLineToScene(0, 80, 120, 80, Qt::darkGray);

    //under 45 degree and 40 pixels long and mach end of blue line
    //addLineToScene(120, 80, 160, 40, Qt::red);
    //imaginary turnout switch
    //addLineToScene(120, 80, 160, 80, Qt::yellow);
    //under 45 degree and 40 pixels long
    //addLineToScene(160, 40, 200, 80, Qt::blue);
    //imaginary turnout switch
    //addLineToScene(160, 80, 200, 80, Qt::yellow);

    //rail 40 pixels long
    //addLineToScene(200, 80, 240, 80, Qt::darkGray);
    //turnout Left 40 pixels long 45 degree south
    //addLineToScene(240, 80, 280, 120, Qt::green);
    //imaginary turnout switch pointing to the right
    //addLineToScene(240, 80, 280, 80, Qt::yellow);

    //straight line 40 pixels long 45 degree south
    //addLineToScene(280, 120, 320, 160, Qt::darkGray);
    //turnout right east 40 pixels long 45 degree south
    //addLineToScene(320, 160, 360, 160, Qt::green);
    //imaginary turnout switch pointing to the right
    //addLineToScene(320, 160, 360, 200, Qt::yellow);

    //straight line 40 pixels long kolaj 4
    //addLineToScene(360, 160, 600, 160, Qt::darkGray);

    //turnout right 45 degree south 20 pixels long
    //addLineToScene(360, 200, 380, 220, Qt::green);
    //turnout straght 20 pixels long
    //addLineToScene(380, 220, 400, 220, Qt::green);
    //imaginary turnout switch opposite to 20pixel turnout straight to west
    //addLineToScene(380, 220, 360, 220, Qt::yellow);
    //imaginary turnout switch opposite to 20pixel turnout left 180 degree
    //addLineToScene(380, 220, 400, 240, Qt::yellow);



    //straight line 40 pixels long
    //addLineToScene(400, 220, 600, 220, Qt::darkGray); //kolaj 6


    //rail 280+600 pixels long straight
    addLineToScene(280, 80, 880, 80, Qt::darkGray); //kolaj 2





}

void rails::addLineToScene(int x1, int y1, int x2, int y2, QColor color) const {
    auto *line = new QGraphicsLineItem(x1, y1, x2, y2);
    //add condition if color is yellow no width
    if(color == Qt::yellow)
        line->setPen(QPen(color, 0, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
    else {
        line->setPen(QPen(color, 10, Qt::SolidLine, Qt::MPenCapStyle, Qt::BevelJoin));
    }
    railsSceneGraphic->addItem(line);
}

void rails::addLineWithTurnAngle(int x1, int y1, int x2, int y2, QColor color, int turnLength, double rotationAngle, int angle) {
    // Convert rotationAngle from degrees to radians
    double rotationAngleRad = rotationAngle * M_PI / 180;

    // Calculate the initial position of the line
    int x1_initial = x1 + 40 * cos(rotationAngleRad);
    int y1_initial = y1 + 40 * sin(rotationAngleRad);

    // First part of the line: straight until the turn
    addLineToScene(x1, y1, x1_initial, y1_initial, color);

    // Calculate the direction of the first line segment
    double direction = atan2(y2 - y1, x2 - x1) + rotationAngleRad;

    // Calculate the new direction after the turn
    double newDirection = direction + angle * M_PI / 180;

    // Calculate the end point of the second line segment
    int x3 = x1_initial + cos(newDirection) * (40 + turnLength);
    int y3 = y1_initial + sin(newDirection) * (40 + turnLength);

    // Second part of the line: after the turn
    addLineToScene(x1_initial, y1_initial, x3, y3, Qt::darkMagenta);
}

void rails::addLineWithTurnAngleMirror(int x1, int y1, int x2, int y2, QColor color, int turnLength, double rotationAngle, int angle) {
    // Convert rotationAngle from degrees to radians
    double rotationAngleRad = rotationAngle * M_PI / 180;

    // Calculate the initial position of the line
    int x1_initial = x1 - 40 * cos(rotationAngleRad);
    int y1_initial = y1 - 40 * sin(rotationAngleRad);

    // First part of the line: straight until the turn
    addLineToScene(x1, y1, x1_initial, y1_initial, color);

    // Calculate the direction of the first line segment
    double direction = atan2(y1 - y2, x1 - x2) + rotationAngleRad;

    // Calculate the new direction after the turn
    double newDirection = direction + angle * M_PI / 180;

    // Calculate the end point of the second line segment
    int x3 = x1_initial - cos(newDirection) * (40 + turnLength);
    int y3 = y1_initial - sin(newDirection) * (40 + turnLength);

    // Second part of the line: after the turn
    addLineToScene(x1_initial, y1_initial, x3, y3, Qt::darkMagenta);
}