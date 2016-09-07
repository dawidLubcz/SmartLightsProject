#include <QCoreApplication>
#include <stdio.h>
#include <ctestmovesensor.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    smartLights::smartLightsTests::CTestMoveSensor oTestObj;
    bool fTestResultPassed = true;

    fTestResultPassed &= oTestObj.createApp();
    fTestResultPassed &= oTestObj.TC_gate_room_sensor1_MoveDetected();
    fTestResultPassed &= oTestObj.TC_gate_room_sensor2_MoveDetected();
    fTestResultPassed &= oTestObj.TC_only_sensor1_MoveDetected();
    fTestResultPassed &= oTestObj.TC_only_sensor2_MoveDetected();
    fTestResultPassed &= oTestObj.TC_only_gate_MoveDetected();
    fTestResultPassed &= oTestObj.TC_turned_off_by_the_user();
    fTestResultPassed &= oTestObj.TC_turned_on_by_the_user();
    fTestResultPassed &= oTestObj.TC_brightness_set_by_the_user();
    fTestResultPassed &= oTestObj.destroyApp();


    printf("\n+-----------------------+\n");
    printf("| TEST FINISHED: %s |\n", (fTestResultPassed)?"\033[1;32m PASSED":"\033[0;31m FAILED");
    printf("\033[0m +-----------------------+\n");

    return a.exec();
}
