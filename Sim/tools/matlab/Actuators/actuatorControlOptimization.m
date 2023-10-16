clc;

optimizeGains = 0;
runModel = 1;
plotFigs = 1;

switchController = 1;

global Kp Ki Kd N;

Kp = 7469.1259;
Ki = 75079.5092;
Kd = 52.6578;
N = 1735.6444;

dampCoef = 5.0;
Iaxis = 0.05;

t0 = 0.0;
tfinal = 30;
dt = 0.001;

inpAmp = 5*pi/180;
inpPeriod = 2;
inpPulseWidth = 50;
inpPhaseDelay = 0;

if optimizeGains
    searchOutput = fmincon(@costFunc, [Kp; Ki; Kd; N], [], [], [], [], [0;0;0;0]);
end


if runModel
    simout = sim("actuationModel.slx");
end

if plotFigs && runModel
    close all;
    
    nfig = 0;

    nfig = nfig + 1;
    hfig(nfig) = figure(nfig);
    grid on; hold on;
    plot(simout.time, simout.input, 'displayname', 'Input')
    plot(simout.time, simout.theta, 'displayname', 'Theta')
    title("Tracking")
    legend('location', 'best')

    nfig = nfig + 1;
    hfig(nfig) = figure(nfig);
    grid on; hold on;
    subplot(211)
    plot(simout.time, simout.thetadot, 'displayname', 'Theta\_dot')
    title("Theta\_dot")
    legend('location', 'best')

    subplot(212)
    plot(simout.time, simout.thetadotdot, 'displayname', 'Theta\_dotdot')
    title("Theta\_dotdot")
    legend('location', 'best')

    nfig = nfig + 1;
    hfig(nfig) = figure(nfig);
    grid on; hold on;
    plot(simout.time, simout.error)
    title("Error")

    nfig = nfig + 1;
    hfig(nfig) = figure(nfig);
    grid on; hold on;
    plot(simout.time, simout.cmd)
    title("Cmd")
end