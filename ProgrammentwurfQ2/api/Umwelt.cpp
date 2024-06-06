#include "Umwelt.h"
#include <cmath>


Umwelt::Umwelt()
{
    time = 0;
    periodLength = 30;

    outsideTempMean = 18;
    outsideTempAmplitude = 12;

    insideTempMean = 20;
    insideTempAmplitude = 6;
    insideTempPhase = 6;

    sunIntensityMean = 40;
    sunIntensityAmplitude = 30;
}

double Umwelt::getOutsideTemp()
{
    return outsideTempMean + outsideTempAmplitude*sin(2*3.14*time++/periodLength);
}

double Umwelt::getInsideTemp()
{
    return insideTempMean + insideTempAmplitude*sin(2*3.14*(time++ - insideTempPhase)/periodLength);
}

double Umwelt::getSunIntensity()
{
    //return sunIntensityMean + sunIntensityAmplitude*sin(2*3.14*time++/periodLength);
    int periodicTime = time % (2*periodLength);
    return sunIntensityMean + sunIntensityAmplitude*(periodicTime - periodLength);
}
