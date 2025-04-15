#include "ppmshift.h"

shifts::shifts(){
	width = 0;
	height = 0;
	counter = 0;
}

int shifts::open(int argc, char **argv) {
	char currentline[256];
	char dimensions[256];
	int i = 0;
	
	tagname = new char[--argc];
	for(int i = 0; i < argc-1; ++i) tagname[i] = argv[i+2][0];
	strcpy(filename_char, argv[1]);
	
	loadfile.open(filename_char);
	if(!loadfile) {
		cout << "No such file with the name \"" << filename_char << "\" was found." << endl;
		return 1;
	}
	loadfile.getline(magicno, 8);
	loadfile.seekg(0);
	
	cout << "File " << filename_char << " successfully opened." << endl;
	cout << "magicno: " << magicno << endl;
	for(int i = strlen(filename_char)-4; i < strlen(filename_char); ++i) filename_char[i] = '\0';
	filename << "./" << filename_char;
	filename << "_" << tagname << ".ppm";

	if(!(isanim(argv[2]))) fileout.open(filename.str(), fstream::out);
	//lots of double negation here
	while(strcmp(currentline, "255") != 0) {
		strcpy(dimensions, currentline);				//ensures that the dimensions of the file will be stored properly in that they are always in the line above the max brightness line.
		loadfile.getline(currentline, 256);
	}
	
	for(; dimensions[i] != ' '; ++i) {
		width *= 10;
		width += dimensions[i] - 48;
		dimensions[i] = 0;
	}
	cout << "width: " << width << endl;
	++i;
	for(; dimensions[i] != '\0'; ++i) {
		height *= 10;
		height += dimensions[i] - 48;
	}
	cout << "height: " << height << endl;
	pixwidth = width;
	width *= 3;	//since there are 3 chars per pixel
	pixelmap();
	return 0;
}

void shifts::pixelmap() {	//consider redef width var
	int count = 0;
	pixin = new pixel*[pixwidth];
	pixout = new pixel*[pixwidth];
	for(int i = 0; i < pixwidth; ++i) {
		pixin[i] = new pixel[height];
		pixout[i] = new pixel[height];
	}
	for(int j = 0; j < height; ++j) {
		for(int i = 0; i < pixwidth; ++i) {
			loadfile.get(pixin[i][j].red);
			loadfile.get(pixin[i][j].green);
			loadfile.get(pixin[i][j].blue);
			cout << "pixel " << count++ <<\
				" out of " << (pixwidth*height) << " mapped.\r";
		}
	}
	cout << "pixel " << count++ << " out of " << (pixwidth*height) << " mapped." << endl;
	cout << "done!" << endl;

}

void shifts::remap() {
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < pixwidth; ++j) {
			pixin[j][i].red = pixout[j][i].red;
			pixin[j][i].green = pixout[j][i].green;
			pixin[j][i].blue = pixout[j][i].blue;
		}
	}
}

void shifts::output() {
	fileout << magicno << endl;
	fileout << pixwidth << " " << height << endl;
	fileout << "255" << endl;
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < pixwidth; ++j) {
			fileout << pixout[j][i].red;
			fileout << pixout[j][i].green;
			fileout << pixout[j][i].blue;
		}
	}
}

bool shifts::isanim(char *arg) {
	if(!(strcmp(arg, "sineanim"))) return true;
	return false;
}

shifts::~shifts(){
	for(int i = 0; i < pixwidth; ++i) {
		delete[] pixin[i];
		delete[] pixout[i];
	}
	delete[] pixin;
	delete[] pixout;
	delete[] tagname;
	
	fileout.close();
	loadfile.close();
}
