A = zeros(4,5);
parfor j = 1:4
    for k = 1:5
        A(j,k) = j + k;
    end
end
A
