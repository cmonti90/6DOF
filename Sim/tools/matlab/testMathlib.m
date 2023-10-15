clear;clc;

ang1 = 20 * pi / 180;
ang2 = 0 * pi / 180;
ang3 = 30 * pi / 180;

rottype='XZY';
outrottype = 'ZYX';

DCM = angle2dcm(ang1 , ang2, ang3, rottype)

syms axyz a0 a1 a2
% 
Rx = [1 0 0;
    0 cos(axyz) sin(axyz);
    0 -sin(axyz) cos(axyz)];

Ry = [cos(axyz) 0 -sin(axyz);
    0 1 0;
    sin(axyz) 0 cos(axyz)];

Rz = [cos(axyz) sin(axyz) 0;
    -sin(axyz) cos(axyz) 0;
    0 0 1];

Rx2 = subs(Rx, axyz, a2);
Ry2 = subs(Ry, axyz, a2);
Rz2 = subs(Rz, axyz, a2);

%%

Rx1 = subs(Rx, axyz, a1);
Ry1 = subs(Ry, axyz, a2);
Rz1 = subs(Rz, axyz, a0);

R = Ry1 * Rx1 * Rz1

R_a1_0 = subs(R, [a1 a2], [pi/2 0])

% [eul(1), eul(2), eul(3)] = dcm2angle(DCM, rottype);
% eul*180/pi
