//This is the code for the methods in the T_node and BST classes.

#include "BST.h"

/*T_NODE*/
//Default constructor
T_node::T_node():left(nullptr), right(nullptr)
{
}

//Destructor
T_node::~T_node()
{
    if (has_events()) //LLL is not empty
        events.remove_all();

    if (!location.empty())
        location.clear();

    if (left)
        left.reset();

    if (right)
        right.reset();
}

//Copy constructor
T_node::T_node(const T_node & src):left(nullptr), right(nullptr)
{
    copy(src);
}

//Assignment operator
T_node & T_node::operator=(const T_node & src)
{
    if (this == &src)
        return *this;

    //Delete data in T_node
    if (has_events()) //LLL is not empty
        events.remove_all();

    if (!location.empty())
        location.clear();

    if (left)
        left.reset();

    if (right)
        right.reset();

    copy(src);

    return *this;
}
       
//This is the copy function to copy the T_node's data (LLL and string location) from another T_node
//Argument: T_node object reference
//Return: void
void T_node::copy(const T_node & src)
{
    location = src.location;

    //Copy the events LLL from src
    events = src.events;
}

//This is the function that checks if the T_node has any events
//Argument: none
//Return: true or false
bool T_node::has_events()
{
    if (events.get_head())
        return true;

    return false;
}

//This is the function to return the left pointer
//Argument: none
//Return: T_node_ptr reference
typename T_node::T_node_ptr & T_node::get_left()
{
    return left;
}

//This is the function to return the right pointer
//Argument: none
//Return: T_node_ptr reference
typename T_node::T_node_ptr & T_node::get_right()
{
    return right;
}

//This is the function to set the node's left pointer
//Argument: left T_node_ptr
//Return: void
void T_node::set_left(typename T_node::T_node_ptr new_left)
{
    if (!new_left)
    {
        left.reset();
        return;
    }

    left = move(new_left);
}

//This is the function to set the node's right pointer
//Argument: right T_node_ptr
//Return: void
void T_node::set_right(typename T_node::T_node_ptr new_right)
{
    if (!new_right) //new_right is nullptr
    {
        right.reset();
        return;
    }

    right = move(new_right);
}

//This is the function to add an event to the events LLL
//Argument: event ptr
//Return: int, 1 for success, 0 for failure
int T_node::add_event(event * new_event)
{
    return events.insert(new_event); //using LLL insert function
}

//This is the function to set the location string in a T_node
//Argument: a string object
//Return: int, 1 for success, 0 for failure
int T_node::set_location(const string & a_location)
{
    location = a_location;
    return 1;
}

//This is the function that returns the location key at the T_node
//Argument: none
//Return: string
string & T_node::get_location()
{
    return location;
}

//This is the function to display all events in a T_node
//Argument: none
//Return: int, 1 for success, 0 for failure
int T_node::display_all() const
{
    int count {0};

    try
    {
        count += events.display_all();  
    }
    catch (null_head_ptr null)
    {
        cout << null.msg << endl;
        cout << "No events at this location." << endl << endl;
    }

    return count;
}

//This is the function to display an event in a T_node
//Argument: name string
//Return: int, 1 for success, 0 for failure
int T_node::display(const string & name) const
{
    int count {0};

    try
    {
        count += events.display(name);
    }
    catch (null_head_ptr null)
    {
        cout << null.msg << endl;
        cout << "No events at this location." << endl << endl;
    }

    return count;
}

//This is the function to remove an event in the events LLL in a T_node
//Argument: name string
//Return: int, 1 for success, 0 for failure
int T_node::remove_event(const string & name)
{
    int count {0};

    try
    {
        count += events.remove(name); 
    }
    catch (null_head_ptr null)
    {
        cout << null.msg << endl;
        cout << "No events at this location." << endl << endl;
    }
    
    return count;
}

//This is the function to add ingredients to shopping list of a shopping event
//Argument: string event name
//Return: int, 1 for success, 0 for failure
int T_node::add_ingredients(const string & name)
{
    int count {0};

    try
    {
        count += events.add_ingredients(name);
    }
    catch (not_shopping_event invalid)
    {
        throw (invalid);
    }
    catch (null_event_ptr null)
    {
        throw (null);
    }
    catch (null_head_ptr null)
    {
        throw (null);
    }

    return count;
}

//This is the function to clear the data specific to the event type
//Argument: string event name
//Return: int, 1 for success, 0 for failure
int T_node::delete_data(const string & name)
{
    int count {0};

    try
    {
        count += events.delete_data(name);
    }
    catch (null_event_ptr null)
    {
        throw (null);
    }
    catch (null_head_ptr null)
    {
        throw (null);
    }

    return count;
}

/*BST*/
//Default constructor
BST::BST():root(nullptr)
{
}

//Destructor
BST::~BST()
{
    if (root)
        remove_all();
}

//This is the wrapper function to remove all nodes in BST
//Argument: none
//Return: void
void BST::remove_all()
{
    null_root_ptr null;

    if (!root)
        throw (null);

    remove_all(root);
}

//This is the recursive function to remove all nodes in BST
//Argument: none
//Return: void
void BST::remove_all(typename T_node::T_node_ptr & root)
{
    if (!root) return;

    remove_all(root->get_left());
    remove_all(root->get_right());

    root.reset();
}

//Copy constructor
BST::BST(const BST & src):root(nullptr)
{
    if (src.root)
        copy(root, src.root);
}

//Assignment operator
BST & BST::operator=(const BST & src)
{
    if (this == &src)
        return *this;
    
    if (root)
        remove_all();

    copy(root, src.root);
    
    return *this;
}

//This is the copy function to copy all nodes of one BST to another
//Arguments: T_node_ptr to dest and src
//Return: void
void BST::copy(T_node_ptr & dest, const T_node_ptr & src)
{
    if (!src)
    {
        dest.reset();
        return;
    }

    unique_ptr <T_node> temp (new T_node(*src)); //use T_node copy constructor
    dest = move(temp);

    copy(dest->get_left(), src->get_left());
    copy(dest->get_right(), src->get_right());
}

//This is the wrapper function to insert a node in the BST, setting the location key and starting a LLL in the node
//Argument: event pointer
//Return: int, 1 for success, 0 for failure
int BST::insert(/*base_event_ptr &*/ event * new_event /*, const string & location*/)
{
    null_event_ptr null;
    empty_location_string empty;
    int count {0};

    if (!new_event)
        throw (null);
    
    //Get the location of the new event, the key
    string location {new_event->get_location()};

    if (location.empty())
        throw (empty);
    
    if (!root) //empty tree
    {
        unique_ptr <T_node> temp (new T_node);
        count += temp->set_location(location); //set the key for that node
        count += temp->add_event(new_event);
        root = move(temp);

        return count;
    }

    return insert(new_event, location, root);
}

//This is the recursive function to insert a node in the BST, setting the location key and starting a LLL in the node
//Argument: event pointer, location string, and T_node_ptr root
//Return: int, 1 for success, 0 for failure
int BST::insert(/*base_event_ptr &*/ event * new_event, const string & location, T_node_ptr & root)
{
    int count {0};

    if (!root)
    {
        unique_ptr <T_node> temp (new T_node);
        count += temp->set_location(location); //set the key for that node
        count += temp->add_event(new_event);
        root = move(temp);

        return count;
    }

    //Find a match in location and add to the events LLL
    if (root->get_location() == location)
    {
        //unique_ptr <T_node> temp (new T_node);
        count += root->add_event(new_event);
        return count;
        //root = move(temp);
    }
    
    if (root->get_location() <= location) //(root->get_location().compare(location) < 0) //root's location is smaller
        count += insert(new_event, location, root->get_right());
    else //if (root->get_location().compare(location) > 0) //root's location is greater
        count += insert(new_event, location, root->get_left());
    
    return count;
}

//This is the wrapper function to display all events at a particular location
//Argument: location string, for searching the T_nodes
//Return: int, 1 for success, 0 for failure
int BST::display_all(const string & location) const
{
    null_root_ptr null;
    empty_location_string empty_location;

    if (!root)
        throw (null);
    
    if (location.empty())
        throw (empty_location);
    //if (!root) return 0;

    return display_all(location, root);
}

//This is the recursive function to display all events at a particular location
//Argument: location string and T_node_ptr root
//Return: int, 1 for success, 0 for failure
int BST::display_all(const string & location, const T_node_ptr & root) const
{
    int count {0};

    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        count += root->display_all();
        return count;
    }

    if (root->get_location() <= location) //(root->get_location().compare(location) < 0) //root's location is smaller
        count += display_all(location, root->get_right());
    else //if (root->get_location().compare(location) > 0) //root's location is greater
        count += display_all(location, root->get_left());

    return count;
}

//This is the wrapper function to find a match in the event name and location and display its info
//Arguments: name and location strings
//Return: int, 1 for success, 0 for failure (no match)
int BST::display(const string & name, const string & location) const
{
    empty_name_string empty_name;
    empty_location_string empty_location;
    empty_string empty;
    null_root_ptr null;

    if (!root)
        throw (null);
    
    if (name.empty() && location.empty())
        throw (empty);
    else if (name.empty())
        throw (empty_name);
    else if (location.empty())
        throw (empty_location);

    return display(name, location, root);
}

//This is the recursive function to find a match in the event name and location and display its info
//Arguments: name and location strings and T_node_ptr to root
//Return: int, 1 for success, 0 for failure (no match)
int BST::display(const string & name, const string & location, const T_node_ptr & root) const
{
    int count {0};
    
    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        count += root->display(name);
        return count;
    }

    if (root->get_location() <= location) //root's location is smaller
        count += display(name, location, root->get_right());
    else //root's location is greater
        count += display(name, location, root->get_left());

    return count;
}

//This is the wrapper function to display all events in all nodes in the BST (inorder)
//Argument: none
//Return: int, 1 for success, 0 for failure
int BST::display_table() const
{
    null_root_ptr null;

    if (!root)
        throw (null);
   //if (!root) return 0;

   return display_table(root);
}

//This is the recursive function to display all events in all nodes in the BST (inorder)
//Argument: none
//Return: int, 1 for success, 0 for failure
int BST::display_table(const T_node_ptr & root) const
{
    if (!root) return 0;

    int count = display_table(root->get_left());

    count += root->display_all();

    count += display_table(root->get_right());

    return count;
}

//This is the wrapper function to remove an event in a particular T_node
//Argument: name and location strings, and T_node_ptr to root
//Return: int, 1 for success, 0 for failure (no match)
int BST::remove_event(const string & name, const string & location)
{
    empty_name_string empty_name;
    empty_location_string empty_location;
    empty_string empty;
    null_root_ptr null;

    if (!root)
        throw (null);
    
    if (name.empty() && location.empty())
        throw (empty);
    else if (name.empty())
        throw (empty_name);
    else if (location.empty())
        throw (empty_location);
    
    return remove_event(name, location, root);
}

//This is the recursive function to remove an event in a particular T_node
//Argument: name and location strings, and T_node_ptr to root
//Return: int, 1 for success, 0 for failure (no match)
int BST::remove_event(const string & name, const string & location, T_node_ptr & root)
{
    int count {0};
    
    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        count += root->remove_event(name);

        //If the LLL is empty after removal, we'd want to remove the T_node we're at
        if (!root->has_events())
            count += remove_location(location, root);

        return count;
    }

    if (root->get_location() <= location) //root's location is smaller
        count += remove_event(name, location, root->get_right());
    else //root's location is greater
        count += remove_event(name, location, root->get_left());

    return count;
}

//This is the wrapper function to remove a T_node at a particular location
//Argument: location string, to find the node
//Return: int, 1 for success, 0 for failure (no match)
int BST::remove_location(const string & location)
{
    null_root_ptr null;
    empty_location_string empty;

    if (!root)
        throw (null);
    
    if (location.empty())
        throw (empty);

    return remove_location(location, root);
}

//This is the recursive function to remove a T_node at a particular location
//Argument: location string, to find the node, and the T_node_ptr root
//Return: int, 1 for success, 0 for failure (no match)
int BST::remove_location(const string & location, T_node_ptr & root)
{
    int count {0};

    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        //Remove from a leaf
        if (!root->get_left() && !root->get_right())
            root.reset();

        //Has a left child
        else if (root->get_left() && !root->get_right())
        {
            unique_ptr <T_node> hold = move(root->get_left()); //hold on to left
            root.reset();
            root = move(hold);
        }
        
        //Has a left child
        else if (root->get_right() && !root->get_left())
        {
            unique_ptr <T_node> hold = move(root->get_right()); //hold on to right
            root.reset();
            root = move(hold);
        }

        //Has 2 children
        else
        {
            unique_ptr <T_node> current = move(root->get_right());

            //Right child has no left children, right child is IOS
            if (!current->get_left())
            {
                //Copy IOS data into root
                //unique_ptr <T_node> copy (new T_node(*current)); //use T_node copy constructor
                //root = move(copy);
                root->copy(*current); //copy data
                
                //Adopt
                root->get_right() = move(current->get_right());

                current.reset();
            }
            //Find IOS
            else
            {
                unique_ptr <T_node> parent;

                while (current->get_left())
                {
                    parent = move(current);
                    current = move(current->get_left());
                }

                //Copy IOS data into root
                unique_ptr <T_node> copy (new T_node(*current));
                root = move(copy);

                parent->get_left() = move(current->get_right());

                current.reset();
            }
        }
        return 1;
    }

    if (root->get_location() <= location) //root's location is smaller
        count += remove_location(location, root->get_right());
    else //root's location is greater
        count += remove_location(location, root->get_left());
    
    return count;
}

//This is the wrapper function to add ingredients to shopping list of a shopping event
//Arguments: string event name and location
//Return: int, 1 for success, 0 for failure
int BST::add_ingredients(const string & name, const string & location)
{
    empty_name_string empty_name;
    empty_location_string empty_location;
    empty_string empty;
    null_root_ptr null;

    if (!root)
        throw (null);
    
    if (name.empty() && location.empty())
        throw (empty);
    else if (name.empty())
        throw (empty_name);
    else if (location.empty())
        throw (empty_location);

    return add_ingredients(name, location, root);
}

//This is the recursive function to add ingredients to shopping list of a shopping event
//Arguments: string event name and location and T_node_ptr to root
//Return: int, 1 for success, 0 for failure
int BST::add_ingredients(const string & name, const string & location, const T_node_ptr & root)
{
    int count {0};
    
    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        try
        {
            count += root->add_ingredients(name);
        }
        catch (not_shopping_event invalid)
        {
            //cout << null.msg << endl;
            throw (invalid);
        }
        catch (null_event_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }
        catch (null_head_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }

        return count;
    }

    if (root->get_location() <= location) //root's location is smaller
        count += add_ingredients(name, location, root->get_right());
    else //root's location is greater
        count += add_ingredients(name, location, root->get_left());

    return count;
}

//This is the wrapper function to delete data that is specific to the event type
//Arguments: string event name and location
//Return: int, 1 for success, 0 for failure
int BST::delete_data(const string & name, const string & location)
{
    empty_name_string empty_name;
    empty_location_string empty_location;
    empty_string empty;
    null_root_ptr null;

    if (!root)
        throw (null);
    
    if (name.empty() && location.empty())
        throw (empty);
    else if (name.empty())
        throw (empty_name);
    else if (location.empty())
        throw (empty_location);

    return delete_data(name, location, root);
}

//This is the recursive function to delete data that is specific to the event type
//Arguments: string event name and location, and T_node_ptr root
//Return: int, 1 for success, 0 for failure
int BST::delete_data(const string & name, const string & location, const T_node_ptr & root)
{
    int count {0};
    
    if (!root) return 0; //no match in location

    if (root->get_location() == location)
    {
        try
        {
            count += root->delete_data(name);
        }
        catch (null_event_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }
        catch (null_head_ptr null)
        {
            //cout << null.msg << endl;
            throw (null);
        }

        return count;
    }

    if (root->get_location() <= location) //root's location is smaller
        count += delete_data(name, location, root->get_right());
    else //root's location is greater
        count += delete_data(name, location, root->get_left());

    return count;
}
