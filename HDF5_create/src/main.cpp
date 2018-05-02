#include <stdlib.h>
#ifdef HAVE_HDF5
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
using namespace H5;
using namespace std;
namespace bf = boost::filesystem;

const H5std_string FILE_NAME("results/SDS.h5");
const H5std_string	DATASET_NAME("IntArray");
const int	DIM0 = 5;
const int	DIM1 = 6;
const int RANK = 2;

int main(void)  
{  
  bf::path pdir("results");
  bf::create_directory(pdir);

  int data[DIM0][DIM1];
  //data initialize
  for (int j=0; j<DIM0; ++j)
    for (int i=0; i<DIM1; ++i)
    {
      data[j][i] = i+j;
    }

  try
  {
    //try exception
    Exception::dontPrint();

    //create file by default
    H5File file(FILE_NAME, H5F_ACC_TRUNC);

    //define dataspace
    hsize_t dimsf[RANK];
    dimsf[0]=DIM0;
    dimsf[1]=DIM1;
    DataSpace dataspace(RANK, dimsf);

    //define datatype
    IntType datatype(PredType::NATIVE_INT);
    datatype.setOrder(H5T_ORDER_LE);

    //define dataset
    DataSet dataset = file.createDataSet(DATASET_NAME, datatype, dataspace);

    //write data to dataset
    dataset.write(data, PredType::NATIVE_INT);
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