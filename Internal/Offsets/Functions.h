#pragma once

/* Spells Related */
#define		fCastSpellClick			0x8c4f90	/* | 13.24: 0x8c4f90	| */
#define		fCastSpell				0x6B7ED0	/* | 13.24: 0x6B7ED0	| */
#define		fHudCastSpell			0x822380	/* | 13.24: 0x822380	| */

/* AI Related */
#define		fBuildNavPath			0xd380b0	/* | 13.24: 0xd380b0	| */
#define		fSmoothPath				0x8b7870	/* | 13.24: 0x8b7870	| */
#define		fNewIssueOrder			0x8d94a0	/* | 13.24: 0x8d94a0	| */
#define		fIsAlive				0x3d65d0	/* | 13.24: 0x3d65d0	| */

/* Getters */
#define		fGetAiManager			0x20b950	/* | 13.24: 0x20b950	| */
#define		fGetStat				0x2B9800	/* | 13.24: 0x2B9800	| */
#define		fGetBoundingRadius		0x85A820	/* | 13.24: 0x85A820	| */
#define		fGetHealthBarPosition	0x7D77E0	/* | 13.24: 0x7D77E0	| */
#define		fGetSpellState			0x6A44D0	/* | 13.24: 0x6A44D0	| */
#define		fGetAttackDelay			0x3d65c0	/* | 13.24: 0x3d65c0	| */
#define		fGetAttackCastDelay		0x3d64c0	/* | 13.24: 0x3d64c0	| */

/* VMT Hook Essentials */
#define		OnProcessSpellCast		0x1391e9	/* | 13.24: 0x1391e9	| */
