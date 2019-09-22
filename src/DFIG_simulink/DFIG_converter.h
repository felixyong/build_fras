#pragma once

extern double time_s, tstep;
// Entry point for the simulator
double DFIG_converter(double in1, double in2, double in3);
void variables_to_zero(void);	// Initializes variables to zero