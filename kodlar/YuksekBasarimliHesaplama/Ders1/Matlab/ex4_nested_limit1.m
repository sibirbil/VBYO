%For proper variable classification, the 
%range of a for-loop nested in a parfor 
%must be defined by constant numbers or 
%variables. In the following example, 
%the code on the left does not work because 
%the for-loop upper limit is defined by a function call. 

A = zeros(5, 5);
parfor i = 1:size(A, 1)
   for j = 1:size(A, 2)
      A(i, j) = plus(i, j);
   end
end
A