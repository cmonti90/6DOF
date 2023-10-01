clear;close all;clc;

dataDir = "/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/0";
fName = "eom.dat";

data = load(fullfile(dataDir, fName));

idx.time = 1;
idx.posEci = 2:4;
idx.eulerAngs = 5:7;
idx.eulerAngRates = 8:10;

%% Plotting
nfig = 0;

% Pos ECI
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'PositionECI');

subplot(311)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(1)))
xlabel('Time (sec)'); ylabel('X (m)')
title("Position ECI")

subplot(312)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(2)))
xlabel('Time (sec)'); ylabel('Y (m)')

subplot(313)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(3)))
xlabel('Time (sec)'); ylabel('Z (m)')


% Euler Angles
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'EulerAngles');

subplot(311)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(1)) * 180/pi)
xlabel('Time (sec)'); ylabel('Roll (deg)')
title('Euler Angles')

subplot(312)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(2)) * 180/pi)
xlabel('Time (sec)'); ylabel('Pitch (deg)')

subplot(313)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(3)) * 180/pi)
xlabel('Time (sec)'); ylabel('Yaw (deg)')


% Euler Angle Rates
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'EulerAngleRates');

subplot(311)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngRates(1)) * 180/pi)
xlabel('Time (sec)'); ylabel('Roll Rate (deg/sec)')
title('Euler Angle Rates')

subplot(312)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngRates(2)) * 180/pi)
xlabel('Time (sec)'); ylabel('Pitch Rate (deg/sec)')

subplot(313)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngRates(3)) * 180/pi)
xlabel('Time (sec)'); ylabel('Yaw Rate (deg/sec)')
