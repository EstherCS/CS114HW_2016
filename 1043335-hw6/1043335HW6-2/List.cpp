// Member-function definitions for class template List

#include "List.h" // include definition of class template List

// Constructs an empty list container, with no elements.
template< typename T >
List< T >::List(unsigned int n)
:size(n)
{
	sentinal = new ListNode< T >;
	sentinal->data = T();
	sentinal->rlink = sentinal->llink = sentinal;

	List< T >::iterator newNode = nullptr;
	if (n > 0)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = sentinal->rlink;
			sentinal->rlink->llink = newNode;
			sentinal->rlink = newNode;
		}
		newNode->llink = sentinal;
	}
}

// Destroys all list container elements, and deallocates all the storage allocated by the list container.
template< typename T >
List< T >::~List()
{
	clear();
}

template< typename T >
bool List< T >::operator!=(const List< T > &right) const
{
	return !(*this == right);
}

template< typename T >
ListNode< T >* List< T >::begin() const
{
	return sentinal->llink;
}

template< typename T >
ListNode< T >* List< T >::end() const
{
	return sentinal;
}

template< typename T >
ListNode< T >* List< T >::rbegin() const
{
	return sentinal->rlink;
}

template< typename T >
ListNode< T >* List< T >::rend() const
{
	return sentinal;
}

// Removes all elements from the list container (which are destroyed)
template< typename T >
void List< T >::clear()
{
	if (size != 0) // the list is not empty
	{
		while (sentinal->llink != sentinal)
		{
			sentinal->llink = sentinal->llink->llink;
			delete sentinal->llink->rlink;
		}

		sentinal->rlink = sentinal;
		size = 0;
	}
}

template< typename T >
unsigned int List< T >::getSize() const
{
	return size;
}

// Constructs a list container with a copy of each of the elements in listToCopy.
template< typename T >
List< T >::List(const List< T > &listToCopy)
{
	size = listToCopy.size;                           // 設定大小
	sentinal = new ListNode< T >;                     // 創造新的 sentinal
	sentinal->data = T();                             // data 放入 0
	sentinal->rlink = sentinal->llink = sentinal;     // 將 rlink llink 皆指回自己

	List< T >::iterator listCopy = listToCopy.begin();
	List< T >::iterator newnode = nullptr;
	for (unsigned int i = 0; i < size; i++)
	{
		newnode = new ListNode< T >;                  // 新的 node  
		newnode->data = listCopy->data;               // 將舊的 data 放入新的
		newnode->rlink = sentinal->rlink;             // (1)
		sentinal->rlink->llink = newnode;             // (2)
		sentinal->rlink = newnode;                    // (3)             
		listCopy = listCopy->llink;
	}
	/* (1) (2)
	           ----------  (1)  ----------
      	(new)  |  |  |  |<----->|  | 0|  | (sen)
	           ----------       ----------
	                            ^        |  (2)
	                            └--------
	*/
	/* (3)
	           ----------       ----------
	    (new)  |  |  |  |<----->|  | 0|  | (sen)
	           ----------       ----------
               ^                         |  (3)
	          └--------------------------
	*/

	if (size != 0)
		newnode->llink = sentinal;
}

template< typename T >
// Copies all the elements from "right" into the list container 
const List< T >& List< T >::operator=(const List< T > &right)
{
	if (&right != this)                // 不相等時才做
	{
		List< T >::iterator rightptr = right.sentinal->llink;
		if (size == right.size)        // nodes 數量一樣，直接複製 
		{
			List< T >::iterator nowptr = sentinal->llink;
			for (int i = 0; i < size; i++, rightptr = rightptr->llink, nowptr = nowptr->llink)
			{
				nowptr->data = rightptr->data;
			}
		}
		else                           // 砍掉舊的，創建新的
		{
			clear();
			size = right.size;
			sentinal = new ListNode< T >;
			sentinal->data = T();
			sentinal->rlink = sentinal->llink = sentinal;

			List< T >::iterator newnode = nullptr;
			for (unsigned int i = 0; i < size; i++, rightptr = rightptr->llink)
			{
				newnode = new ListNode< T >;
				newnode->data = rightptr->data;
				newnode->rlink = sentinal->rlink;
				sentinal->rlink->llink = newnode;
				sentinal->rlink = newnode;
			}
			newnode->llink = sentinal;
		}
	}

	return *this;
}

template< typename T >
bool List< T >::operator==(const List< T > &right) const
{
	if (size != right.size)
		return false;
	else
	{
		List< T >::iterator it1 = begin();
		List< T >::iterator it2 = right.begin();
		for (; it1 != end(); it1 = it1->llink, it2 = it2->llink)
		{
			if (it1->data != it2->data)
				return false;
		}
	}
	return true;
}

template< typename T >
void List< T >::resize(unsigned int n)
{
	if (n == size)
		return;
	else if (n < size)                // 大變小
	{
		size = n;
	}
	else                              // 小變大
	{
		List< T >::iterator now = sentinal->rlink;
		List< T >::iterator newNode = nullptr;
		for (unsigned int i = 0; i < n; i++)
		{
			newNode = new ListNode< T >;
			newNode->data = T();
			newNode->rlink = sentinal->rlink;
			sentinal->rlink->llink = newNode;
			sentinal->rlink = newNode;
			now = now->llink;
		}
		newNode->llink = sentinal;
	}
	size = n;
}