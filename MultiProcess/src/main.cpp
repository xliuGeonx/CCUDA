#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;

bp::child start_child(bp::ipstream& is)
{
	string ss("gcc --version");
	return bp::child(ss, bp::std_out > is);
};

int main()  
{
	bp::ipstream is;
	bp::child c = start_child(is);
	
	string line;

	while (is && getline(is, line) && !line.empty())
		cout << line << endl;
	c.wait();
	return 1;
};  