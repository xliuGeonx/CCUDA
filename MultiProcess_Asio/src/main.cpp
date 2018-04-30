#define _WIN32_WINNT 0x0A00
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;
namespace ba = boost::asio;


int main()  
{
	ba::io_service ios;
	vector<char> buf(10000,0);
	
	bp::child c("D:/xin00build/CCUDA/SimpleKernel/RelWithDebInfo/CCUDA_SimpleKernel.exe", bp::std_out > ba::buffer(buf), ios);
	cout << "before wait\n";
	//ios.run();
	//cout << &buf[0];
	
	c.wait();
	cout << "after wait\n";
	ios.run();
	cout << &buf[0];
	return 1;
};  