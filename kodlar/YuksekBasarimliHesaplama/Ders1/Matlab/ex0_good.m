% --------
% Workaround: create vector outside loop and use index vector
z = 0;
xAll = 0:0.1:1;
parfor I = 1:length(xAll)
    x = xAll(I);
    z = z + x;
end

% Copyright 2010 - 2014 The MathWorks, Inc.