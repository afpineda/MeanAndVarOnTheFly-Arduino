/**
 * @author afpineda
 * @brief Use mean as a filter for analog readings
 * @date 2023-03-03
 * 
 * @note The mean work as a filter. The analog input is supposed to stay "steady" while
 *       computing the mean, which is true for a short sampling interval (a few milliseconds). 
 *       In order to ensure such a condition, keep the sample size low. A sample size of 100
 *       is more than enough.
 * @note The variance is shown for demonstration porpuses.
 *       You may use the variance as a criteria to discard
 *       bad readings or as input to other filtering algorithms.
 */
 
#include <Arduino.h>
#include <MeanAndVarOnTheFly.h>

// Count of samples for the ADC reading
#define SAMPLE_SIZE 50

// ADC Pin
// Change as you wish
#define ANALOG_PIN 36

void setup()
{
    // Initialize serial output
    Serial.begin(9600);

    // Initialize ADC pin
    pinMode(ANALOG_PIN,INPUT);
}

// Create statistical population object
MeanAndVar<int> population;

void loop()
{
    population.reset();
    // Read samples from the Analog-to-Digital Converter
    // and add them to the statistical population
    for (int i=0; i<SAMPLE_SIZE; i++)
        population.add(analogRead(ANALOG_PIN));

    // Print mean and variance to the serial port
    Serial.print(population.getMean());
    Serial.print(", ");
    Serial.println(population.getUnbiasedVariance());

    // Wait before the next iteration
    delay(200);
}