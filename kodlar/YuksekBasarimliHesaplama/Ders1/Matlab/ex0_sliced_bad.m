function ex3_bad
data = rand(4,4);
parfor I = 1:4
   j = I
   means(j) = mean(data(:,j));
end
disp(means)
