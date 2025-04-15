uses imagemagick as a dependency to convert .ppm to .png when making animations. 
make sure you have imagemagick installed by running "brew install imagemagick" or a similar command depending on your OS.

program runs on the command line. navigate to the directory ppmshift is in and run "./ppmshift" followed by the name of the file you'd like to manipulate and any number of flags afterwards.

these flags are:

flip - flips the image horizontally and vertically

biwave - adds a blue, purple, and pink filter over your image

sine - prompts user for amplitude and wavelength of sinewave and applies it horizontally to the image

autosine - assigns a random value to each of the above variables and runs the program

sineanim - prompts user for number of frames to animate and applies a sine function to the image for that number of frames. outputs each resulting frame with name and number (in .png format to save space) in source folder. frames can be stitched together into an animation using quicktime or similar software.

multiple flags can be used in the same program call. for example
>./ppmshift myphoto.ppm colorswap biwave biwave colorswap flip sine

this file is then output into the source folder with the name myphoto_cbbcfs.ppm.
