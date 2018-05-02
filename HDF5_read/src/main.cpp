#include <stdlib.h>
#ifdef HAVE_HDF5
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
using namespace H5;
using namespace std;
namespace bf = boost::filesystem;

const H5std_string FILE_NAME("SDS.h5");
const H5std_string	DATASET_NAME("IntArray");

const int NX_SUB = 3;
const int NY_SUB = 4;
const int NX = 7;
const int NY = 7;
const int NZ = 3;
const int RANK_OUT = 3;

int main(void)  
{  
  bf::path pdir("results");
  bf::create_directory(pdir);

  int data_out[NX][NY][NZ];
  //data initialize
  for(int k=0; k<NZ; ++k)
    for (int j=0; j<NY; ++j)
      for (int i=0; i<NX; ++i)
      {
        data_out[i][j][k] = 0;
      }

  try
  {
    //try exception
    Exception::dontPrint();

    //create file by default
    H5File file(FILE_NAME, H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet(DATASET_NAME);

    H5T_class_t type_class = dataset.getTypeClass();

    if ( type_class == H5T_INTEGER)
    {
      cout << "Dataset has INTEGER type\n";
      IntType inttype = dataset.getIntType();

      H5std_string order_string;
      inttype.getOrder(order_string);
      cout << order_string << endl;

      size_t size = inttype.getSize();
      cout << "Data size is " << size << endl;
    }

    DataSpace dataspace = dataset.getSpace();
    int rank = dataspace.getSimpleExtentNdims();

    hsize_t dims_out[2];
    int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
    cout << "rank " << rank << ", dimensions " <<
          (unsigned long)(dims_out[0]) << " x " <<
          (unsigned long)(dims_out[1]) << endl;

    hsize_t offset[2];
    hsize_t count[2];
    offset[0] = 1;
    offset[1] = 2;
    count[0] = NX_SUB;
    count[1] = NY_SUB;
    dataspace.selectHyperslab(H5S_SELECT_SET, count, offset);

    hsize_t dimsm[3];
    dimsm[0]=NX;
    dimsm[1]=NY;
    dimsm[2]=NZ;
    DataSpace memspace(RANK_OUT, dimsm);

     hsize_t      offset_out[3];   // hyperslab offset in memory
     hsize_t      count_out[3];    // size of the hyperslab in memory
     offset_out[0] = 3;
     offset_out[1] = 0;
     offset_out[2] = 0;
     count_out[0]  = NX_SUB;
     count_out[1]  = NY_SUB;
     count_out[2]  = 1;
     memspace.selectHyperslab( H5S_SELECT_SET, count_out, offset_out );

     dataset.read(data_out, PredType::NATIVE_INT, memspace, dataspace);

      for (int j = 0; j < NX; j++)
      {
        for (int i = 0; i < NY; i++)
          cout << data_out[j][i][0] << " ";
        cout << endl;
      }
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