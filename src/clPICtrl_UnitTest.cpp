#include <cstdlib>
#include "unicos.h"
#include "clPICtrl.h"
#include "gtest/gtest.h"

/**
* This test covers PI-controller basic unit tests.
*/

// Test fixture class
class clPICtrl_UnitTest : public ::testing::Test
{
protected:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

/**
 * This test covers basic P-term evaluation.
 */
TEST_F(clPICtrl_UnitTest, ProportionalTerm)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const p_gain = 10.0f;
    PI.vSetParams(p_gain, 0.0f, 1.0f, false);

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    uindx const input_max = 9000uL;
    uindx const input_min = 1uL;

    real32 const Input = static_cast<real32>(input_min + (rand() % input_max - input_min + 1uL));
    real32 const Output = PI.r32Control(Input, false, 0.0f);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_output = Input * p_gain;
    ASSERT_FLOAT_EQ(expected_output, Output) << "Proportional gain applied incorrectly!";
}

/**
* This test covers the tracking function of I-term.
*/
TEST_F(clPICtrl_UnitTest, Tracking)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const p_gain = 3.0f;
    real32 const i_gain = 2.0f;
    real32 const sample_interval = 1.0f;
    PI.vSetParams(p_gain, i_gain, 1.0f, false);
    real32 const constant_error = 5.0f;
    real32 const saturated_value = 2.0f;

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    PI.vUpdateTrackingTerm(saturated_value);
    real32 const Output = PI.r32Control(constant_error, false, 0.0f);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_PI = (constant_error * p_gain) + (constant_error + saturated_value)*sample_interval / i_gain;
    real32 const actual_PI = Output;
    ASSERT_FLOAT_EQ(expected_PI, actual_PI) << "Output incorrect with saturated output!";
}

/**
* This test covers the basic I-term accumulation case
*/
TEST_F(clPICtrl_UnitTest, IntegrationTerm)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const i_gain = 2.0f;
    real32 const sample_interval = 1.0f;
    PI.vSetParams(0.0f, i_gain, sample_interval, false);

    uindx const loop_min = 10uL;
    uindx const loop_max = 1000uL;
    uindx const loops = loop_min + (rand() % static_cast<uindx>(loop_max - loop_min + 1uL));
    real32 const constant_error = 1.0f;
    real32 Output = 0.0f;

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    for (uindx i = 0; i < loops; i++)
    {
        PI.vUpdateTrackingTerm(Output);
        Output = PI.r32Control(constant_error, false, 0.0f);
    }

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_ITerm = loops*constant_error*sample_interval / i_gain;
    real32 const actual_ITerm = Output;
    ASSERT_FLOAT_EQ(expected_ITerm, actual_ITerm) << "I term accumulated incorrectly after " << loops << " steps!";
}

/**
* This test covers the basic I-term output balancing.
* - Bal ref enabled
* - Bal ref = some value
* --> Control output should equal bal ref.
*/
TEST_F(clPICtrl_UnitTest, Balancing)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const i_gain = 1.0f;
    PI.vSetParams(0.0f, i_gain, 1.0f, false);
    real32 const constant_error = 200.0f;

    // Pseudorandom reference between 1 and 100
    real32 const random_balref = 1.0f + static_cast<real32>(rand() % static_cast<uindx>(100uL));

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    real32 const Output = PI.r32Control(constant_error, true, random_balref);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_ITerm = random_balref;
    real32 const actual_ITerm = Output;
    ASSERT_FLOAT_EQ(expected_ITerm, actual_ITerm) << "Output not following balanced ref!";
}

/**
* This test covers normal PI opration.
* Academic mode is ON: Kp effects also I-part.
*/
TEST_F(clPICtrl_UnitTest, NormalPI)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const i_gain = 2.0f;
    real32 const sample_interval = 1.0f;
    real32 const p_gain = 10.0f;
    bool const academic_mode = true;
    PI.vSetParams(p_gain, i_gain, sample_interval, academic_mode);

    real32 const constant_error = 1.0f;
    real32 Output = 0.0f;

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    PI.vUpdateTrackingTerm(Output);
    Output = PI.r32Control(constant_error, false, 0.0f);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_PI = constant_error*p_gain*(1.0f + sample_interval / i_gain);
    real32 const actual_PI = Output;
    ASSERT_FLOAT_EQ(expected_PI, actual_PI) << "PI output erroneous!";
}

/**
* This test covers the testing of too low integration time
*/
TEST_F(clPICtrl_UnitTest, IntegrationTimeLow)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const i_gain = 1.9f; // i_gain < 2 x sample_interval !!!
    real32 const sample_interval = 1.0f;
    PI.vSetParams(0.0f, i_gain, sample_interval, false);

    real32 const constant_error = 1.0f;
    real32 Output = 0.0f;

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    PI.vUpdateTrackingTerm(Output);
    Output = PI.r32Control(constant_error, false, 0.0f);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_ITerm = 0.0f;
    real32 const actual_ITerm = Output;
    ASSERT_FLOAT_EQ(expected_ITerm, actual_ITerm) << "I term NOT zero!";
}

/**
* This test covers the testing of high enough integration time
*/
TEST_F(clPICtrl_UnitTest, IntegrationTimeOk)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const i_gain = 2.0f; // i_gain > 1.999x sample_interval -> ok
    real32 const sample_interval = 1.0f;
    PI.vSetParams(0.0f, i_gain, sample_interval, false);

    real32 const constant_error = 1.0f;
    real32 Output = 0.0f;

    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    PI.vUpdateTrackingTerm(Output);
    Output = PI.r32Control(constant_error, false, 0.0f);

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_ITerm = constant_error*sample_interval / i_gain;
    real32 const actual_ITerm = Output;
    ASSERT_FLOAT_EQ(expected_ITerm, actual_ITerm) << "I term erroneous!";
}

/**
* This test covers the anti-windup mechanism of the PI controller.
*/
TEST_F(clPICtrl_UnitTest, AntiWindup)
{
    //-----------------
    // INITIALIZATIONS:
    //-----------------
    clPICtrl PI;
    real32 const p_gain = 3.0f;
    real32 const i_gain = 2.0f;
    real32 const sample_interval = 1.0f;
    PI.vSetParams(p_gain, i_gain, sample_interval, false);

    uindx const loop_min = 20uL;
    uindx const loop_max = 30uL;
    uindx const loops = loop_min + (rand() % static_cast<uindx>(loop_max - loop_min + 1uL));
    real32 const constant_error = 5.0f;
    real32 output = 0.0f;
    real32 saturated_output = 3.0f;

    // Actual output remains saturated
    PI.vUpdateTrackingTerm(saturated_output);
    //----------------------
    // CALL UNIT UNDER TEST:
    //----------------------
    for (uindx i = 0; i < loops; i++)
    {
        output = PI.r32Control(constant_error, false, 0.0f);
    }

    //------------
    // ASSERTIONS:
    //------------
    real32 const expected_output = saturated_output + constant_error;
    real32 const actual_output = output;
    ASSERT_NEAR(expected_output, actual_output, 0.1f) << "Anti-windup not working correctly after " << loops << " steps!";
}
