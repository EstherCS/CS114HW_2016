#ifndef LIST_NODE_H
#define LIST_NODE_H

template< typename T > class list;   // forward declare
template< typename T > class ListIterator; // forward declare
template< typename T > class ReverseListIterator; // forward declare

// ListNode class template definition
template< typename T >
class ListNode
{
   template< typename T > friend class list;
   template< typename T > friend class ListIterator;
   template< typename T > friend class ReverseListIterator;
private:
   ListNode *llink;
   T data;
   ListNode *rlink;
}; // end class template ListNode

#endif


#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

// ListIterator class template definition
template< typename T >
class ListIterator
{
   template< typename T > friend class list;
public:
   ListIterator( ListNode< T > *p = 0 ) // default constructor
      : ptr( p )
   {
   }

   ListIterator( const ListIterator &iteratorToCopy ) // copy constructor
      : ptr( iteratorToCopy.ptr )
   {
   }

   ~ListIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const ListIterator &operator=( const ListIterator &right )
   {
      if( &right != this ) // avoid self-assignment
         ptr = right.ptr;
      return *this; // enables x = y = z, for example
   }

   T& operator*() const // dereferencing operator
   {
      return ptr->data;
   }

   ListIterator& operator++() // prefix increment operator
   {
      ptr = ptr->llink;
      return *this;
   }

   ListIterator& operator--() // prefix decrement operator
   {
      ptr = ptr->rlink;
      return *this;
   }

   bool operator==( const ListIterator &right ) const // equal to
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListIterator &right ) const // not equal to
   {
      return ptr != right.ptr;
   }

private:
   ListNode< T > *ptr; // keep a pointer to list
}; // end class template ListIterator

#endif


#ifndef REVERSE_LIST_ITERATOR_H
#define REVERSE_LIST_ITERATOR_H

// ReverseListIterator class template definition
template< typename T >
class ReverseListIterator : public ListIterator< T >
{
   template< typename U > friend class List;
public:
   ReverseListIterator( ListNode< T > *p = 0 ) // default constructor
      : ListIterator( p )
   {
   }

   ReverseListIterator( const ReverseListIterator &iteratorToCopy ) // copy constructor
      : ListIterator( iteratorToCopy )
   {
   }

   ~ReverseListIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const ReverseListIterator &operator=( const ReverseListIterator &right )
   {
      ListIterator< T >::operator=( right );
      return *this; // enables x = y = z, for example
   }

   ReverseListIterator& operator++() // prefix increment operator
   {
      ListIterator< T >::operator--();
      return *this;
   }

   ReverseListIterator& operator--() // prefix decrement operator
   {
      ListIterator< T >::operator++();
      return *this;
   }
}; // end class template ReverseListIterator

#endif


#ifndef LIST_H
#define LIST_H

// list class template definition
template< typename T >
class list
{
public:
   typedef ListIterator< T > iterator;
   typedef ReverseListIterator< T > reverse_iterator;

   list( unsigned int n = 0 ); // Constructs an empty list container, with no elements.

   // Constructs a list container with a copy of each of the elements in listToCopy.
   list( const list< T > &listToCopy );

   // Destroys all list container elements, and deallocates all the storage allocated by the list container.
   ~list();

   // Copies all the elements from "right" into the list container 
   const list &operator=( const list &right );

   bool operator==( const list &right ) const;

   bool operator!=( const list &right ) const;

   iterator begin() const; // Returns a pointer pointing to the first element in the list container.

   iterator end() const; // Returns an pointer referring to the past-the-end element in the list container.

   reverse_iterator rbegin() const; // Returns a pointer pointing to the last element in the list container
                                    // (i.e., its reverse beginning).

   reverse_iterator rend() const; // Returns a pointer pointing to the theoretical element preceding
                                  // the first element in the list container (which is considered its reverse end).

   void clear(); // Removes all elements from the list container (which are destroyed).

   unsigned int size() const; // Returns the number of elements in the list container.

   // Resizes the list container so that it contains n elements.
   // If n is smaller than the current list container size,
   // the content is reduced to its first n elements, removing those beyond.
   // If n is greater than the current list container size,
   // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
   void resize( unsigned int n );

private:
   unsigned int mySize;       // the number of elements in the list container
   ListNode< T > *head; // pointing to the past-the-end element in the list container
}; // end class template list

#endif


// Constructs an empty list container, with no elements.
template< typename T >
list< T >::list( unsigned int n )
   :mySize( n )
{
   head = new ListNode< T >;
   head->data = T();
   head->rlink = head->llink = head;

   ListNode< T > *newNode = nullptr;
   if( n > 0 )
   {
      for( unsigned int i = 0; i < n; i++ )
      {
         newNode = new ListNode< T >;
         newNode->data = T();
         newNode->rlink = head->rlink;
         head->rlink->llink = newNode;
         head->rlink = newNode;
      }
      newNode->llink = head;
   }
}

// Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
list< T >::~list()
{
   clear();
   delete head;
}

template< typename T >
bool list< T >::operator!=( const list< T > &right ) const
{
   return !( *this == right );
}

template< typename T >
ListIterator< T > list< T >::begin() const
{
   return iterator( head->llink );
}

template< typename T >
ListIterator< T > list< T >::end() const
{
   return iterator( head );
}

template< typename T >
ReverseListIterator< T > list< T >::rbegin() const
{
   return reverse_iterator( head->rlink );
}

template< typename T >
ReverseListIterator< T > list< T >::rend() const
{
   return reverse_iterator( head );
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void list< T >::clear()
{
   if( mySize != 0 ) // the list is not empty
   {
      while( head->llink != head )
      {
         head->llink = head->llink->llink;
         delete head->llink->rlink;
      }

      head->rlink = head;
      mySize = 0;
   }
}

template< typename T >
unsigned int list< T >::size() const
{
   return mySize;
}

template< typename T >
list< T >::list(const list< T > &listToCopy)
{
	mySize = listToCopy.mySize;
	head = new ListNode< T >;                     // 創造新的 head
	head->data = T();                             // data 放入 0
	head->rlink = head->llink = head;             // 將 rlink llink 皆指回自己

	ListIterator< T > it1 = listToCopy.begin();   // it1 是 class
	ListNode< T > *newNode = nullptr;
	if (mySize > 0)
	{
		for (unsigned int i = 0; i < mySize; i++, ++it1)
		{
			newNode = new ListNode< T >;           // 新的 node  
			newNode->data = *it1;                  // data 放入舊的值
			newNode->rlink = head->rlink;          // (1)
			head->rlink->llink = newNode;          // (2)
			head->rlink = newNode;                 // (3)
		}
		newNode->llink = head;                     // (4)
	}
	/* (1)
	                         ---------------------- ┐
	                         |                      ↓
	       ----------  (1)  ----------       ----------
	(new)  |  | 9|  | ----->|  | 5|  |<----->|  | 0|  | (head)
           ----------       ----------       ----------
                             ^                       |
	                        └------------------------
	*/
	/* (2)

	       ----------  (2)  ----------       ----------
	(new)  |  | 9|  |<----->|  | 5|  |<----->|  | 0|  | (head)
	       ----------       ----------       ----------
	                         ^                       |
	                        └------------------------
	*/
	/* (3)

	       ----------       ----------       ----------
	(new)  |  |  |  |<----->|  |  |  |<----->|  | 0|  | (head)
	       ----------       ----------       ----------
	        ^                                        |  (3)
	       └-----------------------------------------
	*/
	/* (4)
	         --------------------------------------- ┐
	        |                                       ↓  (4)
	       ----------       ----------       ----------
	(new)  |  |  |  |<----->|  |  |  |<----->|  | 0|  | (head)
	       ----------       ----------       ----------
	        ^                                        |
	       └-----------------------------------------
	*/
}

template< typename T >
const list< T > &list< T >::operator=(const list< T > &right)
{
	if (&right != this)                // 不相等時才做
	{
		ListNode< T > *rightptr = right.head->llink;
		if (mySize == right.mySize)    // nodes 數量一樣，直接複製 
		{
			ListNode< T > *nowptr = head->llink;
			for (int i = 0; i < mySize; i++, rightptr = rightptr->llink, nowptr = nowptr->llink)
			{
				nowptr->data = rightptr->data;
			}
		}
		else                           // 砍掉舊的，創建新的
		{
			clear();
			mySize = right.mySize;
			head = new ListNode< T >;
			head->data = T();
			head->rlink = head->llink = head;

			ListNode< T > *newnode = nullptr;
			if (mySize > 0)
			{
				for (unsigned int i = 0; i < mySize; i++, rightptr = rightptr->llink)
				{
					newnode = new ListNode< T >;
					newnode->data = rightptr->data;
					newnode->rlink = head->rlink;
					head->rlink->llink = newnode;
					head->rlink = newnode;
				}
				newnode->llink = head;
			}
		}
	}
	return *this;
}

template< typename T >
bool list< T >::operator==(const list< T > &right) const
{
	if (mySize != right.mySize)
		return false;
	else
	{
		ListIterator< T > it1 = begin();
		ListIterator< T > it2 = right.begin();
		for (; it1 != end(); it1++, it2++)
		{
			if (*it1 != *it2)
				return false;
		}
	}
	return true;
}
template< typename T >
void list< T >::resize(unsigned int n)
{
	if (n == mySize)
		return;
	else if (n < mySize)                                  // 大變小 
	{
		// 將多餘的刪除
		for (int i = n; i < mySize; i++)
		{
			head->rlink = head->rlink->rlink;             // (1) -> (2)
			delete head->rlink->llink;                    // (XX)
			head->rlink->llink = head;                    // (3)
		}
		mySize = n;
	}
	else                                                  // 小變大
	{
		ListNode< T > *newNode = nullptr;
		for (unsigned int i = mySize; i < n; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = head->rlink;
			head->rlink->llink = newNode;
			head->rlink = newNode;
		}
		newNode->llink = head;
	}
	mySize = n;
	/*

	----------   (XX)  ----------         ----------
	|  |  |  | <-----> |  |  |  | <-----> |  |  |  |  (head)
	----------         ----------         ----------
	 ^                                            |      (1)
	 └--------------------------------------------


	----------         ----------
	|  |  |  | <-----> |  |  |  |  (head)
	----------         ----------
	 ^                         |    (2)
	└-------------------------


	 ------------------------- ┐
	|                         ↓   (3)
	----------         ----------
	|  |  |  | <-----> |  |  |  |  (head)
	----------         ----------
	 ^                        |
	└-------------------------
	*/
}