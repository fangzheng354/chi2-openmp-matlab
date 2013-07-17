if ispc
    mex -largeArrayDims -O COMPFLAGS="$COMPFLAGS /openmp" LinkerFlags="$LinkerFlags /openmp" MEX_OPTION="$MEX_OPTION /lgomp" chi2_double.cpp
    mex -largeArrayDims -O COMPFLAGS="$COMPFLAGS /openmp" LinkerFlags="$LinkerFlags /openmp" MEX_OPTION="$MEX_OPTION /lgomp" chi2_float.cpp
else % linux or mac
    mex -largeArrayDims -O CXXFLAGS="\$CXXFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" chi2_double.cpp
    mex -largeArrayDims -O CXXFLAGS="\$CXXFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" chi2_float.cpp
end