#include <stdlib.h>
#ifdef HAVE_HDF5
#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "H5Cpp.h"
using namespace H5;
using namespace std;
namespace bf = boost::filesystem;

const H5std_string FILE_NAME( "results/Group.h5" );
const int      RANK = 2;

// Operator function
extern "C" herr_t file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo,
    void *opdata);


int main(void)  
{  
  bf::path pdir("results");
  bf::create_directory(pdir);

  hsize_t  dims[2];
  hsize_t  cdims[2];


  try
  {
    /*
     * Create the named file, truncating the existing one if any,
     * using default create and access property lists.
     */
    H5File *file = new H5File( FILE_NAME, H5F_ACC_TRUNC );
    /*
     * Create a group in the file
     */
    Group* group = new Group( file->createGroup( "/Data" ));
    /*
     * Create dataset "Compressed Data" in the group using absolute
     * name. Dataset creation property list is modified to use
     * GZIP compression with the compression effort set to 6.
     * Note that compression can be used only when dataset is chunked.
     */
    dims[0] = 1000;
    dims[1] = 20;
    cdims[0] = 20;
    cdims[1] = 20;
    DataSpace *dataspace = new DataSpace(RANK, dims); // create new dspace
    DSetCreatPropList ds_creatplist;  // create dataset creation prop list
    ds_creatplist.setChunk( 2, cdims );  // then modify it for compression
    ds_creatplist.setDeflate( 6 );
    /*
     * Create the first dataset.
     */
    DataSet* dataset = new DataSet(file->createDataSet(
        "/Data/Compressed_Data", PredType::NATIVE_INT,
        *dataspace, ds_creatplist ));
    /*
     * Close the first dataset.
     */
    delete dataset;
    delete dataspace;
    /*
     * Create the second dataset.
     */
    dims[0] = 500;
    dims[1] = 20;
    dataspace = new DataSpace(RANK, dims); // create second dspace
    dataset = new DataSet(file->createDataSet("/Data/Float_Data",
            PredType::NATIVE_FLOAT, *dataspace));
    delete dataset;
    delete dataspace;
    delete group;
    delete file;
    /*
     * Now reopen the file and group in the file.
     */
    file = new H5File(FILE_NAME, H5F_ACC_RDWR);
    group = new Group(file->openGroup("Data"));

    /*
     * Access "Compressed_Data" dataset in the group.
     */
    try {  // to determine if the dataset exists in the group
        dataset = new DataSet( group->openDataSet( "Compressed_Data" ));
    }
    catch( GroupIException not_found_error ) {
        cout << " Dataset is not found." << endl;
    }
    cout << "dataset \"/Data/Compressed_Data\" is open" << endl;
    /*
     * Close the dataset.
     */
    delete dataset;
    /*
     * Create hard link to the Data group.
     */
    file->link( H5L_TYPE_HARD, "Data", "Data_new" );
    /*
     * We can access "Compressed_Data" dataset using created
     * hard link "Data_new".
     */
    try {  // to determine if the dataset exists in the file
        dataset = new DataSet(file->openDataSet( "/Data_new/Compressed_Data" ));
    }
    catch( FileIException not_found_error )
    {
        cout << " Dataset is not found." << endl;
    }
    cout << "dataset \"/Data_new/Compressed_Data\" is open" << endl;
    /*
     * Close the dataset.
     */
    delete dataset;
    /*
     * Use iterator to see the names of the objects in the file
     * root directory.
     */
    cout << endl << "Iterating over elements in the file" << endl;
    herr_t idx = H5Literate(file->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, file_info, NULL);
    cout << endl;
    /*
     * Unlink  name "Data" and use iterator to see the names
     * of the objects in the file root direvtory.
     */
    cout << "Unlinking..." << endl;
    try {  // attempt to unlink the dataset
        file->unlink( "Data" );
    }
    catch( FileIException unlink_error )
    {
        cout << " unlink failed." << endl;
    }
    cout << "\"Data\" is unlinked" << endl;
    cout << endl << "Iterating over elements in the file again" << endl;
    idx = H5Literate(file->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, file_info, NULL);
    cout << endl;
    /*
     * Close the group and file.
     */
    delete group;
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

  return 1;  
};

/*
 * Operator function.
 */
herr_t
file_info(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
{
    hid_t group;
    /*
     * Open the group using its name.
     */
    group = H5Gopen2(loc_id, name, H5P_DEFAULT);
    /*
     * Display group name.
     */
    cout << "Name : " << name << endl;
    H5Gclose(group);
    return 0;
};


#endif