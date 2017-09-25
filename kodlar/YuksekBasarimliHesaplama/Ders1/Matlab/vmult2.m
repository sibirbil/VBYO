function time = vmult2(n) 
    A = rand(n,n);
    b = rand(n,1);
    c = zeros(n,1);
    
    tID = tic;
    for j = 1:n
        val = b(j);
        for k = 1:n
            c(k) = c(k) + A(k,j) * val;
        end
    end
    
    time = toc(tID);
    d = A * b;
    error = norm(d-c,1)
end
