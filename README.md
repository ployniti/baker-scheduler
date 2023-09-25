# baker-scheduler
This project explores dynamic binding in a program with a self-similar hierarchy, using a binary search tree of linear linked lists as the primary data structure.

# Specification
Implement a scheduler program that sorts data in a non-linear way so that users won’t have to click through their program multiple times to, say, 
find all the events at a particular location or with a particular person.

# Hierarchy Design

<p align="center">
  <img width="1824" alt="uml" src="https://github.com/ployniti/baker-scheduler/assets/145937137/b0daee98-ae06-41b3-9f34-dd929b89fe1b">
</p >

I decided to write a scheduler program for a baker who frequently has client meetings to discuss catering, visit their bakeries, and go shopping for ingredients for their baking. 
As a result, derived from the base event class, I have a client_meeting, bakery_visit, and shopping classes in my design.

There is a hierarchy with a self-similar interface between the derived classes so that dynamic binding can be leveraged.

I have a base event class be the hub where all the virtual methods reside. 
I have one pure virtual function with no code body, `delete_data`, in the event base class, making it an abstract base class. 
My base event class did have data that it manages; data that are common amongst the different event types such as event’s `name`, `starting time`, `ending time`, and `location`, 
so I did implement most of the virtual functions for my event class to do so. The three virtual functions that I chose for the classes were `add_event`, `display_event`, and `delete_event`. 
The `add_event` function prompts users to input information about their event. Each derived class calls the base class’s function as well as having unique prompts for input specific to their event type. 
For example, the bakery visit has a duty information while the shopping event has a shopping list the user can add to. 
The `display_event` displays the events’ data and the `delete_event` clears the event type specific data.

The one function that requires RTTI for my program was a function to add to the ingredients list of the shopping class so this function is not virtual and only exists in the shopping class. 
Consequently, I needed to do RTTI to make sure that the event the user is searching for is a shopping event before we can call the function for the user to input ingredients into their list. 
I used a vector for the `shopping_list` data member.

For the data structures, I chose to implement a binary search tree where each node has a linear linked list. 
I had a `L_node` class and a LLL class to implement the linear linked list. Each `L_node` has a base class event pointer which can point to a derived object, upcasting, to leverage dynamic binding. 
My LLL class then has a `L_node` pointer head to point to the beginning of the LLL. I then had a `T_node` class and a BST class to implement the binary search tree. 
Each `T_node` class has a LLL object, events, and a string for the location of where those events are; this is the key for sorting the data in my schedule/table. 
The BST class then held a `T_node` pointer root to the root of the tree.

# Compilation Instructions
Run `make` in terminal the directory created after unzipping the tar.gz file. 
This will generate a `run` executable to run the program.

# Run Instructions
Run `./run` in terminal.
