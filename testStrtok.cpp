

#include <dirent.h>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
	string delimet = "<00>";
  char str[] ="pppppppK <00> - This, a sample string.";
  
  char * pch;
  //printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str, delimet.c_str());
  
  //cout << pch << endl;
  
  while (pch != NULL)
  {
    //printf ("%s\n",pch);
    cout << "_" << pch << "_" << endl;
    pch = strtok (NULL, delimet.c_str());
  }
  return 0;
}
