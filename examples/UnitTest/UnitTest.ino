/**
 * @author afpineda
 * @brief Unit test for this library
 * @date 2023-03-03
 */

#include <Arduino.h>
#include <MeanAndVarOnTheFly.h>
#include <CovarianceOnTheFly.h>

void assert_equals(int expected, int actual, int testNumber)
{
    Serial.print("Test #");
    Serial.print(testNumber);
    if (expected != actual)
    {
        Serial.print(": ERROR. Expected ");
        Serial.print(expected);
        Serial.print(". Got ");
        Serial.print(actual);
    }
    else
        Serial.print(": OK");
    Serial.println(".");
}

void assert_equals_f(float expected, float actual, int testNumber)
{
    Serial.print("Test #");
    Serial.print(testNumber);
    float from = expected - 0.1;
    float to = expected + 0.1;
    if ((actual < from) || (actual > to))
    {
        Serial.print(": ERROR. Expected ");
        Serial.print(expected);
        Serial.print(". Got ");
        Serial.print(actual);
    }
    else
        Serial.print(": OK");
    Serial.println(".");
}

void setup()
{
    Serial.begin(115200);
    Serial.println("--START OF TEST--");
    Serial.println("You should not see any error message...");

    Serial.println("* Creating population object");
    MeanAndVar<int> pop;
    int testNumber = 1;

    Serial.println("* Initial state");
    assert_equals(0, pop.getCount(), testNumber++);
    assert_equals(0, pop.getMean(), testNumber++);
    assert_equals(0, pop.getUnbiasedVariance(), testNumber++);
    assert_equals(0, pop.getVariance(), testNumber++);

    Serial.println("* Adding population");
    Serial.println("** 1st");
    pop.add(12);
    assert_equals(1, pop.getCount(), testNumber++);
    assert_equals(12, pop.getMean(), testNumber++);
    assert_equals(0, pop.getUnbiasedVariance(), testNumber++);
    assert_equals(0, pop.getVariance(), testNumber++);

    Serial.println("** 2nd");
    pop.add(8);
    assert_equals(2, pop.getCount(), testNumber++);
    assert_equals(10, pop.getMean(), testNumber++);
    assert_equals(8, pop.getUnbiasedVariance(), testNumber++);
    assert_equals(4, pop.getVariance(), testNumber++);

    Serial.println("** 3rd");
    pop.add(10);
    assert_equals(3, pop.getCount(), testNumber++);
    assert_equals(10, pop.getMean(), testNumber++);
    assert_equals(4, pop.getUnbiasedVariance(), testNumber++);
    assert_equals(2, pop.getVariance(), testNumber++);

    Serial.println("** 4th");
    pop.add(-3);
    assert_equals(4, pop.getCount(), testNumber++);
    assert_equals(7, pop.getMean(), testNumber++);
    assert_equals(46, pop.getUnbiasedVariance(), testNumber++);
    assert_equals(34, pop.getVariance(), testNumber++);

    CovarianceMatrix<double> cov(2);
    Serial.println("* Covariance matrix (double)");

    Serial.println("** 5th");
    assert_equals(0, cov.getCount(), testNumber++);
    assert_equals_f(0.0, cov.getCovariance(0, 0), testNumber++);
    assert_equals_f(0.0, cov.getCovariance(0, 1), testNumber++);
    assert_equals_f(0.0, cov.getCovariance(1, 1), testNumber++);
    assert_equals_f(0.0, cov.getMean(0), testNumber++);
    assert_equals_f(0.0, cov.getMean(1), testNumber++);

    cov.add(3.0, 65.0);
    cov.add(5.0, 85.0);
    cov.add(2.0, 65.0);
    cov.add(7.0, 90.0);
    cov.add(4.0, 75.0);

    Serial.println("** 6th");
    assert_equals(5, cov.getCount(), testNumber++);
    assert_equals_f(4.2, cov.getMean(0), testNumber++);
    assert_equals_f(76.0, cov.getMean(1), testNumber++);
    assert_equals_f(16.8, cov.getCovariance(0, 1), testNumber++);

    Serial.println("--END OF TEST--");
}

void loop()
{
    delay(5000);
    // Serial.println(".");
}