clear;clc; close all;

ang1 = 30 * pi / 180;
ang2 = 15 * pi / 180;
ang3 = 40 * pi / 180;

DCM = angle2dcm(ang1 , ang2, ang3, "ZXZ")

syms a0 a1 a2

% Rx1 = [1 0 0;
%     0 cos(a1) sin(a1);
%     0 -sin(a1) cos(a1)];

% Rx2 = [1 0 0;
%     0 cos(a2) sin(a2);
%     0 -sin(a2) cos(a2)];

Ry1 = [cos(a1) 0 -sin(a1);
    0 1 0;
    sin(a1) 0 cos(a1)];

% Ry2 = [cos(a2) 0 -sin(a2);
%     0 1 0;
%     sin(a2) 0 cos(a2)];

Rz1 = [cos(a0) sin(a0) 0;
    -sin(a0) cos(a0) 0;
    0 0 1];

Rz2 = [cos(a2) sin(a2) 0;
    -sin(a2) cos(a2) 0;
    0 0 1];

R = Rz2 * Ry1 * Rz1;

fprintf("\n")
for i = 1:3
    for j = 1:3
        str_std = strrep(strrep(string(R(i, j)), 'cos', 'std::cos'), 'sin', 'std::sin');
        str_vars = strrep(strrep(strrep(str_std, 'a0', 'this->vec[0]'), 'a1', 'this->vec[1]'), 'a2', 'this->vec[2]');
        fprintf("tmp[%i][%i] = %s;\n", i-1, j-1, str_vars)
    end
    fprintf("\n")
end