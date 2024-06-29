//FILE: sequence.cpp
//Author: Timothy Tong
//Contributions: Implemented majority of functions in the file.
//
//IMPLEMENTS: The functions of the sequence class (see sequence.h for documentation)
//INVARIANT for the sequence class:
//Items stored in sequence order, in a forward linked list.
//head_ptr points to 1st item in sequence, tail_ptr points to last item.
//many_nodes contains the total number of nodes in the linked list.
//For an empty sequence, all pointers are null, and many_nodes is 0. For a sequence with 1 item, cursor points at head = tail, and precursor is null. Otherwise, cursor points to current item in sequence, precursor points to item before current item. Precursor is null when cursor is head.

#include <cassert>
#include "sequence.h"
namespace coen79_lab6
{

// CONSTRUCTOR for the sequence class:
// Postcondition: Initializes an empty sequence.
	sequence::sequence( )
	{
		//default state 
    		head_ptr = NULL;
    		tail_ptr = NULL;
    		cursor = NULL;
    		precursor = NULL;
    		many_nodes = 0;
	}

// Postcondition: Creates a new sequence as a copy of source.
        sequence::sequence(const sequence& source)
	{
		//default state 
    		head_ptr = NULL;
    		tail_ptr = NULL;
    		cursor = NULL;
    		precursor = NULL;
    		many_nodes = 0;
		*this = source; //assigns src to seq
	}
	
// DESTRUCTOR for the sequence class:
// Postcondition: Deallocates dynamic memory for sequence.
	sequence::~sequence( )
	{
		list_clear(head_ptr); //deallocates nodes
		//resets seq
    		head_ptr = NULL;
    		tail_ptr = NULL;
    		cursor = NULL;
    		precursor = NULL;
    		many_nodes = 0;
	}
	
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
// Postcondition: Modify precursor and cursor so that 1st item in the sequence is the current item (no current item if empty sequence)
	void sequence::start( )
	{
		precursor = NULL; //if empty or not, precursor is null
		cursor = head_ptr; //if empty, cursor is null, otherwise is head
	}

// Postcondition: Modify precursor and cursor so that last item in the sequence is the current item (no current item if empty sequence)
	void sequence::end( )
	{
		if (tail_ptr == head_ptr) //if 1 item or seq is empty 
		{
			cursor = tail_ptr; //cursor is tail
			precursor = NULL; //precursor is null
		}
		else //if seq more than 1 item
		{
			precursor = list_locate(head_ptr, many_nodes-1); //precursor is 1 before tail
			cursor = tail_ptr; //cursor is tail
		}
	}

// Precondition: is_item is true.
// Postcondition: Next item is now the current item. If original current item was the last item, now there is no current item. 
// Assumption is advance can iterate past tail ptr: cursor = NULL, precursor = tail_ptr
   	void sequence::advance( )
	{
		assert(is_item());
		precursor = cursor; //incr precursor
		cursor = cursor->link(); //incr current
	}

// Postcondition: Insert entry before current item. If no current item, entry is inserted at sequence start. Current item is inserted item.
// Allocates dynamic memory for list insert.
	void sequence::insert(const sequence::value_type& entry)
	{
		if ((precursor == NULL) || !is_item()) //if current item is head or no valid current item
		{
			list_head_insert(head_ptr, entry); //insert new head
			precursor = NULL; //precursor is null
			cursor = head_ptr; //cursor is head
			if (tail_ptr == NULL) //if seq was empty
				tail_ptr = head_ptr; //has 1 item
		}
		else //if current item not head and is valid
		{
			list_insert(precursor, entry); //new entry before cursor
			cursor = precursor->link(); //update cursor
		}
		many_nodes++;
	}

// Postcondition: Insert entry after current item. If no current item, entry is inserted at sequence end. Current item is inserted item.
// Allocates dynamic memory for list insert.
	void sequence::attach(const sequence::value_type& entry)
	{
		if (tail_ptr == NULL) //if sequence is empty
		{
			list_head_insert(head_ptr, entry); //insert new head
			precursor = NULL; //precursor is null
			tail_ptr = cursor = head_ptr; //cursor is head, 1 item inserted
		}
		else if (!is_item()) //if no valid current item
		{
			list_insert(tail_ptr, entry); //new entry after tail
			precursor = tail_ptr; //precursor at original tail
			cursor = tail_ptr = tail_ptr->link(); //incr tail, cursor at new tail
		}
		else //if nonempty sequence and valid current item
		{
			list_insert(cursor, entry); //insert entry after current
			if (tail_ptr == cursor) //if current is tail
				tail_ptr = tail_ptr->link(); //incr tail
			precursor = cursor; //precursor at original current
			cursor = cursor->link(); //incr current
		}
		many_nodes++;
	}

// Postcondition: Assigns a copy of source to sequence object.
// Allocates dynamic memory for list copy and list piece.
        void sequence::operator =(const sequence& source)
	{
		if (&source == this) //check for self-assignment
			return;
		if (!source.is_item()) //if invalid current item
		{
			list_copy(source.head_ptr, head_ptr, tail_ptr); //copy list
			precursor = cursor = NULL; //current is null
		}
		else if (source.cursor == source.head_ptr) //if src current is src head
		{
			list_copy(source.head_ptr, head_ptr, tail_ptr); //copy list
			precursor = NULL; //precursor is null
			cursor = head_ptr; //current is head
		}
		else //if src current is after 1st item
		{
			list_piece(source.head_ptr, source.cursor, head_ptr, precursor); //list copy head to precursor
			list_piece(source.cursor, NULL, cursor, tail_ptr); //list copy cursor to tail
			precursor->set_link(cursor); //link precursor to cursor
		}
		many_nodes = source.many_nodes;
	}

// Precondition: is_item is true.
// Postcondition: Removes current item, and makes next item, if it exists, new current item.
	void sequence::remove_current( )
	{
		assert(is_item());
		if (cursor == head_ptr) //if current item is head
		{
			list_head_remove(head_ptr); //remove head
			precursor = NULL; //update precursor
			if (head_ptr == tail_ptr) //if was 1 item
			{
				//reset sequence
    				head_ptr = NULL;
    				tail_ptr = NULL;
    				many_nodes = 0;
			}
			cursor = head_ptr; //if more than 1 item, current is head, otherwise is NULL
		}
		else //if current not 1st item, can be tail, or neither head nor tail
		{
			list_remove(precursor); //remove current
			if (cursor == tail_ptr) //if current item was tail (!= head)
			{
				tail_ptr = precursor; //decr tail
			}
			cursor = precursor->link(); //update current, is NULL if current was tail
		}
		many_nodes--;
	}

// CONSTANT MEMBER FUNCTIONS for the sequence class:
// Postcondition: Returns number of sequence items.
	sequence::size_type sequence::size( ) const
	{
		return many_nodes; //node count
	}

// Postcondition: Returns true if there is a valid, accessible current item, otherwise returns false.
	bool sequence::is_item( ) const
	{
		return cursor != NULL; //valid if current not null
	}

// Precondition: is_item is true.
// Postcondition: Returns sequence current item.
	sequence::value_type sequence::current( ) const
	{
		assert(is_item());
		return cursor->data();
	}
}
