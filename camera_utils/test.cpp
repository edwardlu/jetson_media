#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::string get_name()
{
	return "helloworld";
}

int main()
{
	std::string str ; 
	str= get_name();
	cout<<str<<endl;
	std::vector<int> array;
	array.reserve(128);

	cout<<array.size()<<endl;
	return 0;
}
