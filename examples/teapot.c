
#include <stdio.h>
#include "vogle.h"

/*
 *	Draws Newell's Teapot as a heap of Bezier surface patches.
 */


#define	TEAPOT		1
#define	ESC		27

/*
 *	Data for the teapot.
 */
#define	NUM_PNTS	306
#define	NUM_PATCH	32 

float	xyz[NUM_PNTS][3] = {
	{ 1.400,   0.000,   2.400},
	{ 1.400,  -0.784,   2.400},
	{ 0.784,  -1.400,   2.400},
	{ 0.000,  -1.400,   2.400},
	{ 1.337,   0.000,   2.531},
	{ 1.337,  -0.749,   2.531},
	{ 0.749,  -1.337,   2.531},
	{ 0.000,  -1.337,   2.531},
	{ 1.438,   0.000,   2.531},
	{ 1.438,  -0.805,   2.531},
	{ 0.805,  -1.438,   2.531},
	{ 0.000,  -1.438,   2.531},
	{ 1.500,   0.000,   2.400},
	{ 1.500,  -0.840,   2.400},
	{ 0.840,  -1.500,   2.400},
	{ 0.000,  -1.500,   2.400},
	{-0.784,  -1.400,   2.400},
	{-1.400,  -0.784,   2.400},
	{-1.400,   0.000,   2.400},
	{-0.749,  -1.337,   2.531},
	{-1.337,  -0.749,   2.531},
	{-1.337,   0.000,   2.531},
	{-0.805,  -1.438,   2.531},
	{-1.438,  -0.805,   2.531},
	{-1.438,   0.000,   2.531},
	{-0.840,  -1.500,   2.400},
	{-1.500,  -0.840,   2.400},
	{-1.500,   0.000,   2.400},
	{-1.400,   0.784,   2.400},
	{-0.784,   1.400,   2.400},
	{ 0.000,   1.400,   2.400},
	{-1.337,   0.749,   2.531},
	{-0.749,   1.337,   2.531},
	{ 0.000,   1.337,   2.531},
	{-1.438,   0.805,   2.531},
	{-0.805,   1.438,   2.531},
	{ 0.000,   1.438,   2.531},
	{-1.500,   0.840,   2.400},
	{-0.840,   1.500,   2.400},
	{ 0.000,   1.500,   2.400},
	{ 0.784,   1.400,   2.400},
	{ 1.400,   0.784,   2.400},
	{ 0.749,   1.337,   2.531},
	{ 1.337,   0.749,   2.531},
	{ 0.805,   1.438,   2.531},
	{ 1.438,   0.805,   2.531},
	{ 0.840,   1.500,   2.400},
	{ 1.500,   0.840,   2.400},
	{ 1.750,   0.000,   1.875},
	{ 1.750,  -0.980,   1.875},
	{ 0.980,  -1.750,   1.875},
	{ 0.000,  -1.750,   1.875},
	{ 2.000,   0.000,   1.350},
	{ 2.000,  -1.120,   1.350},
	{ 1.120,  -2.000,   1.350},
	{ 0.000,  -2.000,   1.350},
	{ 2.000,   0.000,   0.900},
	{ 2.000,  -1.120,   0.900},
	{ 1.120,  -2.000,   0.900},
	{ 0.000,  -2.000,   0.900},
	{-0.980,  -1.750,   1.875},
	{-1.750,  -0.980,   1.875},
	{-1.750,   0.000,   1.875},
	{-1.120,  -2.000,   1.350},
	{-2.000,  -1.120,   1.350},
	{-2.000,   0.000,   1.350},
	{-1.120,  -2.000,   0.900},
	{-2.000,  -1.120,   0.900},
	{-2.000,   0.000,   0.900},
	{-1.750,   0.980,   1.875},
	{-0.980,   1.750,   1.875},
	{ 0.000,   1.750,   1.875},
	{-2.000,   1.120,   1.350},
	{-1.120,   2.000,   1.350},
	{ 0.000,   2.000,   1.350},
	{-2.000,   1.120,   0.900},
	{-1.120,   2.000,   0.900},
	{ 0.000,   2.000,   0.900},
	{ 0.980,   1.750,   1.875},
	{ 1.750,   0.980,   1.875},
	{ 1.120,   2.000,   1.350},
	{ 2.000,   1.120,   1.350},
	{ 1.120,   2.000,   0.900},
	{ 2.000,   1.120,   0.900},
	{ 2.000,   0.000,   0.450},
	{ 2.000,  -1.120,   0.450},
	{ 1.120,  -2.000,   0.450},
	{ 0.000,  -2.000,   0.450},
	{ 1.500,   0.000,   0.225},
	{ 1.500,  -0.840,   0.225},
	{ 0.840,  -1.500,   0.225},
	{ 0.000,  -1.500,   0.225},
	{ 1.500,   0.000,   0.150},
	{ 1.500,  -0.840,   0.150},
	{ 0.840,  -1.500,   0.150},
	{ 0.000,  -1.500,   0.150},
	{-1.120,  -2.000,   0.450},
	{-2.000,  -1.120,   0.450},
	{-2.000,   0.000,   0.450},
	{-0.840,  -1.500,   0.225},
	{-1.500,  -0.840,   0.225},
	{-1.500,   0.000,   0.225},
	{-0.840,  -1.500,   0.150},
	{-1.500,  -0.840,   0.150},
	{-1.500,   0.000,   0.150},
	{-2.000,   1.120,   0.450},
	{-1.120,   2.000,   0.450},
	{ 0.000,   2.000,   0.450},
	{-1.500,   0.840,   0.225},
	{-0.840,   1.500,   0.225},
	{ 0.000,   1.500,   0.225},
	{-1.500,   0.840,   0.150},
	{-0.840,   1.500,   0.150},
	{ 0.000,   1.500,   0.150},
	{ 1.120,   2.000,   0.450},
	{ 2.000,   1.120,   0.450},
	{ 0.840,   1.500,   0.225},
	{ 1.500,   0.840,   0.225},
	{ 0.840,   1.500,   0.150},
	{ 1.500,   0.840,   0.150},
	{-1.600,   0.000,   2.025},
	{-1.600,  -0.300,   2.025},
	{-1.500,  -0.300,   2.250},
	{-1.500,   0.000,   2.250},
	{-2.300,   0.000,   2.025},
	{-2.300,  -0.300,   2.025},
	{-2.500,  -0.300,   2.250},
	{-2.500,   0.000,   2.250},
	{-2.700,   0.000,   2.025},
	{-2.700,  -0.300,   2.025},
	{-3.000,  -0.300,   2.250},
	{-3.000,   0.000,   2.250},
	{-2.700,   0.000,   1.800},
	{-2.700,  -0.300,   1.800},
	{-3.000,  -0.300,   1.800},
	{-3.000,   0.000,   1.800},
	{-1.500,   0.300,   2.250},
	{-1.600,   0.300,   2.025},
	{-2.500,   0.300,   2.250},
	{-2.300,   0.300,   2.025},
	{-3.000,   0.300,   2.250},
	{-2.700,   0.300,   2.025},
	{-3.000,   0.300,   1.800},
	{-2.700,   0.300,   1.800},
	{-2.700,   0.000,   1.575},
	{-2.700,  -0.300,   1.575},
	{-3.000,  -0.300,   1.350},
	{-3.000,   0.000,   1.350},
	{-2.500,   0.000,   1.125},
	{-2.500,  -0.300,   1.125},
	{-2.650,  -0.300,   0.938},
	{-2.650,   0.000,   0.938},
	{-2.000,  -0.300,   0.900},
	{-1.900,  -0.300,   0.600},
	{-1.900,   0.000,   0.600},
	{-3.000,   0.300,   1.350},
	{-2.700,   0.300,   1.575},
	{-2.650,   0.300,   0.938},
	{-2.500,   0.300,   1.125},
	{-1.900,   0.300,   0.600},
	{-2.000,   0.300,   0.900},
	{ 1.700,   0.000,   1.425},
	{ 1.700,  -0.660,   1.425},
	{ 1.700,  -0.660,   0.600},
	{ 1.700,   0.000,   0.600},
	{ 2.600,   0.000,   1.425},
	{ 2.600,  -0.660,   1.425},
	{ 3.100,  -0.660,   0.825},
	{ 3.100,   0.000,   0.825},
	{ 2.300,   0.000,   2.100},
	{ 2.300,  -0.250,   2.100},
	{ 2.400,  -0.250,   2.025},
	{ 2.400,   0.000,   2.025},
	{ 2.700,   0.000,   2.400},
	{ 2.700,  -0.250,   2.400},
	{ 3.300,  -0.250,   2.400},
	{ 3.300,   0.000,   2.400},
	{ 1.700,   0.660,   0.600},
	{ 1.700,   0.660,   1.425},
	{ 3.100,   0.660,   0.825},
	{ 2.600,   0.660,   1.425},
	{ 2.400,   0.250,   2.025},
	{ 2.300,   0.250,   2.100},
	{ 3.300,   0.250,   2.400},
	{ 2.700,   0.250,   2.400},
	{ 2.800,   0.000,   2.475},
	{ 2.800,  -0.250,   2.475},
	{ 3.525,  -0.250,   2.494},
	{ 3.525,   0.000,   2.494},
	{ 2.900,   0.000,   2.475},
	{ 2.900,  -0.150,   2.475},
	{ 3.450,  -0.150,   2.513},
	{ 3.450,   0.000,   2.513},
	{ 2.800,   0.000,   2.400},
	{ 2.800,  -0.150,   2.400},
	{ 3.200,  -0.150,   2.400},
	{ 3.200,   0.000,   2.400},
	{ 3.525,   0.250,   2.494},
	{ 2.800,   0.250,   2.475},
	{ 3.450,   0.150,   2.513},
	{ 2.900,   0.150,   2.475},
	{ 3.200,   0.150,   2.400},
	{ 2.800,   0.150,   2.400},
	{ 0.000,   0.000,   3.150},
	{ 0.000,  -0.002,   3.150},
	{ 0.002,   0.000,   3.150},
	{ 0.800,   0.000,   3.150},
	{ 0.800,  -0.450,   3.150},
	{ 0.450,  -0.800,   3.150},
	{ 0.000,  -0.800,   3.150},
	{ 0.000,   0.000,   2.850},
	{ 0.200,   0.000,   2.700},
	{ 0.200,  -0.112,   2.700},
	{ 0.112,  -0.200,   2.700},
	{ 0.000,  -0.200,   2.700},
	{-0.002,   0.000,   3.150},
	{-0.450,  -0.800,   3.150},
	{-0.800,  -0.450,   3.150},
	{-0.800,   0.000,   3.150},
	{-0.112,  -0.200,   2.700},
	{-0.200,  -0.112,   2.700},
	{-0.200,   0.000,   2.700},
	{ 0.000,   0.002,   3.150},
	{-0.800,   0.450,   3.150},
	{-0.450,   0.800,   3.150},
	{ 0.000,   0.800,   3.150},
	{-0.200,   0.112,   2.700},
	{-0.112,   0.200,   2.700},
	{ 0.000,   0.200,   2.700},
	{ 0.450,   0.800,   3.150},
	{ 0.800,   0.450,   3.150},
	{ 0.112,   0.200,   2.700},
	{ 0.200,   0.112,   2.700},
	{ 0.400,   0.000,   2.550},
	{ 0.400,  -0.224,   2.550},
	{ 0.224,  -0.400,   2.550},
	{ 0.000,  -0.400,   2.550},
	{ 1.300,   0.000,   2.550},
	{ 1.300,  -0.728,   2.550},
	{ 0.728,  -1.300,   2.550},
	{ 0.000,  -1.300,   2.550},
	{ 1.300,   0.000,   2.400},
	{ 1.300,  -0.728,   2.400},
	{ 0.728,  -1.300,   2.400},
	{ 0.000,  -1.300,   2.400},
	{-0.224,  -0.400,   2.550},
	{-0.400,  -0.224,   2.550},
	{-0.400,   0.000,   2.550},
	{-0.728,  -1.300,   2.550},
	{-1.300,  -0.728,   2.550},
	{-1.300,   0.000,   2.550},
	{-0.728,  -1.300,   2.400},
	{-1.300,  -0.728,   2.400},
	{-1.300,   0.000,   2.400},
	{-0.400,   0.224,   2.550},
	{-0.224,   0.400,   2.550},
	{ 0.000,   0.400,   2.550},
	{-1.300,   0.728,   2.550},
	{-0.728,   1.300,   2.550},
	{ 0.000,   1.300,   2.550},
	{-1.300,   0.728,   2.400},
	{-0.728,   1.300,   2.400},
	{ 0.000,   1.300,   2.400},
	{ 0.224,   0.400,   2.550},
	{ 0.400,   0.224,   2.550},
	{ 0.728,   1.300,   2.550},
	{ 1.300,   0.728,   2.550},
	{ 0.728,   1.300,   2.400},
	{ 1.300,   0.728,   2.400},
	{ 0.000,   0.000,   0.000},
	{ 1.500,   0.000,   0.150},
	{ 1.500,   0.840,   0.150},
	{ 0.840,   1.500,   0.150},
	{ 0.000,   1.500,   0.150},
	{ 1.500,   0.000,   0.075},
	{ 1.500,   0.840,   0.075},
	{ 0.840,   1.500,   0.075},
	{ 0.000,   1.500,   0.075},
	{ 1.425,   0.000,   0.000},
	{ 1.425,   0.798,   0.000},
	{ 0.798,   1.425,   0.000},
	{ 0.000,   1.425,   0.000},
	{-0.840,   1.500,   0.150},
	{-1.500,   0.840,   0.150},
	{-1.500,   0.000,   0.150},
	{-0.840,   1.500,   0.075},
	{-1.500,   0.840,   0.075},
	{-1.500,   0.000,   0.075},
	{-0.798,   1.425,   0.000},
	{-1.425,   0.798,   0.000},
	{-1.425,   0.000,   0.000},
	{-1.500,  -0.840,   0.150},
	{-0.840,  -1.500,   0.150},
	{ 0.000,  -1.500,   0.150},
	{-1.500,  -0.840,   0.075},
	{-0.840,  -1.500,   0.075},
	{ 0.000,  -1.500,   0.075},
	{-1.425,  -0.798,   0.000},
	{-0.798,  -1.425,   0.000},
	{ 0.000,  -1.425,   0.000},
	{ 0.840,  -1.500,   0.150},
	{ 1.500,  -0.840,   0.150},
	{ 0.840,  -1.500,   0.075},
	{ 1.500,  -0.840,   0.075},
	{ 0.798,  -1.425,   0.000},
	{ 1.425,  -0.798,   0.000}
};

int	patches[NUM_PATCH][16] = {
	{  1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16},
	{  4,  17,  18,  19,   8,  20,  21,  22,  12,  23,  24,  25,  16,  26,  27,  28},
	{ 19,  29,  30,  31,  22,  32,  33,  34,  25,  35,  36,  37,  28,  38,  39,  40},
	{ 31,  41,  42,   1,  34,  43,  44,   5,  37,  45,  46,   9,  40,  47,  48,  13},
	{ 13,  14,  15,  16,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60},
	{ 16,  26,  27,  28,  52,  61,  62,  63,  56,  64,  65,  66,  60,  67,  68,  69},
	{ 28,  38,  39,  40,  63,  70,  71,  72,  66,  73,  74,  75,  69,  76,  77,  78},
	{ 40,  47,  48,  13,  72,  79,  80,  49,  75,  81,  82,  53,  78,  83,  84,  57},
	{ 57,  58,  59,  60,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96},
	{ 60,  67,  68,  69,  88,  97,  98,  99,  92, 100, 101, 102,  96, 103, 104, 105},
	{ 69,  76,  77,  78,  99, 106, 107, 108, 102, 109, 110, 111, 105, 112, 113, 114},
	{ 78,  83,  84,  57, 108, 115, 116,  85, 111, 117, 118,  89, 114, 119, 120,  93},
	{121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136},
	{124, 137, 138, 121, 128, 139, 140, 125, 132, 141, 142, 129, 136, 143, 144, 133},
	{133, 134, 135, 136, 145, 146, 147, 148, 149, 150, 151, 152,  69, 153, 154, 155},
	{136, 143, 144, 133, 148, 156, 157, 145, 152, 158, 159, 149, 155, 160, 161,  69},
	{162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177},
	{165, 178, 179, 162, 169, 180, 181, 166, 173, 182, 183, 170, 177, 184, 185, 174},
	{174, 175, 176, 177, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197},
	{177, 184, 185, 174, 189, 198, 199, 186, 193, 200, 201, 190, 197, 202, 203, 194},
	{204, 204, 204, 204, 207, 208, 209, 210, 211, 211, 211, 211, 212, 213, 214, 215},
	{204, 204, 204, 204, 210, 217, 218, 219, 211, 211, 211, 211, 215, 220, 221, 222},
	{204, 204, 204, 204, 219, 224, 225, 226, 211, 211, 211, 211, 222, 227, 228, 229},
	{204, 204, 204, 204, 226, 230, 231, 207, 211, 211, 211, 211, 229, 232, 233, 212},
	{212, 213, 214, 215, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245},
	{215, 220, 221, 222, 237, 246, 247, 248, 241, 249, 250, 251, 245, 252, 253, 254},
	{222, 227, 228, 229, 248, 255, 256, 257, 251, 258, 259, 260, 254, 261, 262, 263},
	{229, 232, 233, 212, 257, 264, 265, 234, 260, 266, 267, 238, 263, 268, 269, 242},
	{270, 270, 270, 270, 279, 280, 281, 282, 275, 276, 277, 278, 271, 272, 273, 274},
	{270, 270, 270, 270, 282, 289, 290, 291, 278, 286, 287, 288, 274, 283, 284, 285},
	{270, 270, 270, 270, 291, 298, 299, 300, 288, 295, 296, 297, 285, 292, 293, 294},
	{270, 270, 270, 270, 300, 305, 306, 279, 297, 303, 304, 275, 294, 301, 302, 271}
};


/*
 * patch basis type
 */

Matrix	bezier = {
	{-1.0,	3.0,	-3.0,	1.0},
	{3.0,	-6.0,	3.0,	0.0},
	{-3.0,	3.0,	0.0,	0.0},
	{1.0,	0.0,	0.0,	0.0} 
};

Matrix	x, y, z;

extern	int	atoi();

main(argc, argv)
	int	argc;
	char	**argv;
{
	char	dev[20];
	int	i, j, k, params[4];

	fprintf(stderr, "Using %s:\n\n", argv[0]);

	fprintf(stderr, "Use the 'q' key to quit\n");
	fprintf(stderr, "Use the 'x' key to rotate about x\n");
	fprintf(stderr, "Use the 'y' key to rotate about y\n");
	fprintf(stderr, "Use the 'z' key to rotate about z\n");
	fprintf(stderr, "Use the 'e' key to enlarge\n");
	fprintf(stderr, "Use the 'r' key to reduce\n");
	fprintf(stderr, "Use the 'p' key to produce a postscript file\n");
	fprintf(stderr, "   of the current view (teapot.ps)\n");
	fprintf(stderr, "Use the 'h' key to produce a hpgl file\n");
	fprintf(stderr, "   of the current view (teapot.hp)\n\n");

	fprintf(stderr,"Enter output device: ");
	gets(dev);

	params[0] = params[1] = 4;
	params[2] = params[3] = 6;

	if (argc > 2) 
		for (i = 2; i < argc; i++)
			params[i - 2] = atoi(argv[i]);

	vinit(dev);          /* set up device */

	color(BLACK);
	clear();

	window(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
	lookat(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0);

	patchcurves(params[0], params[1]);
	patchprecision(params[2], params[3]);
	patchbasis(bezier, bezier);

	/*
	 * Make an object with the teapot in it.
	 */

	makeobj(TEAPOT);
		color(CYAN);
		for (i = 0; i < NUM_PATCH; i++) {
			/*
			 * Set up geometry arrays...
			 */
			for (j = 0; j < 4; j++) {
				x[0][j] = xyz[patches[i][j] - 1][0];
				x[1][j] = xyz[patches[i][j + 4] - 1][0];
				x[2][j] = xyz[patches[i][j + 8] - 1][0];
				x[3][j] = xyz[patches[i][j + 12] - 1][0];

				y[0][j] = xyz[patches[i][j] - 1][1];
				y[1][j] = xyz[patches[i][j + 4] - 1][1];
				y[2][j] = xyz[patches[i][j + 8] - 1][1];
				y[3][j] = xyz[patches[i][j + 12] - 1][1];

				z[0][j] = xyz[patches[i][j] - 1][2];
				z[1][j] = xyz[patches[i][j + 4] - 1][2];
				z[2][j] = xyz[patches[i][j + 8] - 1][2];
				z[3][j] = xyz[patches[i][j + 12] - 1][2];
			}
			/*
			 * Draw it...
			 */
			patch(x, y, z);
		}
	closeobj();

	backbuffer();

	while (1) {

		color(BLACK);
		clear();
		callobj(TEAPOT);


		swapbuffers();

		switch (getkey()) {
		case 'q':	/* Stop the program */
		case ESC:
			vexit();
			exit(0);

		case 'p':	/* Do a postscript plot of it */
			voutput("teapot.ps");
			vnewdev("postscript");
			fprintf(stderr,"Producing POSTSCRIPT output on file teapot.ps\n");
			callobj(TEAPOT);
			vnewdev(dev);
			break;

		case 'h':	/* Do a hpgl plot of it */
			voutput("teapot.hp");
			vnewdev("hpgl");
			fprintf(stderr,"Producing HPGL output on file teapot.hp\n");
			callobj(TEAPOT);
			vnewdev(dev);
			break;

		case 'x':	/* Obvious isn't it */
			rotate(10.0, 'x');
			break;

		case 'y':
			rotate(10.0, 'y');
			break;

		case 'z':
			rotate(10.0, 'z');
			break;

		case 'e':	/* Enlarge */
			scale(1.1, 1.1, 1.1);
			break;

		case 'r':	/* Reduce */
			scale(0.9, 0.9, 0.9);
			break;

		default:
			;
		}
	}
}
