#pragma once

class Umwelt
{
        int time;
        int periodLength;
        int outsideTempMean;
        int outsideTempAmplitude;
        int insideTempMean;
        int insideTempAmplitude;
        int insideTempPhase;
        int sunIntensityMean;
        int sunIntensityAmplitude;

    public:

        // Creates a simulation of the environment 
        Umwelt();

        // The following functions simulate measurements
        double getOutsideTemp();
        double getInsideTemp();
        double getSunIntensity();
};