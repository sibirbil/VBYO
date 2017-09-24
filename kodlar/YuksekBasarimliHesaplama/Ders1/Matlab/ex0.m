function total = ex0() 
    clear A;    
    for i = 1:10
        A(i) = i*1000000;
    end
    B = zeros(10,1);
    tic
    for i = 1:length(A)
        B(i) = f(A(i));
    end
    total = sum(B);
    toc
end

function total = f(n)
    total = 0;  
    for i = 1:n
        total = total + 1/i;
    end
end

