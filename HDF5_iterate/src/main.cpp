/************************************************************

  This example shows how to iterate over group members using
  H5Literate.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include "hdf5.h"
#include <stdio.h>
#include "H5cpp.h"
using namespace H5;

#define FILE_NAME       "Group.h5"

/*
 * Operator function to be called by H5Literate.
 */
herr_t op_func (hid_t loc_id, const char *name, const H5L_info_t *info,
            void *operator_data);

int
main (void)
{
    //hid_t           file;           /* Handle */
    herr_t          status;

    /*
     * Open file.
     */
    H5File* file = new H5File(FILE_NAME, H5F_ACC_RDWR);
    Group* group = new Group(file->openGroup("Data_new"));
    /*
     * Begin iteration.
     */
    printf ("Objects in root group:\n");
    status = H5Literate (group->getId(), H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, NULL);

    /*
     * Close and release resources.
     */
    file->close();

    return 0;
}


/************************************************************

  Operator function.  Prints the name and type of the object
  being examined.

 ************************************************************/
herr_t op_func (hid_t loc_id, const char *name, const H5L_info_t *info,
            void *operator_data)
{
    herr_t          status;
    H5O_info_t      infobuf;

    /*
     * Get type of the object and display its name and type.
     * The name of the object is passed to this function by
     * the Library.
     */
    status = H5Oget_info_by_name (loc_id, name, &infobuf, H5P_DEFAULT);
    switch (infobuf.type) {
        case H5O_TYPE_GROUP:
            printf ("  Group: %s\n", name);
            break;
        case H5O_TYPE_DATASET:
            printf ("  Dataset: %s\n", name);
            break;
        case H5O_TYPE_NAMED_DATATYPE:
            printf ("  Datatype: %s\n", name);
            break;
        default:
            printf ( "  Unknown: %s\n", name);
    }

    return 0;
}