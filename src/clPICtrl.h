#ifndef clPICtrl_INC
#define clPICtrl_INC

class clPICtrl
{
public:
	/**
	 * Constructor for PI controller.
	 */
	clPICtrl():
		m_r32ePro(0.0f),
		m_r32eInt(0.0f),
		m_r32Out(0.0f),
		m_r32Kp(0.0f),
		m_r32Ki(0.0f),
		m_r32TrackingFb(0.0f)
	{}

	~clPICtrl()
	{}

    /**
     * The method to evaluate control.
     *
     * @param   r32ErrIn    The input error value
     * @param   bBal        Balancing cmd to set the controller output to r32BalOut
     * @param   r32BalOut   Balancing reference for setting the controller output to this value
     * @return  real32      Control output.
     */
	 real32 r32Control(real32 const r32ErrIn, bool const bBal, real32 const r32BalOut);

    /**
     * Set PI controller coefficients according to the selected topology.
     *
     * @param   Kp  Proportional gain
     * @param   Ki  Integration time
     * @param   sampleInterval Sampling interval in (s)
     * @param   bAcademic true, if parameters are calculated according to the "academic" PID topology.
     *                    false, if the controller parameters follow "parallel" topology and are decoupled.
     */
	 void vSetParams(real32 const Kp, real32 const Ki, real32 const r32SampleInterval, bool const bAcademic);

    /**
    * Updates the (possibly saturated) output value for tracking anti-windup.
    * Note: Must be called prior to integrator evaluation to function properly.
    * Note: Unit must match with the control output.
    *
    * @param   r32TrackingFb   Control output value that exhibits all possible cases of output saturation.
    */
	void vUpdateTrackingTerm(real32 const r32TrackingFb);

private:
	real32 m_r32ePro;		// Propotional part
	real32 m_r32eInt;		// Integral part
	real32 m_r32Out;		// Controller output, sum of all terms
	real32 m_r32Kp;			// Proportional gain
	real32 m_r32Ki;			// Integral part gain
	real32 m_r32TrackingFb;	// Last saturated, limited signal from the end of the chain for tracking anti-windup.
	
	/**
	 * The method to ransform a time-based controller prarmeter (input) for internal representation,
	 * taking into account the samping rate.
	 *
	 * @param r32Coeff	Controller parameter
	 * @return real32	Transformed controller parameter.
	*/
	real32 r32CalcCoeff(real32 const r32Coeff, real32 const r32SampleInterval) const;


};
#endif // clPICtrl_INC
