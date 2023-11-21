/**
 * @author afpineda
 * @brief Unit test for this library
 * @date 2023-03-03
 */

#include<Arduino.h>
#include<MeanAndVarOnTheFly.h>
#include<CovarianceOnTheFly.h>

void assert_equals(int expected, int actual, int testNumber)
{
    Serial.print("Test #");
    Serial.print(testNumber);
    if (expected!=actual) {
        Serial.print(": ERROR. Expected ");
        Serial.print(expected);
        Serial.print(". Got ");
        Serial.print(actual);
    } else
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
    assert_equals(0,pop.getCount(),testNumber++);
    assert_equals(0,pop.getMean(),testNumber++);
    assert_equals(0,pop.getUnbiasedVariance(),testNumber++);
    assert_equals(0,pop.getVariance(),testNumber++);

    Serial.println("* Adding population");
    Serial.println("** 1st");
    pop.add(12);
    assert_equals(1,pop.getCount(),testNumber++);
    assert_equals(12,pop.getMean(),testNumber++);
    assert_equals(0,pop.getUnbiasedVariance(),testNumber++);
    assert_equals(0,pop.getVariance(),testNumber++);

    Serial.println("** 2nd");
    pop.add(8);
    assert_equals(2,pop.getCount(),testNumber++);
    assert_equals(10,pop.getMean(),testNumber++);
    assert_equals(8,pop.getUnbiasedVariance(),testNumber++);
    assert_equals(4,pop.getVariance(),testNumber++);

    Serial.println("** 3rd");
    pop.add(10);
    assert_equals(3,pop.getCount(),testNumber++);
    assert_equals(10,pop.getMean(),testNumber++);
    assert_equals(4,pop.getUnbiasedVariance(),testNumber++);
    assert_equals(2,pop.getVariance(),testNumber++);

    Serial.println("** 4th");
    pop.add(-3);
    assert_equals(4,pop.getCount(),testNumber++);
    assert_equals(7,pop.getMean(),testNumber++);
    assert_equals(46,pop.getUnbiasedVariance(),testNumber++);
    assert_equals(34,pop.getVariance(),testNumber++);

    Covariance<int> cov;
    cov.add(3,65);
    cov.add(5,85);
    cov.add(2,65);
    cov.add(7,90);
    cov.add(4,75);
    Serial.println("* Covariance");

    Serial.println("** 5th");
    assert_equals(5,cov.getCount(),testNumber++);
    assert_equals(22,cov.getCurrent(),testNumber++);

    Serial.println("--END OF TEST--");
}

void loop()
{
    delay(5000);
    //Serial.println(".");
}