#include "ppmshift.h"

void shifts::flip() {
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < pixwidth; ++j) {
			pixout[j][i].red = pixin[(pixwidth-j)-1][(height-i)-1].red;
			pixout[j][i].green = pixin[(pixwidth-j)-1][(height-i)-1].green;
			pixout[j][i].blue = pixin[(pixwidth-j)-1][(height-i)-1].blue;
		}
	}
	remap();
}

void shifts::biwave() {
	char c;
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < pixwidth; ++j) {
			pixout[j][i].blue = pixin[j][i].blue + 40;
			pixout[j][i].green = pixin[j][i].green;
			pixout[j][i].red = pixin[j][i].red + counter/(pixwidth*3);
			++counter;
		}
	}
	counter = 0;
	remap();
}

void shifts::colorswap() {
	for(int i = 0; i < height; ++i) {
		for(int j = 0; j < pixwidth; ++j) {
			pixout[j][i].green = pixin[j][i].green;
			pixout[j][i].blue = pixin[j][i].red;
			pixout[j][i].red = pixin[j][i].blue;
		}
	}
	remap();
}

void shifts::sine() {
	int sinsize, wavelength;
	/*
	do {
	*/
		cout << "shift by how much? (" << -pixwidth << " - " << pixwidth << "): ";
		cin >> sinsize;
		cin.ignore();
		/*
		if(sinsize > pixwidth || sinsize < -pixwidth) {
			cout << "shift must occur between -" << pixwidth << " and " << pixwidth << ". enter a valid number. " << endl;
		}
	} while(sinsize > pixwidth || sinsize < -pixwidth);
	*/
	cout << "what should the wavelength of the sine wave be? ";
	cin >> wavelength;
	cin.ignore();
	sine(sinsize, wavelength);
}

void shifts::sine(int size, int wavel) {
	double ideg, offset;
	int offset_width = pixwidth;
	for(int i = 0; i < height; ++i) {
		ideg = i*3.14159/wavel;
		if(size > pixwidth) {
			size -= pixwidth + pixwidth*(size/pixwidth);
			//is there a better way to do this?
		}
		offset = (size*sin(ideg));
		offset_width -= offset;
		if(offset < 0) offset_width -= pixwidth;	
		for(int o = offset_width; o < pixwidth; ++o) {
			pixout[counter][i].red = pixin[o][i].red;
			pixout[counter][i].green = pixin[o][i].green;
			pixout[counter][i].blue = pixin[o][i].blue;
			++counter;

		}
		for(int j = 0; j < offset_width; ++j) {
			pixout[counter][i].red = pixin[j][i].red;
			pixout[counter][i].green = pixin[j][i].green;
			pixout[counter][i].blue = pixin[j][i].blue;
			++counter;
		}

		offset_width = pixwidth;
		counter = 0;
	}
	remap();
}


void shifts::autosine() {
	srand(time(nullptr));
	sine((rand() % pixwidth*2) - pixwidth, (rand() % pixwidth) * 5);
	remap();
}

void shifts::sineanim() {
	stringstream framename;
	stringstream syscall;
	int frames;
	float progress;
	int sizelower, sizeupper;
	int wavelower, waveupper;
	cout << "how many frames? ";
	cin >> frames;
	cin.ignore();

	syscall << "mkdir " << filename_char << "_anim";
	system(syscall.str().c_str());
	syscall.str("");
	syscall << "cd " << filename_char << "_anim";
	system(syscall.str().c_str());
	syscall.str("");
	
	for(int i = 0; i < frames; ++i) {
		progress = 100*((i+1)/(float)frames);
		framename << "./" << filename_char << "_anim/" <<\
			     filename_char << "_frame" << i << ".ppm";
		sine(i, 20+i);
		fileout.open(framename.str(), fstream::out);
		output();
		fileout.close();

		syscall << "magick " << framename.str() << " " <<\
			   filename_char << "_anim/" << filename_char <<\
			   "_frame" << i << ".png";
		system(syscall.str().c_str());
		syscall.str("");
		syscall << "rm " << framename.str();
		system(syscall.str().c_str());
		syscall.str("");

		framename.str("");
		cout << "\rgenerating frames... ";
		printf("%.1f", progress); 
		cout << "\% done." << flush;
	}
	cout << "\rgenerating frames... 100\% done.    " << endl;
}
