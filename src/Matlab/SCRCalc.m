function [ gridR_Ohm, gridL_H] = SCRCalc(f,Vg_pp, Pt, XRr, SCR)
%SCRCalc Calculates grid resistance and impedance for specific SCR ratio
%based on grid and generator parameters
%   Detailed explanation goes here
%   f:      fundamental frequency
%   Vg_pp:  grid voltage phase-to-phase, v
%   Pt:     rated power, VA
%   XRr:    grid X/R ratio, can use 10 as default value
%           From General Electric Application Information. Short-circuit Current Calculations. Appendix X/R Ratios ( From ANSI Standard C37.010):
%           E. Utility source
%           1.Near generating plant Range: 15-30
%           2.Long open-wire line Range: 2-16
%           3.Typical Range: 5-12
%   SCR:    grid short-circuit ratio

Pgrid = SCR*Pt; % Grid power
gridX = Vg_pp^2/(Pgrid*sqrt(1+(1/XRr)^2));
gridL_H = gridX/(2*pi*f);
gridR_Ohm = gridX/XRr;
end

