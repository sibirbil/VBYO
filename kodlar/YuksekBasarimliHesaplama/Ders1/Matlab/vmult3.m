function time = vmult3(n) 
    A = rand(n,n);
    b = rand(n,1);
    c = zeros(n,1);
    
    tID = tic;
    for i = 1:n
        sum = 0;
        for k = 1:n
            sum = sum + A(i,k) * b(k);
        end
        c(i) = sum;    
    end
    
    time = toc(tID);
    d = A * b;
    error = norm(d-c,1)
end
