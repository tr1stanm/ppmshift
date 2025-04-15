#include "ppmshift.h"

int main(int argc, char ** argv) {
	if(argc < 2) {
		cout << "Command line args needed. Exiting program..." << endl;
		//list potential command line args here
		return 1;
	}

	if(strcmp(argv[1], "cleanup") == 0) {
		system("mogrify -format jpg -path ./saves *_*.ppm");
		system("rm *_*.ppm");
		return 0;
	}
	if(argc < 3) {
		cout << "More command line args needed. Input desired pixel shift effect, e.g. biwave, flip, sine, etc." << endl;
		cout << "Exiting program..." << endl;
		return 3;
	}

	shifts shifts;
	if(shifts.open(argc, argv)) return 4;
	
	//maybe think about doing this as a switch case?	
	for(int i = 2; i < argc; ++i) {
		shifts.shiftname = argv[i];
		cout << "shifting...";
		if(!strcmp(shifts.shiftname, "flip")) shifts.flip();
		if(!strcmp(shifts.shiftname, "biwave")) shifts.biwave();
		if(!strcmp(shifts.shiftname, "sine")) shifts.sine();
		if(!strcmp(shifts.shiftname, "colorswap")) shifts.colorswap();
		if(!strcmp(shifts.shiftname, "autosine")) shifts.autosine();
		if(!strcmp(shifts.shiftname, "sineanim")) shifts.sineanim();
		cout << "done!" << endl;
	}
	shifts.output();


	return 0;
}
