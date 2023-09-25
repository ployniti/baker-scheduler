//This is the .h file for the LLL and L_node classes.

#pragma once
#include "main.h"
#include "event.h"

//Classes
class L_node
{
    public:
        typedef unique_ptr <L_node> L_node_ptr;
        //typedef unique_ptr <event> base_event_ptr;

        L_node();
        ~L_node();
        L_node(const L_node &);
        L_node & operator=(const L_node &);
        
        L_node_ptr & get_next();
        event * & get_event();
        void set_next(L_node_ptr new_next);
        void set_event(event * new_event);
        void display() const;
        int delete_data();
        
        int add_ingredients();

    private:
        //base_event_ptr an_event; //pointer to the base event class
        event * event_ptr;
        L_node_ptr next;
        
        void copy(const L_node & src);
};

class LLL
{
    public:
        typedef unique_ptr <L_node> L_node_ptr;
        //typedef unique_ptr <event> base_event_ptr;
        
        LLL();
        ~LLL();
        LLL(const LLL &);
        LLL & operator=(const LLL &);
        
        L_node_ptr & get_head();
        int remove(const string & name); //remove event with a particular name
        void remove_all(); //remove all nodes in LLL
        int insert(/*base_event_ptr*/ event *); //insert a node passing in address of an event object
        int display(const string & name) const; //display one particular event at a location
        int display_all() const; //display all events at a location
        int add_ingredients(const string & name);
        int delete_data(const string & name);

    private:
        L_node_ptr head;

        int remove(const string & name, L_node_ptr & head);
        void remove_all(L_node_ptr & head);
        int insert(/*base_event_ptr*/ event *, L_node_ptr & head);
        int display(const string & name, const L_node_ptr & head) const;
        int display_all(const L_node_ptr & head) const;
        int add_ingredients(const string & name, const L_node_ptr & head);
        int delete_data(const string & name, const L_node_ptr & head);
        
        void copy(L_node_ptr & dest, const L_node_ptr & src);
};
