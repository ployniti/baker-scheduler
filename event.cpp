//This is the code for the methods in the base event class and derived client_meeting, shopping, and bakery_visit classes.

#include "event.h"

/*EVENT*/
//Default constructor
event::event() //all string data members don't need initialization
{
}

/*
event::event(const event & src):
            name(src.name), date(src.date), start_time(src.start_time), end_time(src.end_time), location(src.location), notes(src.notes)
{
}
*/

//Destructor
event::~event()
{
    clear_data();
}

//This is the function to display the event class data members
//Argument: none
//Return: void
void event::display_event() const
{
    no_event_data error;

    //Check that there are the required data before displaying, notes are optional
    if (!name.empty() && !date.empty() && !start_time.empty() && !end_time.empty() && !location.empty())
    {
        cout << "Event name: " << name << endl
             << "Date: " << date << endl
             << "From: " << start_time << endl
             << "To: " << end_time << endl
             << "Location: " << location << endl
             << "Notes: " << notes << endl << endl;
    }
    else
        throw (error);
}

//This is the function to prompt and set the event class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int event::add_event()
{
    //User must enter in certain fields
    do
    {
        cout << "Please enter name of the event: ";
        getline(cin, name);
    } while (name.empty());
    
    do
    {
        cout << "Please enter date of the event: ";
        getline(cin, date);
    } while (date.empty());
    
    do
    {
        cout << "When is the event from: ";
        getline(cin, start_time);
    } while (start_time.empty());
    
    do
    {
        cout << "When is the event until: ";
        getline(cin, end_time);
    } while (end_time.empty());
    
    do
    {
        cout << "Where is the event: ";
        getline(cin, location);
    } while (location.empty());

    cout << "Add notes about the event (optional): ";
    getline(cin, notes);

    return 1;
}

/*
//This is the function to delete/clear the event class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int event::delete_event()
{
    clear_data();
    return 1;
}
*/

//This is the function to clear the data members in the event class
//Argument: none
//Return: void
void event::clear_data()
{
    //Clear string data members
    if (!name.empty())
        name.clear();

    if (!date.empty())
        date.clear();

    if (!start_time.empty())
        start_time.clear();

    if (!end_time.empty())
        end_time.clear();

    if (!location.empty())
        location.clear();

    if (!notes.empty())
        notes.clear();
}

//This is the function to get the name of the event for comparison and finding
//Argument: none
//Return: string name
string & event::get_name()
{
    return name;
}

//This is the function to get the location of the event for comparison and finding
//Argument: none
//Return: string location
string & event::get_location()
{
    return location;
}

/*CLIENT_MEETING*/
//Default constructor
client_meeting::client_meeting():participant_num(0)
{
}

/*
client_meeting::client_meeting(const client_meeting & src):event(src), client(src.client), participant_num(src.participant_num)
{
}
*/

//Destructor
client_meeting::~client_meeting()
{
    clear_data();
}

//This is the function to display the client_meeting class data members
//Argument: none
//Return: void
void client_meeting::display_event() const
{
    no_meeting_data error;
    
    cout << "/***CLIENT MEETING***/" << endl;

    event::display_event();

    if (!client.empty())
    {
        cout << "Client: " << client << endl
             << "Participant numbers: " << participant_num << endl << endl;
    }
    else
        throw (error);
}

//This is the function to prompt and set the client_meeting class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int client_meeting::add_event()
{
    cout << "Adding a client meeting event" << endl;

    int val {event::add_event()};

    cout << "Which client are you meeting with: ";
    getline(cin, client);
    
    cout << "How many people will be there: ";
    cin >> participant_num;
    cin.ignore(100, '\n');

    cout << '\n';

    return ++val;
}

//This is the function to delete/clear the client_meeting class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int client_meeting::delete_event()
{
    //int val {event::delete_event()}; //call base class delete function
    
    clear_data();

    return 1;
    //return ++val;
}

//This is the function to clear the data members in the client_meeting class
//Argument: none
//Return: void
void client_meeting::clear_data()
{
    if (!client.empty())
        client.clear();

    participant_num = 0;
}

/*SHOPPING*/
//Default constructor
shopping::shopping()
{
}

//Destructor
shopping::~shopping()
{
    clear_data();
}

//This is the function to display the shopping class data members
//Argument: none
//Return: void
void shopping::display_event() const
{
    cout << "/***SHOPPING***/" << endl;
    
    no_shopping_data error;

    event::display_event();

    if (!shopping_list.empty())
    {
        cout << "Shopping list: " << endl;
        for (auto i : shopping_list)
            cout << i << endl;
        cout << '\n';
    }
    else
        throw (error);
}

//This is the function to prompt and set the shopping class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int shopping::add_event()
{
    cout << "Adding a shopping event" << endl;
    
    int val {event::add_event()}; //call base class add function
    char answer;
    
    //Check if they want to start a shopping list, if so calls the add_ingredients function
    cout << "Would you like to start a shopping list (Y/N): ";
    cin >> answer;
    cin.ignore(100, '\n');
    cout << '\n';

    if (answer == 'y' || answer == 'Y')
        val += add_ingredients();
    
    return val;
}

//This is the function to add ingredients to the shopping_list vector
//Argument: none
//Return: int, 1 for success, 0 for failure
int shopping::add_ingredients()
{
    bool agree {true};
    char answer;
    
    while (agree)
    {
        string item;
        cout << "What would you like to add to the shopping list?: ";
        getline(cin, item);
        shopping_list.push_back(item);

        cout << "Add more items? (Y/N) ";
        cin >> answer;
        cin.ignore(100, '\n');
        cout << '\n';

        if (answer != 'y' && answer != 'Y')
            agree = false;
    }

    return 1;
}

//This is the function to delete/clear the shopping class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int shopping::delete_event()
{
    //int val {event::delete_event()}; //call base class delete function
    
    clear_data();
    return 1;
    //return ++val;
}

//This is the function to clear the data members in the shopping class
//Argument: none
//Return: void
void shopping::clear_data()
{
    if (!shopping_list.empty())
        shopping_list.clear();
}

/*BAKERY_VISIT*/
//Default constructor
bakery_visit::bakery_visit() //all string data members don't need initialization
{
}

//Destructor
bakery_visit::~bakery_visit()
{
    clear_data();
}

//This is the function to display the bakery_visit class data members
//Argument: none
//Return: void
void bakery_visit::display_event() const
{
    cout << "/***BAKERY VISIT***/" << endl;
    
    no_visit_data error;

    event::display_event();

    if (!duty.empty())
        cout << "Duty: " << duty << endl << endl;
    else
        throw (error);
}

//This is the function to prompt and set the bakery_visit class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int bakery_visit::add_event()
{
    cout << "Adding a bakery visit event" << endl;
    
    int val {event::add_event()};

    cout << "What is the duty during the visit: ";
    getline(cin, duty);
    cout << '\n';
    
    return ++val;
}

//This is the function to delete/clear the bakery_visit class data members
//Argument: none
//Return: int, 1 for success, 0 for failure
int bakery_visit::delete_event()
{
    //int val {event::delete_event()}; //call base class delete function
    
    clear_data();
    return 1;
    //return ++val;
}

//This is the function to clear the data members in the bakery_visit class
//Argument: none
//Return: void
void bakery_visit::clear_data()
{
    if (!duty.empty())
        duty.clear();
}
