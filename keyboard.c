#include "keyboard.h"

int lastPressed = -1;

int KYBgetint(int a)
{
   int key = lastPressed;
   lastPressed = -1;
   return key;
}


