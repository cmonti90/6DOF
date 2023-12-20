clear;clc; close all;

dataDir = '/home/cmonti/Documents/Coding/Projects/6DOF/Sim/run/output/0';

runSimulink = 1;
testTranslational = 1;
testRotational = 1;

if runSimulink
    sim('EOM_ECEF_6DOF.slx')
end

simData = load(fullfile(dataDir, "eom.dat"));
