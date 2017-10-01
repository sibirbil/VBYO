prob = UFget(1345);
A = prob.A;
pamd = amd(A);
prcm = symrcm(A);
A_amd = A(pamd, pamd);
A_rcm = A(prcm, prcm);

b = rand(size(A,1),1);
tic; 
for i = 1:200, c = A * b; b = c; end 
toc
tic; 
for i = 1:200, c = A_amd * b; b = c; end 
toc
tic; 
for i = 1:200, c = A_rcm * b; b = c; end 
toc
