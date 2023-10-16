close all

dataPath = '/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/act';

data = load(fullfile(dataPath, 'actuation.dat'));

dampCoef = 5.0;
Iaxis = 0.05;

t0 = 0.0;
tfinal = 5;
dt = 0.001;

inpAmp = 5*pi/180;
inpPeriod = 2;
inpPulseWidth = 50;
inpPhaseDelay = 0;

simout = sim("actuationModel.slx");

idx.time = 1;
idx.signal = 2;
idx.state = 3;
idx.ctrl = 4;
idx.thetadot = 5;
idx.thetadotdot = 6;

nfig = 0;

nfig = nfig + 1;
hnfig(nfig) = figure(nfig);
subplot(211)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.signal), 'b*-', 'displayname', 'inp_{C++}')
plot(data(:, idx.time), data(:, idx.state), 'r*-', 'displayname', 'theta_{C++}')
plot(simout.time, simout.input, 'm*-', 'displayname', 'inp_{Simulink}')
plot(simout.time, simout.theta, 'g*-', 'displayname', 'theta_{Simulink}')
xlabel('Time (sec)');ylabel('Ang (rad)')
title('Control Surface State Tracking')
legend('location', 'best')
lAxes(1) = gca;

subplot(212)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.ctrl), 'displayname', 'cmd_{C++}')
plot(simout.time, simout.cmd, 'displayname', 'cmd_{Simulink}')
xlabel('Time (sec)');ylabel('Cmd (rad/sec^{2})')
title('Control Surface PID Cmd')
legend('location', 'best')
lAxes(2) = gca;
linkaxes(lAxes, 'x');


nfig = nfig + 1;
hnfig(nfig) = figure(nfig);
subplot(211)
hold on;grid on;
simData = interp1(simout.time, simout.theta, data(:, idx.time));
plot(data(:, idx.time), data(:, idx.state) - simData, 'displayname', 'state')
xlabel('Time (sec)');ylabel('Ang (rad)')
lAxes(1) = gca;

subplot(212)
grid on; hold on;
simData = interp1(simout.time, simout.cmd, data(:, idx.time));
plot(data(:, idx.time), data(:, idx.ctrl) - simData)
xlabel('Time (sec)');ylabel("Cmd")
lAxes(2) = gca;
linkaxes(lAxes, 'x');

nfig = nfig + 1;
hfig(nfig) = figure(nfig);
grid on; hold on;
plot(data(:, idx.time), data(:, idx.ctrl), 'displayname', 'C++')
plot(simout.time, simout.cmd, 'displayname', 'Simulink')
xlabel('Time (sec)')
title("Cmd")
legend('location', 'best')


nfig = nfig + 1;
hnfig(nfig) = figure(nfig);
subplot(211)
hold on;grid on;
plot([0.0; data(:, idx.time) + 0.001], [0.0; data(:, idx.thetadot)], 'r*-', 'displayname', 'thetadot_{C++}')
plot(simout.time, simout.thetadot, 'g*-', 'displayname', 'thetadot_{Simulink}')
xlabel('Time (sec)');ylabel('Ang (rad)')
title('Thetdot')
legend('location', 'best')

subplot(212)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.thetadotdot), 'r*-', 'displayname', 'thetadotdot_{C++}')
plot(simout.time, simout.thetadotdot, 'g*-', 'displayname', 'thetadotdot_{Simulink}')
xlabel('Time (sec)');ylabel('Ang (rad)')
title('Thetdotdot')
legend('location', 'best')