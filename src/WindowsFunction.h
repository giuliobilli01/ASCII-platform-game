#pragma once
#include "Constant.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

void setcursor();

void gotoxy(int x, int y);

void set_console_size(int W_console, int H_console);

void init_console(int W_console, int H_console);

void non_blocking_getch(char* input);