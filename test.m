A = rand(1000,100);
A = abs(A);

tic
X = chi2_double(A,A,1);
toc

tic
X = chi2_double(A,A,2);
toc