function time = vmult(n) 
    A = rand(n,n);
    b = rand(n,1);
    c = zeros(n,1);
    
    tID = tic;
    for i = 1:n
        for k = 1:n
            c(i) = c(i) + A(i,k) * b(k);
        end
    end
    time = toc(tID);
    d = A * b;
    error = norm(d-c,1)
end
