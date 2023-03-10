/**
 * @author afpineda
 * @brief Use mean and variance as a noise filter for analog readings
 * @date 2023-03-03
 */

#include <Arduino.h>
#include <MeanAndVarOnTheFly.h>
#include <cmath>
 
// ADC Pin
// Change as you wish
#define ANALOG_PIN 36

// FILTER_STRENGTH must be a positive value.
// Higher values will filter more noise but at the cost of slower response to changes.
// Lower values (close to 0.0) means low filtering and quick response to changes.
// Set as you wish.
#define FILTER_STRENGTH (double)1.3f

// Count of samples for the ADC reading
// No need to touch
#define SAMPLE_SIZE 50

// Variables are global for simplification
MeanAndVar<int> population;
int steadyMean = 0;
bool firstRun = true;

// Noise Filter implementation
int noiseFilteredAnalogRead(const int adcPin) {
  // Read samples from the Analog-to-Digital Converter
  // and add them to the statistical population
  population.reset();
  for (int i = 0; i < SAMPLE_SIZE; i++)
    population.add(analogRead(adcPin));
  
  // Get the mean
  int newMean = population.getMean();

  // Print the unfiltered input, so you can check
  // how good the filter is with Arduino IDE's serial plotter
  Serial.print(newMean);
  Serial.print(", ");

  // On the first run, return the mean "as is"
  // Otherwise, compute the filtered reading
  if (firstRun) {
    steadyMean = newMean;
    firstRun = false;
  } else {

    // Get the absolute difference between the current reading
    // and the last filter result
    double diff = (steadyMean>newMean) ? (steadyMean - newMean) : (newMean - steadyMean);

    // Update the filter's result only if the current mean is out of the
    // range (steadyMean-FILTER_STRENGTH*standardDeviation,steadyMean+FILTER_STRENGTH*standardDeviation)
    double stdev = sqrt(population.getUnbiasedVariance());
    if (diff>(FILTER_STRENGTH*stdev))
      steadyMean = newMean;
  }
  return steadyMean;
}

void setup()
{
    // Initialize serial output
    Serial.begin(9600);

    // Initialize ADC pin
    pinMode(ANALOG_PIN,INPUT);
}


void loop() {
  int reading = noiseFilteredAnalogRead(ANALOG_PIN);
  Serial.println(reading);
  delay(100);
}
