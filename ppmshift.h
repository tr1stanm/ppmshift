#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

struct pixel {
	char red;
	char green;
	char blue;
};

class shifts {
	public:
		char *shiftname;
		
		shifts();
		~shifts();
		int open(int, char**);	//passes in argc and argv
		void biwave();
		void pixelmap();
		void flip();
		void sine();
		void colorswap();
		void autosine();
		void sineanim();
		void output();		//outputs pixout
	private:
		stringstream filename;
		void remap();
		void sine(int, int);
		bool isanim(char*);
		
		char *tagname, magicno[8], filename_char[256];
		pixel **pixin, **pixout;
		ifstream loadfile;
		fstream fileout;
		int width, pixwidth, height;
		unsigned int counter;
};
