clear;clc; close all;


idx.time = 1;
idx.posEcef = 2:4;
idx.velEcef = 5:7;
idx.accelEcef = 8:10;
idx.eulerAngs = 11:13;
idx.eulerAngRates = 14:16;
idx.qNedToBody = 17:20;
idx.accelEcef = 21:23;

dataDir = '/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/0';

runSimulink = 1;

testTranslational = 1;
F = [0, 0, 0];

testRotational = 0;
M = [0, 0, 0];

if runSimulink
    simlData = sim('EOM_ECEF_6DOF.slx');
end

sixDofData = load(fullfile(dataDir, "eom.dat"));

% Postion ECEF
figure('name', 'posECEF')
subplot(311)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.posEcef(1)), 'DisplayName', '6DOF')
plot(time, posEcef(:,1), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('X [m]')
legend('location', 'best')

subplot(312)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.posEcef(2)), 'DisplayName', '6DOF')
plot(time, posEcef(:,2), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Y [m]')
legend('location', 'best')

subplot(313)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.posEcef(3)), 'DisplayName', '6DOF')
plot(time, posEcef(:,3), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Z [m]')
legend('location', 'best')

% Velocity ECEF
figure('name', 'velECEF')
subplot(311)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.velEcef(1)), 'DisplayName', '6DOF')
plot(time, velEcef(:,1), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('X [m/sec]')
legend('location', 'best')

subplot(312)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.velEcef(2)), 'DisplayName', '6DOF')
plot(time, velEcef(:,2), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Y [m/sec]')
legend('location', 'best')

subplot(313)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.velEcef(3)), 'DisplayName', '6DOF')
plot(time, velEcef(:,3), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Z [m/sec]')
legend('location', 'best')

% Gravity ECEF
figure('name', 'Gravity ECEF')
subplot(311)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.accelEcef(1)), 'DisplayName', '6DOF')
plot(time, gravity(:,1), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('X [m/sec^2]')
legend('location', 'best')

subplot(312)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.accelEcef(2)), 'DisplayName', '6DOF')
plot(time, gravity(:,2), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Y [m/sec^2]')
legend('location', 'best')

subplot(313)
hold on;grid on
plot(sixDofData(:, idx.time), sixDofData(:, idx.accelEcef(3)), 'DisplayName', '6DOF')
plot(time, gravity(:,3), 'DisplayName', 'Simulink')
xlabel('Time [sec]');ylabel('Z [m/sec^2]')
legend('location', 'best')