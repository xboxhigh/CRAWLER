#include <iostream>

using namespace std;

int arrayTest(char &_str[10])
{
	_str[0] = "AAAAAAAAAAAAAAA";
	return 0;
}

int main()
{
	char *str[10];
	char *str1;
	
	
	
	arrayTest(&str);
	
	cout << str[0] << endl;
	
	
	
	
	
	return 0;
}
