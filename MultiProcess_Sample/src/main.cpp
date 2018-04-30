#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;

int main()  
{
	int i = 0;
	boost::filesystem::path p("D:/xin00build/CCUDA/SimpleKernel/RelWithDebInfo/CCUDA_SimpleKernel.exe");
	//bp::child c(p.string());

	bp::child c(bp::search_path("gcc"), "--version");
	
	cout << ++i << endl;
	cout << "main process no wait" << endl;
	c.wait();
	
	cout << "main process" << endl;
	bp::ipstream is;
	bp::child c1("gcc --version", bp::std_out > is);
	string line;
	while (is && getline(is, line) && !line.empty())
		cout << line << endl;
	c1.wait();

	bp::child c2("gcc --version", bp::std_out > "gcc-log.log");
	c2.wait();

	int result = c.exit_code();
	return 1;
};  