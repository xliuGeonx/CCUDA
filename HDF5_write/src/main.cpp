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

    hsize_t dim1[] = {MSPACE1_DIM};
    DataSpace mspace1(MSPACE1_RANK,dim1);
    start[0]  = 1;
    stride[0] = 1;
    count[0]  = 48;
    block[0]  = 1;
    mspace1.selectHyperslab( H5S_SELECT_SET, count, start, stride, block);

    int    vector[MSPACE1_DIM]; // vector buffer for dset
    /*
     * Buffer initialization.
     */
    vector[0] = vector[MSPACE1_DIM - 1] = -1;
    for (i = 1; i < MSPACE1_DIM - 1; i++)
        vector[i] = i;
    /*
     * Write selection from the vector buffer to the dataset in the file.
     *
     * File dataset should look like this:
     *                    0  1  2  0  3  4  0  5  6  0  7  8
     *                    0  9 10  0 11 12  0 13 14  0 15 16
     *                    0 17 18  0 19 20  0 21 22  0 23 24
     *                    0  0  0  0  0  0  0  0  0  0  0  0
     *                    0 25 26  0 27 28  0 29 30  0 31 32
     *                    0 33 34  0 35 36  0 37 38  0 39 40
     *                    0 41 42  0 43 44  0 45 46  0 47 48
     *                    0  0  0  0  0  0  0  0  0  0  0  0
     */
    dataset->write( vector, PredType::NATIVE_INT, mspace1, fspace );
    //reset fspace selection
    fspace.selectNone();
    /*
     * Create dataspace for the second dataset.
     */
    hsize_t dim2[] = {MSPACE2_DIM};  /* Dimension size of the second dataset
                                       (in memory */
    DataSpace mspace2( MSPACE2_RANK, dim2 );

    hsize_t coord[NPOINTS][FSPACE_RANK]; /* Array to store selected points
                                            from the file dataspace */
    coord[0][0] = 0; coord[0][1] = 0;
    coord[1][0] = 3; coord[1][1] = 3;
    coord[2][0] = 3; coord[2][1] = 5;
    coord[3][0] = 5; coord[3][1] = 6;
    fspace.selectElements( H5S_SELECT_SET, NPOINTS, (const hsize_t *)coord);
    /*
     * Write new selection of points to the dataset.
     */
    int    values[] = {53, 59, 61, 67};  /* New values to be written */
    dataset->write( values, PredType::NATIVE_INT, mspace2, fspace );
    /*
     * File dataset should look like this:
     *                   53  1  2  0  3  4  0  5  6  0  7  8
     *                    0  9 10  0 11 12  0 13 14  0 15 16
     *                    0 17 18  0 19 20  0 21 22  0 23 24
     *                    0  0  0 59  0 61  0  0  0  0  0  0
     *                    0 25 26  0 27 28  0 29 30  0 31 32
     *                    0 33 34  0 35 36 67 37 38  0 39 40
     *                    0 41 42  0 43 44  0 45 46  0 47 48
     *                    0  0  0  0  0  0  0  0  0  0  0  0
     *
     */
     delete dataset;
     delete file;

     file = NULL;
     file = new H5File(FILE_NAME, H5F_ACC_RDONLY);

     dataset = NULL;
     dataset = new DataSet(file->openDataSet(DATASET_NAME));
     fspace = dataset->getSpace();

     /*
     * Select first hyperslab for the dataset in the file. The following
     * elements are selected:
     *                     10  0 11 12
     *                     18  0 19 20
     *                      0 59  0 61
     *
     */
    start[0] = 1; start[1] = 2;
    block[0] = 1; block[1] = 1;
    stride[0] = 1; stride[1] = 1;
    count[0]  = 3; count[1]  = 4;
    fspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
    /*
     * Add second selected hyperslab to the selection.
     * The following elements are selected:
     *                    19 20  0 21 22
     *                     0 61  0  0  0
     *                    27 28  0 29 30
     *                    35 36 67 37 38
     *                    43 44  0 45 46
     *                     0  0  0  0  0
     * Note that two hyperslabs overlap. Common elements are:
     *                                              19 20
     *                                               0 61
     */
    start[0] = 2; start[1] = 4;
    block[0] = 1; block[1] = 1;
    stride[0] = 1; stride[1] = 1;
    count[0]  = 6; count[1]  = 5;
    fspace.selectHyperslab(H5S_SELECT_OR, count, start, stride, block);
    /*
     * Create memory dataspace.
     */
    hsize_t mdim[] = {MSPACE_DIM1+1, MSPACE_DIM2+1}; /* Dimension sizes of the
                                                   dataset in memory when we
                                                   read selection from the
                                                   dataset on the disk */
    DataSpace mspace(MSPACE_RANK, mdim);
    /*
     * Select two hyperslabs in memory. Hyperslabs has the same
     * size and shape as the selected hyperslabs for the file dataspace.
     */
    start[0] = 0; start[1] = 0;
    block[0] = 1; block[1] = 1;
    stride[0] = 1; stride[1] = 1;
    count[0]  = 3; count[1]  = 4;
    mspace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
    start[0] = 2; start[1] = 0;
    block[0] = 1; block[1] = 1;
    stride[0] = 1; stride[1] = 1;
    count[0]  = 6; count[1]  = 5;
    mspace.selectHyperslab(H5S_SELECT_OR, count, start, stride, block);
    /*
     * Initialize data buffer.
     */
    int matrix_out[MSPACE_DIM1+1][MSPACE_DIM2+1];
    for (i = 0; i < MSPACE_DIM1+1; i++)
        for (j = 0; j < MSPACE_DIM2+1; j++)
        matrix_out[i][j] = 0;
    /*
     * Read data back to the buffer matrix.
     */
    dataset->read(matrix_out, PredType::NATIVE_INT, mspace, fspace);
    /*
     * Display the result.  Memory dataset is:
     *
     *                    10  0 11 12  0  0  0  0  0
     *                    18  0 19 20  0 21 22  0  0
     *                     0 59  0 61  0  0  0  0  0
     *                     0  0 27 28  0 29 30  0  0
     *                     0  0 35 36 67 37 38  0  0
     *                     0  0 43 44  0 45 46  0  0
     *                     0  0  0  0  0  0  0  0  0
     *                     0  0  0  0  0  0  0  0  0
     */
    for (i=0; i < MSPACE_DIM1+1; i++)
    {
        for(j=0; j < MSPACE_DIM2+1; j++)
        cout << matrix_out[i][j] << "  ";
        cout << endl;
    }
    /*
     * Close the dataset and the file.
     */
    delete dataset;
    delete file;
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

  //return 1;  
}  

#endif