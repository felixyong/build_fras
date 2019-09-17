clear mex;
clear ps*;
clear pm*;
clc;
clear;
close;
%% build and sim
ps_simStepTime = 5e-6;
ps_measSamplingTime = 50e-6;
ps_simEndTime = 0.2; 
mex timestwo.c
sim timestwo_sim.mdl 
%% plot output

figure('Name','times two s function');
subplot(1,1,1);
hold all;
plot(out_t,in,'DisplayName','in');
plot(out_t,out,'DisplayName','out');
xlabel('Time (s)');ylabel('input and output');
grid on;legend show;
hold off;
saveas(gcf,'graph');
saveas(gcf,'graph.jpg');
exit;