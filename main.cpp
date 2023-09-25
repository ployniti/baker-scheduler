//This is the client program to interact with the user

#include "main.h"
#include "event.h"
#include "LLL.h"
#include "BST.h"

int main()
{
    BST table;
    event * an_event {nullptr};
    int selected_option {0};
    bool agree {true};
    char answer;

    cout << "Welcome to your scheduler!" << endl << endl;
    cout << "What would you like to do?" << endl;

    while (agree && 10 != selected_option)
    {
        main_menu(selected_option);
        
        //Add an event
        if (1 == selected_option)
        {
            int option {0};

            event_menu(option);

            if (1 == option)
                //Add a client meeting event
                an_event = new client_meeting;
            else if (2 == option)
                //Add a shopping event
                an_event = new shopping;
            else if (3 == option)
                //Add a bakery vist
                an_event = new bakery_visit;
            
            //Adding event info
            if (!an_event->add_event())
                cout << "Error adding event info." << endl << endl;
            
            //Inserting event into table
            else
            {
                try
                {
                    if (!table.insert(an_event))
                        cout << "Error adding event to schedule." << endl << endl;
                }
                catch (null_event_ptr null)
                {
                    cout << null.msg << endl;
                }
                catch (empty_location_string empty)
                {
                    cout << empty.msg << endl;
                    //Need to delete pointer if not inserted successfully
                    if (an_event)
                    {
                        delete an_event;
                        an_event = nullptr;
                    }
                }
            }
        }

        //Display an event
        if (2 == selected_option)
        {
            string event_name;
            string location_name;
            
            //Prompt the user for name and location to search with
            get_name(event_name);
            get_location(location_name);
            
            try
            {
                if (!table.display(event_name, location_name))
                    cout << "No match in event name and/or location." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
            catch (empty_location_string empty_location)
            {
                cout << empty_location.msg << endl;
            }
            catch (empty_name_string empty_name)
            {
                cout << empty_name.msg << endl;
            }
            catch (empty_string empty)
            {
                cout << empty.msg << endl;
            }
        }
        
        //Display all events at a location
        if (3 == selected_option)
        {
            string location_name;
            
            //Prompt the user for location to search with
            get_location(location_name);
            
            try
            {
                if (!table.display_all(location_name))
                    cout << "No match in location." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
            catch (empty_location_string empty_location)
            {
                cout << empty_location.msg << endl;
            }
        }
        
        //Display all events in the schedule
        if (4 == selected_option)
        {
            try
            {
                if (!table.display_table())
                    cout << "Error displaying events in the table." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
        }

        //Remove an event
        if (5 == selected_option)
        {
            string event_name;
            string location_name;
            
            //Prompt the user for name and location to search with
            get_name(event_name);
            get_location(location_name);
            
            try
            {
                if (!table.remove_event(event_name, location_name))
                    cout << "No match in event name and/or location." << endl << endl;
                else
                    cout << "Successfully removed " << event_name << " at " << location_name << "." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
            catch (empty_location_string empty_location)
            {
                cout << empty_location.msg << endl;
            }
            catch (empty_name_string empty_name)
            {
                cout << empty_name.msg << endl;
            }
            catch (empty_string empty)
            {
                cout << empty.msg << endl;
            }
        }
        
        //Remove all events at a location
        if (6 == selected_option)
        {
            string location_name;
            
            //Prompt the user for location to search with
            get_location(location_name);
            
            try
            {
                if (!table.remove_location(location_name))
                    cout << "No match in location." << endl << endl;
                else
                    cout << "Successfully removed all events at " << location_name << "." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
            catch (empty_location_string empty_location)
            {
                cout << empty_location.msg << endl;
            }
        }
        
        //Remove all events in schedule
        if (7 == selected_option)
        {
            try 
            {
                table.remove_all();
                cout << "Successfully removed all events at in schedule." << endl << endl;
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty, please add an event first." << endl << endl;
            }
        }
        
        //Add ingredients to a shopping event (where RTTI is used)
        if (8 == selected_option)
        {
            string event_name;
            string location_name;
            
            //Prompt the user for name and location to search with
            get_name(event_name);
            get_location(location_name);
            
            try 
            {
                if (!table.add_ingredients(event_name, location_name))
                    cout << "No match in event name and/or location." << endl << endl;
                else
                    cout << "Successfully added ingredients to shopping list for " << event_name << "." << endl << endl;
            }
            catch (not_shopping_event invalid)
            {
                cout << invalid.msg << endl;
                //throw (invalid);
            }
            catch (null_event_ptr null)
            {
                cout << null.msg << endl;
                //throw (null);
            }
            catch (null_head_ptr null)
            {
                cout << null.msg << endl;
                //throw (null);
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty or event doesn't exist, please add an event first." << endl << endl;
            }
        }
        
        //Delete event type specific data, not the event itself just part of its data
        if (9 == selected_option)
        {
            string event_name;
            string location_name;
            
            //Prompt the user for name and location to search with
            get_name(event_name);
            get_location(location_name);
            
            try 
            {
                if (!table.delete_data(event_name, location_name))
                    cout << "No match in event name and/or location." << endl << endl;
                else
                    cout << "Successfully delete data of " << event_name << "." << endl << endl;
            }
            catch (null_event_ptr null)
            {
                cout << null.msg << endl;
                //throw (null);
            }
            catch (null_head_ptr null)
            {
                cout << null.msg << endl;
                //throw (null);
            }
            catch (null_root_ptr null)
            {
                cout << null.msg << endl;
                cout << "Schedule is empty or event doesn't exist, please add an event first." << endl << endl;
            }
        }

        if (10 != selected_option)
        {
            cout << "Would you like to take another action? (y/n): ";
            cin >> answer;
            cin.ignore(100, '\n');
            cout << '\n';

            if (answer != 'y' && answer != 'Y')
                agree = false;
        }
    }

    cout << "Thank you for using the program!" << endl << endl;

    return 1;
}

//This is the function to display the main menu options for the user
//Argument: int value of the selected option
//Return: void
void main_menu(int & selected_option)
{
    cout << "1) Add an event" << endl
         << "2) Display an event" << endl
         << "3) Display all events at a location" << endl
         << "4) Display all events in schedule" << endl
         << "5) Remove an event" << endl
         << "6) Remove all events at a location" << endl
         << "7) Remove all events in schedule" << endl
         << "8) Add to ingredient list of a shopping event" << endl
         << "9) Delete event type specific data" << endl
         << "10) Quit" << endl << endl;

    do
    {
        cout << "Please select from the options by entering a number between 1 and 10: ";
        cin >> selected_option;
        cin.ignore(100, '\n');
        cout << '\n';

        if (selected_option < 1 || selected_option > 10)
            cout << "Please only enter a number between 1 and 10." << endl << endl;
    } while (selected_option < 1 || selected_option > 10);
}

//This is the function to display the different events they can add
//Argument: int value of the selected option
//Return: void
void event_menu(int & selected_option)
{
    cout << "What event would you like to add: " << endl
         << "1) Client meeting" << endl
         << "2) Ingredient shopping" << endl
         << "3) Bakery visit" << endl << endl;
    
    do
    {
        cout << "Please select from the options by entering a number between 1 and 3: ";
        cin >> selected_option;
        cin.ignore(100, '\n');
        cout << '\n';

        if (selected_option < 1 || selected_option > 3)
            cout << "Please only enter a number between 1 and 3." << endl << endl;
    } while (selected_option < 1 || selected_option > 3);
}

//This is the function to prompt the user for the event_name to find
//Argument: string
//Return: void
void get_name(string & event_name)
{
    cout << "Please enter name of the event: ";
    getline(cin, event_name);
    cout << '\n';
}

//This is the function to prompt the user for the event_location to find
//Argument: string
//Return: void
void get_location(string & event_location)
{
    cout << "Please enter location of the event: ";
    getline(cin, event_location);
    cout << '\n';
}
