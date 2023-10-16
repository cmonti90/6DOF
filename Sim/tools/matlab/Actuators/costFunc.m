function costVal = costFunc(Inp)
    global Kp Ki Kd N;

    Kp = Inp(1);
    Ki = Inp(2);
    Kd = Inp(3);
    N = Inp(4);

    simout = sim("actuationModel.slx", 'ReturnWorkspaceOutputs', 'on');

    K.cmd = 0.000;
    K.error = 10;

    costVal = K.cmd * trapz(simout.cmd.^2) + K.error * trapz(simout.time .*simout.time .* simout.error.^2);