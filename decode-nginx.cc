#include "decode-nginx.h"

using namespace std;  

int main(int argc, char *argv[])
{  
	if(argc < 2)
	{
		cout << "./decode-nginx infile outfile" << endl;
		return -1;
	}

	ifstream infile (argv[1]);  
	ofstream outfile(argv[2]);  

	if(!infile){  
		cout << "Unable to open infile";  
		return -1;
	}  
	if(!outfile){  
		cout << "Unable to open outfile";  
		return -1;
	}  

	int i=1;
	int b64resnum = 0;
	char * start = NULL;
	char * paend = NULL;
	char * end = NULL;
	
	char buffer[2048];  
	char realstr[2048]; 
	
	while( infile.getline(buffer, 2048) )
	{    
		start = NULL;
		paend = NULL;
		end = NULL;
		b64resnum = 0;

		//cout << "Read from file: " << buffer << endl;
		if((start = strstr(buffer, "index.cgi?*")) != NULL)
		{
			paend = start;
			start += 10;
			paend[9] = '\0';
			if((paend = strstr(start, "\"")) != NULL)
			{
				end = paend+1;
				paend[0] = '\0';
			}

			if(start[0] == '*' && end != NULL)
			{
				Decrypt(start+1,5);
				char realstr[1024] = {0};
				int b64resnum = 0;
				if(base64_decode((unsigned char *)(start+1), strlen(start+1), (unsigned char *)realstr, &b64resnum) != NULL)
				{
					//cout << "START:   " << buffer << endl;
					//cout << "VALUE:   " << realstr << endl;
					//cout << "END:     " << end << endl;

					outfile << buffer << '?' << realstr << '"' << end << endl;
				}
			}

			//return -1;
			i++;
			memset(buffer, 0, 2048);
			continue;
		}
		else
		{
			outfile << buffer << endl;
			i++;
			memset(buffer, 0, 2048);
		}
	}

	infile.close();  
	outfile.close();  

	return 0;  
}  
