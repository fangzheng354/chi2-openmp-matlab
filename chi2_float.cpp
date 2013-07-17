#include "mex.h"
#include "matrix.h"
#include <string.h>
#include <math.h>
#include <fstream>
using namespace std;

#define min(a,b) ( (a<b)?(a):(b) )
#define max(a,b) ( (a>b)?(a):(b) )
typedef unsigned char uchar;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	//read two matrix
	float *X1;
	X1 = (float *) mxGetPr(prhs[0]);
    float *X2;
	X2 = (float *) mxGetPr(prhs[1]);
    int n1, n2;
    int dim;
    n1 = (int)mxGetM(prhs[0]);
    n2 = (int)mxGetM(prhs[1]);
    dim = (int)mxGetN(prhs[0]);
    
    // read # threads
    int nthread;
    if(nrhs<3)
    {
        nthread = 4;
    }
    else
    {
        nthread=mxGetScalar(prhs[2]);
    }

	float *K;
    mwSize dims[2];
    dims[0] = n1;
    dims[1] = n2;
    plhs[0] = mxCreateNumericArray(2, dims, mxSINGLE_CLASS, mxREAL);
    
	K = (float*)mxGetPr(plhs[0]);
	memset(K, 0, sizeof(float)*n1*n2);
        
	int i, j, k;
    float v;
    //#pragma omp parallel for private(i) 
	for(i = 0;i < n1;i ++)
	{
        #pragma omp parallel for private(j) reduction(+:v) num_threads(nthread)
        for(j = 0; j < n2; j ++)
        {
            v = 0;
            for(k = 0; k < dim; k ++)
                v += (X1[n1*k+i]-X2[n2*k+j]) * (X1[n1*k+i]-X2[n2*k+j]) / max(X1[n1*k+i]+X2[n2*k+j],1e-20);
            K[n1*j+i] = v;
        }
	}

}
