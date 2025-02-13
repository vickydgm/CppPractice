// string::reserve
#include <iostream>
#include <fstream>
#include <string>

int main ()
{
   std::string str;
   
   std::ifstream file ("string.cc",std::ios::in|std::ios::ate);
   if (file) 
   {
   	std::ifstream::streampos filesize = file.tellg();
   	str.reserve(filesize);
   
   	file.seekg(0);
   	while (!file.eof())
   	{
   		str += file.get();
   	}
   	std::cout << str;
   }
   return 0;
}
