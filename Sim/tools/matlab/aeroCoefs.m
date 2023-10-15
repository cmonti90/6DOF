density = 0.4135;

qbar = 0.5 * density * 223.52

%% CLalpha based on this graph: https://www.rccad2vr.com/aeronautics/how-to-read-a-cm-v-alpha-chart
close all;

points.X = [-10, -5, 0, 5, 10, 15, 20];
points.Y = [-0.65, -0.1, 0.48, 1.01, 1.49, 1.70, 1.51];

xdata = points.X;
ydata = points.Y;

xdata = -180:0.01:180;

a = -3.576e-6;
b = -7.293e-5;
c = -2.045e-4;
d = 0.1138;
e = 0.4707;
yfunc = a*xdata.^4 + b*xdata.^3 + c*xdata.^2 + d*xdata + e;

figure
hold on;grid on;
plot(points.X, points.Y, '.', 'MarkerSize', 12, 'Color', 'r', 'displayname', 'Truth')
plot(xdata, yfunc, "Color", 'g', 'LineStyle', '-', 'LineWidth', 3, 'displayname', 'Est')
legend('location', 'best')
axis([-180 180 -20 2])