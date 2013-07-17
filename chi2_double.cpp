#include "mex.h"
#include "matrix.h"
#include <string.h>
#include <math.h>

#define min(a,b) ( (a<b)?(a):(b) )
#define max(a,b) ( (a>b)?(a):(b) )

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	//read two matrix
	double *X1;
	X1 = (double *) mxGetPr(prhs[0]);
    double *X2;
	X2 = (double *) mxGetPr(prhs[1]);
    mwSize n1, n2;
    n1 = mxGetM(prhs[0]);
    n2 = mxGetM(prhs[1]);
   
    int dim;
    dim = (int)mxGetN(prhs[0]);
    
    // read # threads
    int nthread;
    if(nrhs<3)
        nthread = 4;
    else
        nthread= (int)mxGetScalar(prhs[2]);
    
    double *K;
    plhs[0] =  mxCreateDoubleMatrix(n1, n2, mxREAL);
	K = mxGetPr(plhs[0]);
    
	int i, j, d; // i first, j second, d dimension
    double v;
	for(i = 0;i < n1;i ++)
	{
        #pragma omp parallel for private(j) reduction(+:v) num_threads(nthread)
        for(j = 0; j < n2; j ++)
        {
            v = 0;
            for(d = 0; d < dim; d ++)
                v += (X1[n1*d+i]-X2[n2*d+j]) * (X1[n1*d+i]-X2[n2*d+j]) / max(X1[n1*d+i]+X2[n2*d+j],1e-20);
            K[n1*j+i] = v;
        }
	}
    
}
