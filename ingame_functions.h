#pragma once
#include <iostream>
#include <windows.h>
typedef void(__fastcall* fnPrintChat)(DWORD, const char*, int);
typedef bool(__fastcall* fnIsAlive)(uint64_t* obj);
typedef float(__cdecl* fnGetAttackDelay)(uint64_t* obj);
typedef float(__cdecl* fnGetAttackCastDelay)(uint64_t* obj);
typedef bool(__fastcall* fnIsMinion)(uint64_t* a1);
typedef bool(__fastcall* fnIsPlayer)(uint64_t* a1);
typedef int(__fastcall* fnNewIssueOrder)(uint64_t HudThisPtr, int state, int IsAttack, int IsAttackCommand, int x, int y, int AttackAndMove);
typedef int(__fastcall* fnBuildNavPath)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64* a5, __int64 a6, BYTE* a7, float* a8, BYTE* a9, __int64 a10, char a11);
typedef uint64_t(__fastcall* fnGetAiManager)(uint64_t player_adress); // Определяется через fnGetAiManager GetAiManager = reinterpret_cast<fnGetAiManager>(Globals::Base + fGetAiManager);
//typedef DWORD*(__fastcall* OnProcessSpellCast)(void* thisptr, void* edx, int state, SpellCastInfo* spellCastInfo, int a6);
extern fnIsAlive IsAlive;
extern fnPrintChat PrintChat;
extern fnIsMinion fIsMinion;
extern fnGetAttackCastDelay GetAttackCastDelay;
extern fnGetAttackDelay GetAttackDelay;
extern fnIsPlayer IsPlayer;
void copy_to_clipboard(char* text);
void press_key(DWORD key_code, float sleep_for);
void key_down(DWORD key_code);
void key_up(DWORD key_code);