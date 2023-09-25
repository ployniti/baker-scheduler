//This is the .h file for the base event class and derived client_meeting, shopping, and bakery_visit classes.

#pragma once
#include "main.h"

//Classes
class event
{
    public:
        event();
        virtual ~event();

        virtual void display_event() const;
        virtual int add_event();
        virtual int delete_event() = 0; //pure virtual, making the event class an abstract base class
        string & get_name(); //get event name for comparison
        string & get_location();
    
    protected:
        string name; //name of event
        string date; //when the event is happening
        string start_time;
        string end_time;
        string location; //where the event is happending
        string notes; //notes on the event

    private:
        void clear_data();
};

class client_meeting : public event
{
    public:
        client_meeting();
        //client_meeting(const client_meeting &);
        ~client_meeting();

        void display_event() const;
        int add_event();
        int delete_event();

    private:
        string client; //name of client
        int participant_num; //number of people attending the meeting
        
        void clear_data();
};

class shopping : public event
{
    public:
        shopping();
        ~shopping();

        void display_event() const;
        int add_event();
        int delete_event();
        int add_ingredients(); //add to shopping_list

    private:
        vector <string> shopping_list;
        
        void clear_data();
};

class bakery_visit : public event
{
    public:
        bakery_visit();
        ~bakery_visit();

        void display_event() const;
        int add_event();
        int delete_event();

    private:
        string duty; //what to do during the visit
        
        void clear_data();
};
