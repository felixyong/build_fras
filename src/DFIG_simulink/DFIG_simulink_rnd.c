#define S_FUNCTION_NAME DFIG_simulink_rnd /* Defines and Includes */
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include "DFIG_converter.h"

double inputs[10];
double results[50];
int nOutputs;
void DFIG_simulink(double* arg, double* res);

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch reported by the Simulink engine*/
    }

    if (!ssSetNumInputPorts(S, 6)) return;		// Number of input ports
    ssSetInputPortWidth(S, 0, 3);
	ssSetInputPortWidth(S, 1, 1);
	ssSetInputPortWidth(S, 2, 1);
	ssSetInputPortWidth(S, 3, 1);
	ssSetInputPortWidth(S, 4, 1);
	ssSetInputPortWidth(S, 5, 1);

	ssSetInputPortDirectFeedThrough(S, 0, 1);
	ssSetInputPortDirectFeedThrough(S, 1, 1);
	ssSetInputPortDirectFeedThrough(S, 2, 1);
	ssSetInputPortDirectFeedThrough(S, 3, 1);
	ssSetInputPortDirectFeedThrough(S, 4, 1);
	ssSetInputPortDirectFeedThrough(S, 5, 1);

	nOutputs = 26;

    if (!ssSetNumOutputPorts(S, nOutputs)) return;	// Number of output ports
    ssSetOutputPortWidth(S, 0, 3);	// Ig, width of the output ports
	ssSetOutputPortWidth(S, 1, 1);	// Tel
	ssSetOutputPortWidth(S, 2, 1);	// Udc_v
	ssSetOutputPortWidth(S, 3, 3);	// Us_V
	ssSetOutputPortWidth(S, 4, 3);	// Is_V
	ssSetOutputPortWidth(S, 5, 3);	// Ur_V
	ssSetOutputPortWidth(S, 6, 3);	// Ir_V
	ssSetOutputPortWidth(S, 7, 1);	// Chopper_st

	ssSetOutputPortWidth(S, 8, 1);	// CB_THYR
	ssSetOutputPortWidth(S, 9, 1);	// E_CB_Ws
	ssSetOutputPortWidth(S, 10, 1);	// E_chopper_Ws
	ssSetOutputPortWidth(S, 11, 1);	// Chopper_al
	ssSetOutputPortWidth(S, 12, 1);	// conv_trip
	ssSetOutputPortWidth(S, 13, 1);	// fault_bit
	ssSetOutputPortWidth(S, 14, 3);	// Iisu_preLCL
	ssSetOutputPortWidth(S, 15, 3);	// Iisu_postLCL

	ssSetOutputPortWidth(S, 16, 2);	// ISU_PQ
	ssSetOutputPortWidth(S, 17, 2);	// ISQP1Q1
	ssSetOutputPortWidth(S, 18, 1);	// dip_bit
	ssSetOutputPortWidth(S, 19, 2);	// Qref_INU_ISU
	ssSetOutputPortWidth(S, 20, 1);	// Stator_P_lim
	ssSetOutputPortWidth(S, 21, 1);	// I_ac
	ssSetOutputPortWidth(S, 22, 1);	// V_ac
	ssSetOutputPortWidth(S, 23, 1);	// I_bch

	ssSetOutputPortWidth(S, 24, 4);
	ssSetOutputPortWidth(S, 25, 4);

    ssSetNumSampleTimes(S, 1);
	ssSetNumRWork(S, 0);
	ssSetNumIWork(S, 0);
	ssSetNumPWork(S, 0);
	ssSetNumModes(S, 0);
	ssSetNumNonsampledZCs(S, 0);
    /* Take care when specifying exception free code - see sfuntmpl.doc */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
    }

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 5e-6);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);

	real_T* y1 = ssGetOutputPortRealSignal(S, 0);
	real_T* y2 = ssGetOutputPortRealSignal(S, 1);
	real_T* y3 = ssGetOutputPortRealSignal(S, 2);
	real_T* y4 = ssGetOutputPortRealSignal(S, 3);
	real_T* y5 = ssGetOutputPortRealSignal(S, 4);
	real_T* y6 = ssGetOutputPortRealSignal(S, 5);
	real_T* y7 = ssGetOutputPortRealSignal(S, 6);
	real_T* y8 = ssGetOutputPortRealSignal(S, 7);
	real_T* y9 = ssGetOutputPortRealSignal(S, 8);
	real_T* y10 = ssGetOutputPortRealSignal(S, 9);
	real_T* y11 = ssGetOutputPortRealSignal(S, 10);
	real_T* y12 = ssGetOutputPortRealSignal(S, 11);
	real_T* y13 = ssGetOutputPortRealSignal(S, 12);
	real_T* y14 = ssGetOutputPortRealSignal(S, 13);
	real_T* y15 = ssGetOutputPortRealSignal(S, 14);
	real_T* y16 = ssGetOutputPortRealSignal(S, 15);
	real_T* y17 = ssGetOutputPortRealSignal(S, 16);
	real_T* y18 = ssGetOutputPortRealSignal(S, 17);
	real_T* y19 = ssGetOutputPortRealSignal(S, 18);
	real_T* y20 = ssGetOutputPortRealSignal(S, 19);
	real_T* y21 = ssGetOutputPortRealSignal(S, 20);
	real_T* y22 = ssGetOutputPortRealSignal(S, 21);
	real_T* y23 = ssGetOutputPortRealSignal(S, 22);
	real_T* y24 = ssGetOutputPortRealSignal(S, 23);
	real_T* y25 = ssGetOutputPortRealSignal(S, 24);
	real_T* y26 = ssGetOutputPortRealSignal(S, 25);

	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S, 0);
	InputRealPtrsType uPtrs2 = ssGetInputPortRealSignalPtrs(S, 1);
	InputRealPtrsType uPtrs3 = ssGetInputPortRealSignalPtrs(S, 2);
	InputRealPtrsType uPtrs4 = ssGetInputPortRealSignalPtrs(S, 3);
	InputRealPtrsType uPtrs5 = ssGetInputPortRealSignalPtrs(S, 4);
	InputRealPtrsType uPtrs6 = ssGetInputPortRealSignalPtrs(S, 5);

	if (time_s < 1e-9)
		variables_to_zero();

	// Inputs for the simulator
	inputs[0] = *(uPtrs1[0]); //Ugrid_a (V)
	inputs[1] = *(uPtrs1[1]); //Ugrid_b (V)
	inputs[2] = *(uPtrs1[2]); //Ugrid_c (V)

	inputs[3] = *(uPtrs2[0]); //Teref_Nm_in;
	inputs[4] = *(uPtrs3[0]); //Q_ref_INU_in;
	inputs[5] = *(uPtrs4[0]); //n_rpm_in;
	inputs[6] = *(uPtrs5[0]); //Q_ref_ISU_in;



	// Run the actual simulation (for one step)
	DFIG_simulink(inputs, results);
	
	// Set outputs
	// Current to grid
	y1[0] = results[0];
	y1[1] = results[1];
	y1[2] = results[2];
	// Tel
	y2[0] = results[3];
	// Udc_V
	y3[0] = results[4];
	// Us_V
	y4[0] = results[5];
	y4[1] = results[6];
	y4[2] = results[7];
	// Is_V
	y5[0] = results[8];
	y5[1] = results[9];
	y5[2] = results[10];
	// Ur_V
	y6[0] = results[11];
	y6[1] = results[12];
	y6[2] = results[13];
	// Ir_A
	y7[0] = results[14];
	y7[1] = results[15];
	y7[2] = results[16];
	// chopper_st
	y8[0] = results[17];
	// CB_THYR
	y9[0] = results[18];
	// E_CB_Ws
	y10[0] = results[19];
	// E_chopper_Ws
	y11[0] = results[20];
	// chopper_al
	y12[0] = results[21];
	// conv_trip
	y13[0] = results[22];
	// fault_bit
	y14[0] = results[23];
	// Iisu_A pre LCL
	y15[0] = results[24];
	y15[1] = results[25];
	y15[2] = results[26];
	// Iisu_A post LCL
	y16[0] = results[27];
	y16[1] = results[28];
	y16[2] = results[29];
	// ISU_P_kW
	y17[0] = results[30];
	// ISU_Q_kVAr
	y17[1] = results[31];
	// ISU_P1_kW
	y18[0] = results[32];
	// ISU_Q1_kVAr
	y18[1] = results[33];
	//dip_bit
	y19[0] = results[34];
	// Q_ref_VAr
	y20[0] = results[35];
	y20[1] = results[36];
	//Available stator power
	y21[0] = results[37];
	//I_ac active crowbar current through the resistance
	y22[0] = results[38];
	//V_ac Active crowbar voltage over the resistance
	y23[0] = results[39];
	//I_bch current through the break chopper resistance
	y24[0] = results[40];
	// DEBUG VARIABLES
	//debug1  4 elements
	y25[0] = results[41];
	y25[1] = results[42];
	y25[2] = results[43];
	y25[3] = results[44];
	//debug2  4 elements
	y26[0] = results[45];
	y26[1] = results[46];
	y26[2] = results[47];
	y26[3] = results[48];
}

static void mdlTerminate(SimStruct *S)
{
	time_s = 0;
}


/* Simulink/Real-Time Workshop Interface */

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif

void DFIG_simulink(double* arg, double* res)
{
	double U_in1;
	double U_in2;
	double U_in3;
	double ramp_up;
	double Teref_Nm_in;
	double Q_ref_ISU_in;
	double Q_ref_INU_in;
	double n_rpm_in;

	U_in1 = arg[0];
	U_in2 = arg[1];
	U_in3 = arg[2];
	Teref_Nm_in = arg[3];
	Q_ref_INU_in = arg[4];
	n_rpm_in = arg[5];
	Q_ref_INU_in = arg[6];

	DFIG_converter(U_in1, U_in2, U_in3);

}