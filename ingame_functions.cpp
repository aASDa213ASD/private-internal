#include "ingame_functions.h"
#include <Windows.h>

#include <time.h>
#include <dinput.h>
#include <map>
#include <iostream>



void copy_to_clipboard(char* text) {

    const size_t len = strlen(text) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), text, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

}

void press_key(DWORD key_code, float sleep_for) {
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    key = key_code;//VkKeyScan('q');
    mappedkey = MapVirtualKey(LOBYTE(key), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedkey;
    SendInput(1, &input, sizeof(input));
    Sleep(sleep_for);
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));

}

void key_down(DWORD key_code) {
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    key = key_code;//VkKeyScan('q');
    mappedkey = MapVirtualKey(LOBYTE(key), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedkey;
    SendInput(1, &input, sizeof(input));

}

void key_up(DWORD key_code) {
    SHORT key;
    UINT mappedkey;
    INPUT input = { 0 };
    key = key_code;//VkKeyScan('q');
    mappedkey = MapVirtualKey(LOBYTE(key), 0);
    input.type = INPUT_KEYBOARD;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.wScan = mappedkey;
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));

}