#ifndef LIST_H
#define LIST_H

#include "ListNode.h" // include definition of class template ListNode

// List class template definition
template< typename T >
class List
{
public:
   typedef ListNode< T >* iterator;
   typedef ListNode< T >* reverse_iterator;

   List( unsigned int n = 0 ); // Constructs an empty list container, with no elements.

   // Constructs a list container with a copy of each of the elements in listToCopy.
   List( const List< T > &listToCopy );

   // Destroys all linked list elements, and deallocates all the storage allocated by the list container.
   ~List();

   // Copies all the elements from "right" into the list container 
   const List< T > &operator=( const List< T > &right );

   bool operator==( const List< T > &right ) const;

   bool operator!=( const List< T > &right ) const;

   iterator begin() const; // Returns a pointer pointing to the first element in the list container.

   iterator end() const; // Returns an pointer referring to the past-the-end element in the list container.

   reverse_iterator rbegin() const; // Returns a pointer pointing to the last element in the list container
                                    // (i.e., its reverse beginning).

   reverse_iterator rend() const; // Returns a pointer pointing to the theoretical element preceding
                                  // the first element in the list container (which is considered its reverse end).

   void clear(); // Removes all elements from the list container (which are destroyed).

   unsigned int getSize() const; // Returns the number of elements in the list container.

   // Resizes the list container so that it contains n elements.
   // If n is smaller than the current list container size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current list container size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   void resize( unsigned int n );

private:
   unsigned int size;       // the number of elements in the list container
   ListNode< T > *sentinal; // pointing to the past-the-end element in the list container
}; // end class template List

#endif