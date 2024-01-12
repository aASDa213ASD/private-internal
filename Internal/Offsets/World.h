#pragma once

/* Game related */
#define		GameTime			0x2226D48	/* | 13.24: 0x8c4f90	| */
#define		HudInstance			0x221C510 	/* | 13.24: 0x221C510	| */
#define		oRenderer			0x228D1C0  	/* | 13.24: 0x228D1C0	| */
#define		oRendererHeight		0x10		/* | 13.24: 0x10		| */
#define		oRendererWidth		0xc			/* | 13.24: 0xc			| */
#define		oViewProjMatrices	0x2284710	/* | 13.24: 0x2284710	| */

/* search "Dragonkill" string, go 2 functions above, after all the stuff:
"mov rcx,  cs:qword_xxxxxxxxxx",  above is: "eax, ___security_cookie" */
#define		MinimapInstance		0x222C530	/* | 13.24: 0x222C530	| */
#define		MinimapHud			0x320		/* | 13.24: 0x320		| */
#define		MinimapHudPosition	0x60		/* | 13.24: 0x60		| */
#define		MinimapHudSize		0x68		/* | 13.24:	0x68		| */
