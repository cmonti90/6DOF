clear;clc; close all;

ang1 = 20 * pi / 180;
ang2 = 0 * pi / 180;
ang3 = 30 * pi / 180;

rottype='XZY';
outrottype = 'ZYX';

DCM = angle2dcm(ang1 , ang2, ang3, rottype)

syms axyz a0 a1 a2
% 
Rx1 = [1 0 0;
    0 cos(axyz) sin(axyz);
    0 -sin(axyz) cos(axyz)];

Rx1 = subs(Rx1, axyz, a0);

% Rx2 = [1 0 0;
%     0 cos(a2) sin(a2);
%     0 -sin(a2) cos(a2)];

Ry1 = [cos(axyz) 0 -sin(axyz);
    0 1 0;
    sin(axyz) 0 cos(axyz)];

Ry1 = subs(Ry1, axyz, a2);

% Ry2 = [cos(a2) 0 -sin(a2);
%     0 1 0;
%     sin(a2) 0 cos(a2)];

Rz1 = [cos(axyz) sin(axyz) 0;
    -sin(axyz) cos(axyz) 0;
    0 0 1];

Rz1 = subs(Rz1, axyz, a1);

% Rz2 = [cos(a2) sin(a2) 0;
%     -sin(a2) cos(a2) 0;
%     0 0 1];

R = Ry1 * Rz1 * Rx1

R = subs(R, [a1 a2], [pi/2 0])

[eul(1), eul(2), eul(3)] = dcm2angle(DCM, rottype);
eul*180/pi


pos = [1, 2, 3]*1300.0;

ecef2lla(pos)
