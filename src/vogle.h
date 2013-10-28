/*
 * default location for font library
 */
#ifdef PC	/* Stupid pox head crap */
#define	FONTLIB	"c:\\lib\\hershey\\"
char	*vallocate();
char	*malloc();
#endif

#ifndef FONTLIB
#define FONTLIB	"/usr/local/lib/hershey/"
#endif

/*
 * standard colour indices
 */
#define	BLACK		0
#define	RED		1
#define	GREEN		2
#define	YELLOW		3
#define	BLUE		4
#define	MAGENTA		5
#define	CYAN		6
#define	WHITE		7

/*
 * when (if ever) we need the precision
 */
#ifdef DOUBLE
#define	float	double
#endif

/*
 * How to convert degrees to radians
 */
#define	PI	3.14159265358979
#define D2R	(PI / 180.0)

/*
 * miscellaneous typedefs and type defines
 */
typedef float	Vector[4];
typedef float	Matrix[4][4];
typedef float	Tensor[4][4][4];

/*
 * when register variables get us into trouble
 */
#ifdef NOREGISTER
#define	register
#endif

/*
 * max number of vertices in a ploygon
 */
#define	MAXVERTS	128

/*
 * max number of characters in a font name
 */
#define	FONTNAMELEN	32

/*
 * object definitions
 */
#define MAXENTS		101		/* size of object table */
#define	MAXTOKS		100		/* num. of tokens alloced at once in
					   an object  */

/*
 * functions which can appear in objects
 */
#define	ARC		1
#define	BOXTEXT		2
#define	CALLOBJ		3
#define	CENTERTEXT	4
#define	CIRCLE		5
#define	CLEAR		6
#define	COLOR		7
#define	DRAW		8
#define	DRAWCHAR	9
#define	DRAWSTR		10
#define	FIXEDWIDTH	11
#define	FONT		12
#define	HATCHANG	13
#define	HATCHPITCH	14
#define	LOADMATRIX	15
#define	MAPCOLOR	16
#define	MOVE		17
#define	MULTMATRIX	18
#define	POLY		19
#define	POLYFILL	20
#define	POLYHATCH	21
#define	POPATTRIBUTES	22
#define	POPMATRIX	23
#define	POPVIEWPORT	24
#define	PUSHATTRIBUTES	25
#define	PUSHMATRIX	26
#define	PUSHVIEWPORT	27
#define	RCURVE		28
#define	RPATCH		29
#define	SECTOR		30
#define	TEXTANG		31
#define	TEXTSIZE	32
#define	VIEWPORT	33
#define	BACKBUFFER	34
#define	FRONTBUFFER	35
#define	SWAPBUFFER	36
#define	BACKFACING	37

/*
 * data types for object tokens
 */
typedef union tk {
	int		i;
	float		f;
} Token;

typedef struct tls {
	int		count;
	Token		*toks;
	struct tls	*next;
} TokList;

/*
 * attributes
 */
typedef struct {
	char    fill,
		hatch,
		backface,
		centered,
		fixedwidth;
	int     color;
	float   fontheight;
	float   fontwidth;
	float	hatchcos,
		hatchsin,
		hatchpitch;
	float	textcos,
		textsin;
	char    font[FONTNAMELEN];
} Attribute;

/*
 * viewport
 */
typedef struct vp {
	float	left;
	float	right;
	float	bottom;
	float	top;
} Viewport; 

/*
 * stacks
 */
typedef	struct	ms {	/* Matrix stack entries	*/
	Matrix		m;
	struct	ms	*back;
} Mstack;

typedef	struct	as {	/* Attribute stack entries */
	Attribute	a;
	struct	as	*back;
} Astack;

typedef	struct	vs {	/* Viewport stack entries */
	Viewport	v;
	struct	vs	*back;
} Vstack;

/*
 * vogle device structures
 */
typedef struct dev {
	char	*devname;		/* name of device */
	char	*large,			/* name of large font */
		*small;			/* name of small font */
	int	(*Vbackb)(),		/* Set drawing in back buffer */
		(*Vchar)(),		/* Draw a hardware character */
		(*Vcheckkey)(),		/* Ckeck if a key was hit */
		(*Vclear)(),		/* Clear the screen to current color */
		(*Vcolor)(),		/* Set current color */
		(*Vdraw)(),		/* Draw a line */
		(*Vexit)(),		/* Exit graphics */
		(*Vfill)(),		/* Fill a polygon */
		(*Vfont)(),		/* Set hardware font */
		(*Vfrontb)(),		/* Set drawing in front buffer */
		(*Vgetkey)(),		/* Wait for and get the next key hit */
		(*Vinit)(),		/* Initialise the device */
		(*Vlocator)(),		/* Get mouse/cross hair position */
		(*Vmapcolor)(),		/* Set color indicies */
		(*Vstring)(),		/* Draw a hardware string */
		(*Vswapb)();		/* Swap front and back buffers */
} DevEntry;

typedef struct vdev {
	char		initialised,
			clipoff,
			inobject,
			inpolygon,
			upset,			/* is up vector set */
			cpVvalid,		/* is the current device position valid */
			inbackbuffer,		/* are we in the backbuffer */
			clipplanes;		/* active clipping planes */
	void		(*pmove)(),		/* Polygon moves */
			(*pdraw)();		/* Polygon draws */
	TokList		*tokens;		/* ptr to list of tokens for current object */
	Mstack		*transmat;		/* top of transformation stack */
	Astack		*attr;			/* top of attribute stack */
	Vstack		*viewport;		/* top of viewport stack */
	float		hheight, hwidth;	/* hardware character height, width */
	Vector		cpW,			/* current postion in world coords */
			cpWtrans,		/* current world coords transformed */
			upvector;		/* world up */
	int		depth,			/* # bit planes on screen */
			maxVx, minVx,
			maxVy, minVy,
			sizeX, sizeY, 		/* size of square on screen */
			sizeSx, sizeSy,		/* side in x, side in y (# pixels) */
			cpVx, cpVy;
	DevEntry	dev;
} Device;

extern Device	vdevice;		/* device structure */

#define	V_X	0			/* x axis in cpW */
#define	V_Y	1			/* y axis in cpW */
#define	V_Z	2			/* z axis in cpW */
#define	V_W	3			/* w axis in cpW */

/*
 * function definitions
 */

/*
 * arc routines
 */
extern void	arcprecision();
extern void	arc();
extern void	circle();

/*
 * attr routines
 */
extern void	popattributes();
extern void	pushattributes();

/*
 * curve routines
 */
extern void	curve();
extern void	rcurve();
extern void	curven();
extern void	drcurve();
extern void	curvebasis();
extern void	curveprecision();

/*
 * draw routines
 */
extern void	draw();
extern void	draw2();
extern void	rdraw();
extern void	rdraw2();
extern void	sdraw2();
extern void	rsdraw2();

/*
 * device routines
 */
extern void	clear();
extern void	color();
extern int	getkey();
extern int	getplanes();
extern int	locator();
extern int	slocator();
extern void	mapcolor();

extern void	vinit();
extern void	vexit();
extern void	verror();
extern void	voutput();
extern void	vnewdev();
extern char	*vgetdev();

/*
 * mapping routines
 */
extern int	WtoVx();
extern int	WtoVy();
extern void	VtoWxy();
extern void	CalcW2Vcoeffs();

/*
 * general matrix and vector routines
 */
extern void	mult4x4();
extern void	copymatrix();
extern void	identmatrix();
extern void	copytranspose();

extern void	multvector();
extern void	copyvector();
extern void	premultvector();

/*
 * matrix stack routines
 */
extern void	getmatrix();
extern void	popmatrix();
extern void	loadmatrix();
extern void	pushmatrix();
extern void	multmatrix();
extern Matrix	*getmstackaddress();

/*
 * move routines
 */
extern void	move();
extern void	move2();
extern void	rmove();
extern void	rmove2();
extern void	smove2();
extern void	rsmove2();

/*
 * object routines
 */
extern int	isobj();
extern int	genobj();
extern void	delobj();
extern void	makeobj();
extern void	loadobj();
extern void	saveobj();
extern void	callobj();
extern void	closeobj();
extern int	getopenobj();
extern Token	*newtokens();

/*
 * patch routines.
 */
extern void	patch();
extern void	rpatch();
extern void	drpatch();
extern void	patchbasis();
extern void	patchcurves();
extern void	patchprecision();
extern void	transformtensor();

/*
 * point routines
 */
extern void	point();
extern void	point2();
extern void	spoint2();

/*
 * polygon routines.
 */
extern void	poly();
extern void     hatchang();
extern void	makepoly();
extern void	polyfill();
extern void	closepoly();
extern void	polyhatch();
extern void     hatchpitch();

/*
 * rectangle routine
 */
extern void	rect();

/*
 * tensor routines
 */
extern void multtensor();
extern void copytensor();
extern void premulttensor();
extern void copytensortrans();

/*
 * text routines
 */
extern void	font();
extern void	boxfit();
extern void	boxtext();
extern void	drawstr();
extern void	textang();
extern int	numchars();
extern void	drawchar();
extern void	textsize();
extern float	strlength();
extern float	sstrlength();
extern void	centertext();
extern void	fixedwidth();
extern void	getcharsize();
extern void	getfontsize();
extern float	getfontwidth();
extern float	getfontheight();

/*
 * transformation routines
 */
extern void	scale();
extern void	translate();
extern void	rotate();

/*
 * window definition routines
 */
extern void	ortho();
extern void	ortho2();
extern void	lookat();
extern void	window();
extern void	polarview();
extern void	perspective();

/*
 * routines for manipulating the viewport
 */
extern void	viewport();
extern void	popviewport();
extern void	pushviewport();

/*
 * routines for retrieving the graphics position
 */
extern void	getgp();
extern void	getgp2();
extern void	sgetgp2();

/*
 * routines for retrieving the aspect details of the device
 */
extern float	getaspect();
extern void	getfactors();
extern void	getdisplaysize();

/*
 * routines for handling the buffering
 */
extern int	backbuffer();
extern void	frontbuffer();
extern int	swapbuffers();
