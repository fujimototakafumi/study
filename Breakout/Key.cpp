#include "DxLib.h"
#include "Key.h"
//シングルトンと同じ役割のファイル
static int g_key[256] = {};

int gpUpdateKey() {
	int* key = g_key;
	char  tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			key[i]++;
		}
		else {
			key[i] = 0;
		}
	}
	return 0;//key[KEY_INPUT_ESCAPE];
}

bool IsKeyPress(int key)
{
	return g_key[key] > 0;
}

