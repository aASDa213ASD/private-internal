#pragma once

/* */

/* spell related */
#define		fCastSpellClick			0x8c4f90	// | Maybe outdated | 0x8b9750 */
#define		fCastSpell				0x6B7ED0	//UPDATED 13.8 // 0x6AC1D0 ERROR: Client Tried to cast a spell from an invalid slot: %i.\n
#define		fHudCastSpell			0x822380	//UPDATED 13.8  // 0x815430 // E8 ?? ?? ?? ?? 48 8B 5C 24 ?? C6 87 ?? ?? ?? ?? ?? C6 87 ?? ?? ?? ?? ??

/*  ai related */
#define		fBuildNavPath			0xd380b0	// | Outdated | 48 8B C4 48 89 58 10 55 56 57 41 54 41 55 41 56 41 57 48 8D
#define		fSmoothPath				0x8b7870	// | Outdated |40 53 55 41 56 48 83 EC 50 48
#define		fNewIssueOrder			0x8d94a0	//0x8CDE50 //48 83 EC 48 44 8B 42 siga upd // ИСпользую // 0x8463E0
#define		fIsAlive				0x3d65d0	// 0x2b4419 // 0x24fcf0 // uipd// 0x22a7c0 //0x22a7c0// 0x229500//0x223140// 13.8 - 0x2242E0




/* Get-s */


#define		fGetHealthBarPosition	0x7D77E0	// | 13.24:	0x7D77E0 |
#define		fGetAiManager			0x20b950	// | 0x20a8d0  | 0x1ec8d0 | 0x1eace0 
#define		fGetStat				0x2B9800	// UPDATED 13.8 // 0x2B3FA0  / "CharAbilityPower" SUB SOPRA
#define		fGetBoundingRadius		0x85A820	//0x1e6d90 //0x1E2150 // UPDATED 13.8 // 0x1DCE20   / E8 ? ? ? ? 0F 28 F8 48 8B D3 48 8B CE
#define		fGetHealthBarPosition	0x7D77E0	// UPDATED 13.8 //  0x7CCA00  / ACCESSES MAX ZOOM VALUE from debugger
#define		fGetSpellState			0x6A44D0	//UPDATED 13.8 // 0x6974E0 // E8 ? ? ? ? 48 8B CE 44 8B F8
#define		fGetAttackDelay			0x3d65c0	// 0x3CD100 // UPD //0x38d2a0 //0x3885a0// 0x37D730//13.8 - 0x37a0e0 ?
#define		fGetAttackCastDelay		0x3d64c0	//0x3CD000 // UPD //0x38d1a0//  0x3884a0//0x37D630//13.8 -  0x379fe0 ?



/* VMT hook essentials */

#define		OnProcessSpellCast		0x1391e98	// АХТУНГ!!! АУТДЕЙТЕД// 0x1d2ad0//Неее, нужный vtable на 0x1188 и индекс у онпроцесспелла - 29 // хуйня -  0x2143b0// А может быть 0x6bba80, как в 13.8 хотпатче, не ебу :(
