f = zeros(1,10);
f(1) = 1;
f(2) = 2;
for n = 3:10
    f(n) = f(n-1) + f(n-2);
end
f(10)