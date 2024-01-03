#pragma once

/* Object managers */
#define		LocalPlayer		0x223A0B8 	/* | 13.24: 0x223A0B8	| */
#define		HeroList		0x221C620	/* | 13.24: 0x221C620	| */
#define		MinionList		0x221F590	/* | 13.24: 0x221F590	| */
#define		MinionListSize	0x10	 	/* | 13.24: 0x10		| */
#define		MissileList		0x223A1B0	/* | 13.24: 0x223A1B0	| */
#define		MissileListSize	0x10	 	/* | 13.24: 0x10		| */
#define		TurretList		0x2225FC0	/* | 13.24: 0x2225FC0	| */
#define		ObjectManager	0x217B230	/* | 13.24: 0x217B230	| */

/* Spell and missile*/
#define		SpellCastSpellInfo		0x0
#define		SpellCastSpellSlot		0x8
#define		SpellCastStart			0xA4
#define		SpellCastEnd			0xB0
#define		SpellCastMousePos		0xbc
#define		IsSpell					0x10c
#define		IsAAFlags				0x110
#define		SpellCastSrcIdx			0x90
#define		SpellCastNetworkID		0x94	// 0x9C
#define		SpellCastDestIdx		0xE8
#define		SpellCastDirection		0xd4	// 0xDC
#define		SpellCastCastTime		0xF0	// ex: Lux Q 0.250
#define		SpellCastStartTime		0x188	// 0x12c
#define		MissileRadius			0x124
#define		SpellCastCastTimeEnd	0x16C	// 0x16C // CastTime + StartTime
#define		StartTimeAfterCastDelay 0x164
#define		SpellCastWidth			0x540	// [[0x3433a3f290] + 0x60] + 0x540 // CastTime + StartTime
#define		CastFlags 				0x170

#define		SpellInfoSpellData		0x60
#define		SpellDataMissileName	0x80

#define		MissileSpellInfo		0x2E8
#define		MissileSrcIdx			0x370
#define		MissileDestIdx			0x3C8
#define		MissileStartPos			0x38C
#define		MissileEndPos			0x398