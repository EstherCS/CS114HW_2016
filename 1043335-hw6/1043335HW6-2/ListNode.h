#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
using std::ostream;

template< typename T > class List;   // forward declare
template< typename T > class HugeInteger;   // forward declare

// ListNode class template definition
template< typename T >
class ListNode
{
   template< typename U > friend class List;
   template< typename U > friend class HugeInteger;
   template< typename U > friend ostream &operator<<( ostream &, HugeInteger< U > & );
private:
   ListNode *llink;
   T data;
   ListNode *rlink;
}; // end class template ListNode

#endif