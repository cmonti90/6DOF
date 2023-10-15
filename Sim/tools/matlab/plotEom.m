clear;close all;clc;

dataDir = "/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/all";
fName = "eom.dat";

data = load(fullfile(dataDir, fName));

offset = 0;

idx.time = 1;
idx.posEci = 2:4;
idx.eulerAngs = 5:7 - offset;
idx.eulerAngRates = 8:10 - offset;
idx.qNedToBody = 11:14 - offset;

%% Plotting
nfig = 0;

% Pos ECI
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'PositionECI');

subplot(311)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(1)) - data(1, idx.posEci(1)))
xlabel('Time (sec)'); ylabel('\DeltaX (m)')
title("Position ECI")

subplot(312)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(2)) - data(1, idx.posEci(2)))
xlabel('Time (sec)'); ylabel('\DeltaY (m)')

subplot(313)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.posEci(3)) - data(1, idx.posEci(3)))
xlabel('Time (sec)'); ylabel('\DeltaZ (m)')


% Euler Angles
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'EulerAngles');

subplot(311)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(3)) * 180/pi)
xlabel('Time (sec)'); ylabel('Roll (deg)')
title('Euler Angles')

subplot(312)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(2)) * 180/pi)
xlabel('Time (sec)'); ylabel('Pitch (deg)')

subplot(313)
hold on;grid on;
plot(data(:, idx.time), data(:, idx.eulerAngs(1)) * 180/pi)
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


% Quaternion
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'NedToBodyQuat');

hold on;grid on;
plot(data(:, idx.time), data(:, idx.qNedToBody(1)), 'DisplayName', 'w')
plot(data(:, idx.time), data(:, idx.qNedToBody(2)), 'DisplayName', 'x')
plot(data(:, idx.time), data(:, idx.qNedToBody(3)), 'DisplayName', 'y')
plot(data(:, idx.time), data(:, idx.qNedToBody(4)), 'DisplayName', 'z')
xlabel('Time (sec)'); ylabel('(-)')
title('NED to Body Quaternion')
legend('location', 'best')



% Quaternion
nfig = nfig + 1;
h(nfig) = figure(nfig);
set(h(nfig), 'name', 'test');

hold on;grid on;
plot(data(:, idx.time), data(:, idx.qNedToBody(1)) + 4, 'DisplayName', 'w')
plot(data(:, idx.time), data(:, idx.qNedToBody(2)) + 4, 'DisplayName', 'x')
plot(data(:, idx.time), data(:, idx.qNedToBody(3)) + 4, 'DisplayName', 'y')
plot(data(:, idx.time), data(:, idx.qNedToBody(4)) + 4, 'DisplayName', 'z')
xlabel('Time (sec)'); ylabel('(-)')
title('test Quaternion')
legend('location', 'best')