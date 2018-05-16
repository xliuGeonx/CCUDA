/************************************************************

  This example shows how to iterate over group members using
  H5Literate.

  This file is intended for use with HDF5 Library version 1.8

 ************************************************************/

#include "hdf5.h"
#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <string>
#include "H5cpp.h"
#include "boost/function.hpp"
#include "boost/bind.hpp"

using namespace std;
using namespace H5;

typedef std::map<std::string, std::set<std::string> > h5_tree_type;

typedef struct H5ImportInfoType
{
  string _fn;
  //set<string> _groups;
  h5_tree_type _tree;

  const string& get_fn() {return _fn;};
  //const set<string>& get_groups() {return _groups;};
  const h5_tree_type& get_tree() {return _tree;};

  void print() const 
  {
    cout << "**************************************************************" << endl;
    cout << "The structure of file: " << _fn << " is:\n";
    h5_tree_type::const_iterator iter_g = _tree.begin();
    for (; iter_g!=_tree.end(); ++iter_g)
    {
      cout << "   Group: " << iter_g->first << endl;
      set<string>::const_iterator iter_s = iter_g->second.begin();
      for (; iter_s != iter_g->second.end(); ++iter_s)
      {
        cout << "     Dataset: " << *iter_s << endl;
      }
    }
    cout << "**************************************************************" << endl;
  };

}h5_import_info_type;

#define FILE_NAME       "Group.h5"

static h5_import_info_type file_data = h5_import_info_type();
/*
 * Operator function to be called by H5Literate.
 */
herr_t op_func (hid_t loc_id, const char *name, const H5L_info_t *info,
            void *operator_data);
/*
typedef boost::function<herr_t (hid_t loc_id, const char *name, const H5L_info_t *info,
            void *operator_data)>                             h5_op_type;

void h5_group_iterator(const std::string& group_name, const H5File* file)
{  
  herr_t          status;
  //string temp_nm(group_name);
  //h5_tree.insert(std::pair<string, set<string> >(temp_nm, set<string>()));
  h5_op_type op_func = boost::bind(op_funcs, group_name);
  Group* group = new Group(file->openGroup(group_name));
  status = H5Literate (group->getId(), H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, NULL);
};
*/

int main (void)
{
    //hid_t           file;           /* Handle */
    herr_t          status;

    /*
     * Open file.
     */
    file_data._fn.assign(FILE_NAME);
    H5File* file = new H5File(FILE_NAME, H5F_ACC_RDONLY);
    Group* group = new Group(file->openGroup("Data22"));
    /*
     * Begin iteration.
     */
    printf ("Objects in root group:\n");
    status = H5Literate (file->getId(), H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, NULL);

    file_data.print();
    /*
     * Close and release resources.
     */
    file->close();
    delete group;
    delete file;
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

    size_t len = H5Iget_name(loc_id, NULL, 0);
    char* buffer = new char[len];
    H5Iget_name(loc_id,buffer,len+1);
    std::string nn = buffer;
    nn.erase(0,1);
    delete[] buffer;
    cout << "src name is " << nn << endl;

    H5::H5File file;    
    H5::Group group;
    /*
     * Get type of the object and display its name and type.
     * The name of the object is passed to this function by
     * the Library.
     */
    status = H5Oget_info_by_name (loc_id, name, &infobuf, H5P_DEFAULT);
    switch (infobuf.type) {
        case H5O_TYPE_GROUP:
            printf ("  Group: %s\n", name);
            file = H5File(file_data.get_fn(), H5F_ACC_RDONLY);
            file_data._tree.insert(std::pair<string, set<string> >(name, set<string>()));
            group = H5::Group(file.openGroup(name));
            cout << "id: " << loc_id << endl;
            cout << "group id: " << group.getId() << endl;
            H5Literate (group.getId(), H5_INDEX_NAME, H5_ITER_NATIVE, NULL, op_func, NULL);
            break;
        case H5O_TYPE_DATASET:
            printf ("  Dataset: %s\n", name);  
            file_data._tree.find(nn)->second.insert(name);
            break;
        case H5O_TYPE_NAMED_DATATYPE:
            printf ("  Datatype: %s\n", name);
            break;
        default:
            printf ( "  Unknown: %s\n", name);
    }

    return 0;
}