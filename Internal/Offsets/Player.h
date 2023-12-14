#pragma once

/* Player related addresses */
#define		Index				0x10	/* | 13.24: 0x10	| */
#define		Team				0x3c	/* | 13.24: 0x3c	| */
#define		Zombie				0x38	/* | 13.24: 0x38	| */
#define		Name				0x60	/* | 13.24: 0x60	| */
#define		HeroName			0x38a8	/* | 13.24: 0x38a8	| */
#define		Direction			0x3EB4	/* | 13.24: 0x3EB4	| */
#define		NetworkId			0xC8	/* | 13.24: 0xC8	| */
#define		Position			0x220	/* | 13.24: 0x220	| */
#define		StatOwner			0x290	/* | 13.24: 0x290	| */
#define		IsVisible			0x340	/* | 13.24: 0x340	| */
#define		SpawnCount			0x358	/* | 13.24: 0x358	| */
#define		Mana				0x370	/* | 13.24: 0x370	| */
#define		MaxMana				0x388	/* | 13.24: 0x388	| */
#define		IsTargetable		0xeb0	/* | 13.24: 0xeb0	| */
#define		Invulnerable		0x4F0	/* | 13.24: 0x4F0	| */
#define		MaxHealth			0x10A0	/* | 13.24: 0x10A0	| */
#define		Health				0x1088	/* | 13.24:	0x1088	| */
#define		Shield				0x10b8	/* | 13.24:	0x10b8	| */
#define		PhysicalShield		0x10d0	/* | 13.24:	0x10d0	| */
#define		MagicalShield		0x10e8	/* | 13.24:	0x10e8	| */
#define		Gold				0x2148	/* | 13.24: 0x2148	| */
#define		TotalGold			0x2130	/* | 13.24:	0x2130	| */
#define		CombatType			0x2670	/* | 13.24: 0x2670	| */
#define		Direction			0x2190	/* | 13.24:	0x2190	| */
#define		Spellbook			0x2A38	/* | 13.24:	0x2A38	| */
#define		SpellSlots			0x6d0	/* | 13.24:	0x6d0	| */
#define		AttackDamageBase	0x16B4	/* | 13.24:	0x16B4	| */
#define		AttackDamageBonus	0x1620	/* | 13.24:	0x1620	| */
#define		AbilityPower		0x15D0	/* | 13.24:	0x15D0	| */

/* Player related functions */
#define		fGetHealthBarPosition	0x7D77E0	/* | 13.24:	0x7D77E0 | */