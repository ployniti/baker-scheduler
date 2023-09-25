//This is the .h file for the client/main program.
//It'll contain prototypes for funtions that interact with the user

#pragma once
#include <iostream>
#include <cctype>
#include <memory>
#include <vector>
#include <array>
#include "error.h"

void main_menu(int & selected_option);
void event_menu(int & selected_option);
void get_name(string & event_name);
void get_location(string & event_location);
