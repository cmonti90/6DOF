close all

dataPath = '/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/act';

data = load(fullfile(dataPath, 'actuation.dat'));

idx.time = 1;
idx.signal = 2;
idx.state = 3;

nfig = 0;

nfig = nfig + 1;
hnfig(nfig) = figure(nfig);
hold on;grid on;
plot(data(:, idx.time), data(:, idx.signal)*180/pi, 'displayname', 'signal')
plot(data(:, idx.time), data(:, idx.state)*180/pi, 'displayname', 'state')
xlabel('Time (sec)');ylabel('Ang (deg)')
title('Control Surface State Tracking')
legend('location', 'best')