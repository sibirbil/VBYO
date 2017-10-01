%The index variable for the nested for loop 
%must never be explicitly assigned other than 
%in its for statement. When using the nested 
%for-loop variable for indexing the sliced array, 
%you must use the variable in plain form, not as 
%part of an expression.

A = zeros(4, 11);
parfor i = 1:4
   for j = 1:10
      A(i, j + 1) = i + j;
   end
end
 