#include <stdlib.h>
#ifdef HAVE_HDF5
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
using namespace H5;
using namespace std;
namespace bf = boost::filesystem;

const H5std_string FILE_NAME("results/SDSextendible.h5");
const H5std_string	DATASET_NAME("ExtendibleIntArray");
const int	DIM0 = 10;
const int	DIM1 = 5;
const int RANK = 2;

int main(void)  
{  
  bf::path pdir("results");
  bf::create_directory(pdir);

  try
  {
    //try exception
    Exception::dontPrint();

    //create file by default
    H5File file(FILE_NAME, H5F_ACC_TRUNC);

    //define dataspace
    hsize_t dimsf[RANK] = {3, 3};
    hsize_t maxdims[RANK] = {H5S_UNLIMITED, H5S_UNLIMITED};
    DataSpace mspace1(RANK, dimsf, maxdims);

     /*
       * Modify dataset creation properties, i.e. enable chunking.
       */

    DSetCreatPropList cparms;
    hsize_t      chunk_dims[2] ={2, 5};
    cparms.setChunk( RANK, chunk_dims );

     /*
       * Set fill value for the dataset
       */
    int fill_val = 0;
    cparms.setFillValue( PredType::NATIVE_INT, &fill_val);

     /*
       * Create a new dataset within the file using cparms
       * creation properties.
       */
    DataSet dataset = file.createDataSet( DATASET_NAME, PredType::NATIVE_INT, mspace1, cparms);

    /*
       * Extend the dataset. This call assures that dataset is at least 3 x 3.
       */
    hsize_t      size[2];
    size[0]   = 3;
    size[1]   = 3;
    dataset.extend( size );

     /*
       * Select a hyperslab.
       */
    DataSpace fspace1 = dataset.getSpace ();
    hsize_t     offset[2];
    offset[0] = 0;
    offset[1] = 0;
    hsize_t      dims1[2] = { 3, 3};            /* data1 dimensions */
    fspace1.selectHyperslab( H5S_SELECT_SET, dims1, offset );

    /*
       * Write the data to the hyperslab.
       */
    int       data1[3][3] = { {1, 1, 1},       /* data to write */
                {1, 1, 1},
                {1, 1, 1} };
    dataset.write( data1, PredType::NATIVE_INT, mspace1, fspace1 );
      /*
       * Extend the dataset. Dataset becomes 10 x 3.
       */
    hsize_t   dims2[2] = { 7, 1};            /* data2 dimensions */
    dimsf[0]   = dims1[0] + dims2[0];
    size[0]   = dimsf[0];
    size[1]   = dimsf[1];
    dataset.extend( size );

    /*
       * Select a hyperslab.
       */
      DataSpace fspace2 = dataset.getSpace ();
      offset[0] = 3;
      offset[1] = 0;
      fspace2.selectHyperslab( H5S_SELECT_SET, dims2, offset );
      /*
       * Define memory space
       */
      DataSpace mspace2( RANK, dims2 );
      /*
       * Write the data to the hyperslab.
       */
      int  data2[7]    = { 2, 2, 2, 2, 2, 2, 2};
      dataset.write( data2, PredType::NATIVE_INT, mspace2, fspace2 );
      /*
       * Extend the dataset. Dataset becomes 10 x 5.
       */
      hsize_t   dims3[2] = { 2, 2};            /* data3 dimensions */
      dimsf[1]   = dims1[1] + dims3[1];
      size[0]   = dimsf[0];
      size[1]   = dimsf[1];
      dataset.extend( size );
      /*
       * Select a hyperslab
       */
      DataSpace fspace3 = dataset.getSpace ();
      offset[0] = 0;
      offset[1] = 3;
      fspace3.selectHyperslab( H5S_SELECT_SET, dims3, offset );
      /*
       * Define memory space.
       */
      DataSpace mspace3( RANK, dims3 );
      /*
       * Write the data to the hyperslab.
       */
      int         data3[2][2] = { {3, 3}, {3, 3} };
      dataset.write( data3, PredType::NATIVE_INT, mspace3, fspace3 );
      /*
       * Read the data from this dataset and display it.
       */
      int i, j;
      int data_out[DIM0][DIM1];
      for (i = 0; i < DIM0; i++)
      {
         for (j = 0; j < DIM1; j++)
            data_out[i][j] = 0;
      }
      dataset.read( data_out, PredType::NATIVE_INT );
      /*
       * Resulting dataset
       *
       *     1 1 1 3 3
       *     1 1 1 3 3
       *     1 1 1 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       *     2 0 0 0 0
       */
      /*
       * Display the result.
       */
      for (i=0; i < DIM0; i++)
      {
          for(j=0; j < DIM1; j++)
             cout << data_out[i][j] << "  ";
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