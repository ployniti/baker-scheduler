//This is the .h file for the BST and T_node classes.

#pragma once
#include "main.h"
#include "LLL.h"

class T_node
{
    public:
        typedef unique_ptr <T_node> T_node_ptr;

        T_node();
        ~T_node();
        T_node(const T_node &);
        T_node & operator=(const T_node &);

        T_node_ptr & get_left();
        T_node_ptr & get_right();
        void set_left(T_node_ptr new_left);
        void set_right(T_node_ptr new_right);
        int add_event(event *);
        int set_location(const string &);
        string & get_location();
        int display_all() const;
        int display(const string & name) const; //display one particular event at a location
        int remove_event(const string & name);
        bool has_events(); //Return true if there are events in the T_node
        void copy(const T_node &); //Use to copy data from one T_node to another
        int add_ingredients(const string & name); //add ingredients to a shopping event
        int delete_data(const string & name); //delete event type specific data
    
    private:
       LLL events;
       string location; //what the event is grouped by
       T_node_ptr left;
       T_node_ptr right;

       //void copy(const T_node &);
};

class BST
{
    public:
        typedef unique_ptr <T_node> T_node_ptr;
        //typedef unique_ptr <event> base_event_ptr;
        
        BST();
        ~BST();
        BST(const BST &);
        BST & operator=(const BST &);

        int remove_event(const string & name, const string & location); //remove event with a particular name at a particular location
        int remove_location(const string & location); //remove all events at a particular location
        void remove_all(); //remove all nodes in BST
        int insert(/*base_event_ptr* &*/ event * /*, const string & location*/);
        int display(const string & name, const string & location) const; //display one particular event at a location
        int display_all(const string & location) const; //display all events at a location
        int display_table() const;

        int add_ingredients(const string & name, const string & location); //add ingredients to a shopping event
        int delete_data(const string & name, const string & location);

    private:
        T_node_ptr root;

        int remove_event(const string & name, const string & location, T_node_ptr & root);
        int remove_location(const string & location, T_node_ptr & root);
        void remove_all(T_node_ptr & root);
        int insert(/*base_event_ptr &*/ event *, const string & location, T_node_ptr & root);
        int display(const string & name, const string & location, const T_node_ptr & root) const;
        int display_all(const string & location, const T_node_ptr & root) const;
        int display_table(const T_node_ptr & root) const;
        
        int add_ingredients(const string & name, const string & location, const T_node_ptr & root);
        int delete_data(const string & name, const string & location, const T_node_ptr & root);
        
        void copy(T_node_ptr & dest, const T_node_ptr & src);
};
