#include <stdlib.h>
#ifdef HAVE_HDF5
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
using namespace H5;
using namespace std;
namespace bf = boost::filesystem;

const H5std_string FILE_NAME("results/Select.h5");
const H5std_string	DATASET_NAME("Matrix in file");
const int   MSPACE1_RANK = 1;   // Rank of the first dataset in memory
const int   MSPACE1_DIM = 50;   // Dataset size in memory
const int   MSPACE2_RANK = 1;   // Rank of the second dataset in memory
const int   MSPACE2_DIM = 4;    // Dataset size in memory
const int   FSPACE_RANK = 2;    // Dataset rank as it is stored in the file
const int   FSPACE_DIM1 = 8;    // Dimension sizes of the dataset as it is
const int   FSPACE_DIM2 = 12;   //  stored in the file
const int   MSPACE_RANK = 2;    // Rank of the first dataset in memory
const int   MSPACE_DIM1 = 8;    // We will read dataset back from the file
const int   MSPACE_DIM2 = 9;    //  to the dataset in memory with these
                //  dataspace parameters
const int   NPOINTS = 4;    // Number of points that will be selected
                //  and overwritten

int main(void)  
{  
  bf::path pdir("results");
  bf::create_directory(pdir);

  int i,j;

  try
  {
    //try exception
    Exception::dontPrint();

    //create file by default
    H5File* file = new H5File(FILE_NAME, H5F_ACC_TRUNC);

    int fillvalue =0;
    DSetCreatPropList plist;
    plist.setFillValue(PredType::NATIVE_INT, &fillvalue);

    hsize_t fdim[] = {FSPACE_DIM1, FSPACE_DIM2};
    DataSpace fspace(FSPACE_RANK, fdim);

    DataSet* dataset = new DataSet(file->createDataSet(
      DATASET_NAME, PredType::NATIVE_INT, fspace, plist)
      );

    hsize_t start[2]; // Start of hyperslab
    hsize_t stride[2]; // Stride of hyperslab
    hsize_t count[2];  // Block count
    hsize_t block[2];  // Block sizes
    start[0]  = 0; start[1]  = 1;
    stride[0] = 4; stride[1] = 3;
    count[0]  = 2; count[1]  = 4;
    block[0]  = 3; block[1]  = 2;
    fspace.selectHyperslab( H5S_SELECT_SET, count, start, stride, block);

   
  }
  catch(FileIException error)
  {
    error.printError();
    return -1;
  }
  catch (DataSetIException error)
  {
    error.printError();
    return -1;
  }
  catch (DataSpaceIException error)
  {
    error.printError();
    return -1;
  }
  catch (DataTypeIException error)
  {
    error.printError();
    return -1;
  }

  return 1;  
}  

#endif