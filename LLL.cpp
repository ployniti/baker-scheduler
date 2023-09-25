//This is the code for the methods in the L_node and LLL classes.

#include "LLL.h"

/*L_node*/
//Default constructor
L_node::L_node():event_ptr(nullptr), next(nullptr)
{
}

//Destructor
L_node::~L_node()
{
    if (next)
        next.reset();

    if (event_ptr)
    {
        delete event_ptr;
        event_ptr = nullptr;
    }

    /*
    if (an_event)
        an_event.reset();
    */
}

//Copy constructor
L_node::L_node(const L_node & src):event_ptr(nullptr), next(nullptr)
{
    copy(src);
}

//Assignment operator
L_node & L_node::operator=(const L_node & src)
{
    if (this == &src)
        return *this;

    //Delete data in the L_node
    if (next)
        next.reset();

    if (event_ptr)
    {
        delete event_ptr;
        event_ptr = nullptr;
    }

    /*
    if (an_event)
        an_event.reset();
    */

    copy(src);

    return *this;
}

//This is the copy function to copy the L_node's data (base event ptr) from another L_node
//Argument: L_node object reference
//Return: void
void L_node::copy(const L_node & src)
{
    //null_ptr null;

    if (!src.event_ptr)
    {
        event_ptr = nullptr;
        return;
    }

    //Needs to do RTTI
    client_meeting * meeting_ptr {dynamic_cast <client_meeting *> (src.event_ptr)};
    shopping * shopping_ptr {dynamic_cast <shopping *> (src.event_ptr)};
    bakery_visit * visit_ptr {dynamic_cast <bakery_visit *> (src.event_ptr)};

    if (meeting_ptr)
        event_ptr = new client_meeting(*meeting_ptr);
    else if (shopping_ptr)
        event_ptr = new shopping(*shopping_ptr);
    else if (visit_ptr)
        event_ptr = new bakery_visit(*visit_ptr);
}

//This is the function to return the next pointer
//Argument: none
//Return: L_node_ptr reference
typename L_node::L_node_ptr & L_node::get_next()
{
    return next;
}

//This is the function to set the node's next pointer
//Argument: next L_node_ptr
//Return: void
void L_node::set_next(typename L_node::L_node_ptr new_next)
{
    //Is this correct?
    if (!new_next) //new_next is nullptr
        next.reset();
    else
    {
        unique_ptr <L_node> temp (new L_node(*new_next));
        next = move(temp);
    }

    //next = move(new_next);
}

//This is the function to return the event_ptr of a node
//Argument: none
//Return: void
event * & L_node::get_event()
{
    return event_ptr;
}

//This is the function to set the node's event_ptr
//Argument: event pointer
//Return: void
void L_node::set_event(event * new_event)
{
    //Is this correct?
    event_ptr = new_event;
}

//This is the display function to display the event being pointed to by the event_ptr
//Argument: none
//Return: void
void L_node::display() const
{
    null_event_ptr null;

    if (!event_ptr)
        throw (null);
    
    try
    {
        event_ptr->display_event();
    }
    catch (no_visit_data error)
    {
        throw (error);
        //cout << error.msg << endl;
    }
    catch (no_shopping_data error)
    {
        throw (error);
        //cout << error.msg << endl;
    }
    catch (no_meeting_data error)
    {
        throw (error);
        //cout << error.msg << endl;
    }
    catch (no_event_data error)
    {
        throw (error);
        //cout << error.msg << endl;
    }
}

//This is the function to add ingredients to shopping list of a shopping event
//Argument: none
//Return: int, 1 for success, 0 for failure
int L_node::add_ingredients()
{
    null_event_ptr null;
    not_shopping_event invalid;

    if (!event_ptr)
        throw (null);
    
    //RTTI, check if the event is a shopping event
    shopping * shopping_ptr {dynamic_cast <shopping *> (event_ptr)};

    if (shopping_ptr)
        return shopping_ptr->add_ingredients();
    else
        throw (invalid);

    return 0;
}

//This is the function to clear the data specific to the event type
//Argument: none
//Return: int, 1 for success, 0 for failure
int L_node::delete_data()
{
    null_event_ptr null;
    
    if (!event_ptr)
        throw (null);

    return event_ptr->delete_event();
}

/*LLL*/
//Default constructor
LLL::LLL():head(nullptr)
{
}

//Destructor
LLL::~LLL()
{
    if (head)
        remove_all();
}

//This is the wrapper function to remove all nodes in LLL
//Argument: none
//Return: void
void LLL::remove_all()
{
    null_ptr null;

    if (!head)
        throw (null);

    remove_all(head);
}

//This is the recursive function to remove all nodes in LLL
//Argument: none
//Return: void
void LLL::remove_all(L_node_ptr & head)
{
    //error_deleting_node error;

    if (!head) return;

    remove_all(head->get_next());
    
    //Delete and deallocate event_ptr
    /*
    if (head->get_event())
    {
        if (!head->get_event()->delete_event())
            throw (error);
        //delete head->get_event();
        head->set_event(nullptr);
    }
    */

    head.reset();
}

//This is the wrapper function to find a match in the event name and delete the node
//Arguments: string and L_node_ptr to head
//Return: int, 1 for success, 0 for failure (no match)
int LLL::remove(const string & name)
{
    null_head_ptr null;

    if (!head)
        throw (null);
    
    //if (!head || name.empty()) return 0; //empty search name, use exception handling?

    return remove(name, head);
}

//This is the recursive function to find a match in the event name and delete the node
//Arguments: string and L_node_ptr to head
//Return: int, 1 for success, 0 for failure (no match)
int LLL::remove(const string & name, L_node_ptr & head)
{
    if (!head) return 0;

    if (head->get_event()->get_name() == name)
    {
        unique_ptr <L_node> hold = move(head->get_next()); //hold on to next
        head.reset();
        head = move(hold);
        return 1;
    }
    
    return remove(name, head->get_next());
}

//Copy constructor
LLL::LLL(const LLL & src):head(nullptr)
{
    if (src.head)
        copy(head, src.head);
}

//Assignment operator
LLL & LLL::operator=(const LLL & src)
{
    if (this == &src)
        return *this;
    
    if (head)
        remove_all(); //delete data in LLL

    copy(head, src.head);

    return *this;
}

//This is the function to return the L_node_ptr head of the LLL object
//Return: L_node_ptr head
//Argument: none
typename LLL::L_node_ptr & LLL::get_head()
{
    return head;
}

//This is the copy function to copy all nodes of one LLL to another
//Argument: L_node_ptr to dest and src
//Return: void
void LLL::copy(typename LLL::L_node_ptr & dest, const typename LLL::L_node_ptr & src)
{
    if (!src)
    {
        dest.reset();
        return;
    }
    
    unique_ptr <L_node> temp (new L_node(*src)); //use the L_node copy constructor
    dest = move(temp);

    copy(dest->get_next(), src->get_next());
}

//This is the wrapper function to insert a new node into the LLL
//Argument: event pointer
//Return: int, 1 for success, 0 for failure
int LLL::insert(/*base_event_ptr*/ event * new_event) //take in an event reference instead?
{
    /*
    null_event_ptr null;
    
    if (!new_event)
        throw (null);
    */

    //if (!new_event) return 0;

    return insert(new_event, head);
}

//This is the recursive function to insert a new node into the LLL
//Argument: event pointer
//Return: int, 1 for success, 0 for failure
int LLL::insert(/*base_event_ptr*/ event * new_event, L_node_ptr & head)
{
    if (!head)
    {
        unique_ptr <L_node> temp (new L_node); //can also write a constructor with event ptr arg and use it here
        temp->set_event(new_event); //set the event_ptr to new event
        head = move(temp);

        return 1;
    }

    return insert(new_event, head->get_next());
}

//This is the wrapper function to display all nodes in a LLL
//Argument: event pointer
//Return: int, 1 for success, 0 for failure
int LLL::display_all() const
{
    null_head_ptr null;

    if (!head)
        throw (null);
    
    //if (!head) return 0;

    return display_all(head);
}

//This is the recursive function to display all nodes in a LLL
//Argument: event pointer
//Return: int, 1 for success, 0 for failure
int LLL::display_all(const L_node_ptr & head) const
{
    if (!head) return 1;
    
    try
    {
        head->display();
    }
    catch (null_event_ptr null)
    {
        cout << null.msg << endl;
    }
    catch (no_visit_data error)
    {
        cout << error.msg << endl;
    }
    catch (no_shopping_data error)
    {
        cout << error.msg << endl;
    }
    catch (no_meeting_data error)
    {
        cout << error.msg << endl;
    }
    catch (no_event_data error)
    {
        cout << error.msg << endl;
    }
    
    return display_all(head->get_next());
}
        
//This is the wrapper function to find a match in the event name and display its info
//Arguments: string and L_node_ptr to head
//Return: int, 1 for success, 0 for failure (no match)
int LLL::display(const string & name) const
{
    //empty_string empty;
    null_head_ptr null;

    if (!head)
        throw (null);

    //if (name.empty())
        //throw (empty);

    //if (!head || name.empty()) return 0; //empty search name, use exception handling?

    return display(name, head);
}

//This is the recursive function to find a match in the event name and display its info
//Arguments: string and L_node_ptr to head
//Return: int, 1 for success, 0 for failure (no match)
int LLL::display(const string & name, const L_node_ptr & head) const
{
    if (!head) return 0; //no match

    if (head->get_event()->get_name() == name)
    {
        try
        {
            head->display();
            return 1;
        }
        catch (null_event_ptr null)
        {
            cout << null.msg << endl;
        }
        catch (no_visit_data error)
        {
            cout << error.msg << endl;
        }
        catch (no_shopping_data error)
        {
            cout << error.msg << endl;
        }
        catch (no_meeting_data error)
        {
            cout << error.msg << endl;
        }
        catch (no_event_data error)
        {
            cout << error.msg << endl;
        }
        return 0;
    }
    return display(name, head->get_next());
}

//This is the wrapper function to add ingredients to shopping list of a shopping event
//Argument: string event name
//Return: int, 1 for success, 0 for failure
int LLL::add_ingredients(const string & name)
{
    null_head_ptr null;

    if (!head)
        throw (null);

    return add_ingredients(name, head);
}

//This is the recursive function to add ingredients to shopping list of a shopping event
//Argument: string event name and L_node_ptr head to LLL
//Return: int, 1 for success, 0 for failure
int LLL::add_ingredients(const string & name, const L_node_ptr & head)
{
    int count {0};

    if (!head) return 0; //no match

    if (head->get_event()->get_name() == name)
    {
        try
        {
            count += head->add_ingredients();
        }
        catch (null_event_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }
        catch (not_shopping_event invalid)
        {
            //cout << invalid.msg << endl;
            throw (invalid);
        }
        return count;
    }
    
    count += add_ingredients(name, head->get_next());

    return count;
}

//This is the wrapper function to delete data that is specific to the event type
//Argument: string event name
//Return: int, 1 for success, 0 for failure
int LLL::delete_data(const string & name)
{
    null_head_ptr null;

    if (!head)
        throw (null);

    return delete_data(name, head);
}

//This is the recursive function to delete data that is specific to the event type
//Argument: string event name and L_node_ptr head to LLL
//Return: int, 1 for success, 0 for failure
int LLL::delete_data(const string & name, const L_node_ptr & head)
{
    int count {0};

    if (!head) return 0; //no match

    if (head->get_event()->get_name() == name)
    {
        try
        {
            count += head->delete_data();
        }
        catch (null_event_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }
        return count;
    }
    
    count += delete_data(name, head->get_next());

    return count;
}
