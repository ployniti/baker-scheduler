//This is the .h file for all the error structs for exception handling

#pragma once
#include <string>
using namespace std;

struct null_ptr
{
    string msg {"Pointer is null.\n"};
};

struct null_event_ptr
{
    string msg {"Event pointer is null.\n"};
};

struct null_root_ptr
{
    string msg {"Root pointer is null."};
};

struct null_head_ptr
{
    string msg {"Head pointer is null.\n"};
};

struct empty_string
{
    string msg {"No string to search with.\n"};
};

struct empty_name_string
{
    string msg {"Name is empty.\n"};
};

struct empty_location_string
{
    string msg {"Location is empty.\n"};
};

struct no_event_data
{
    string msg {"No event data.\n"};
};

struct no_meeting_data
{
    string msg {"No meeting data.\n"};
};

struct no_shopping_data
{
    string msg {"No shopping data.\n"};
};

struct no_visit_data
{
    string msg {"No visit data.\n"};
};

struct not_shopping_event
{
    string msg {"Not a shopping event, invalid action.\n"};
};
