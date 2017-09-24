function time = mult(n) 
    A = rand(n,n);
    B = rand(n,n);
    C = zeros(n,n);
    
    tID = tic;
    for i = 1:n
        for j = 1:n
            for k = 1:n
                C(i,j) = C(i,j) + A(i,k) * B(k,j);
            end
        end
    end
    time = toc(tID);
    D = A * B;
    error = norm(C-D,1)
end
