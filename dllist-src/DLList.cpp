#include <iostream>
#include "DLList.h"


/**
 * Default Constructor. 
 * Remarks:
 *      The constructor is called when a new instance is
 *      allocated (either on the stack automatically or
 *      on the heap via 'new') and must allocate and initialize
 *      any memory or other resources needed.
 *      DLList must use a sentinel node which points to itself from both 
 *      next and prev if the list is empty. This node is never removed
 *      unless the list is destroyed. The sentinel node itself never
 *      holds a value, it is effectively a 'dummy' node without a value
 */
DLList::DLList() {
	head = new DLNode;
	head->next = head;
	head->prev = head;
	head->data = 0;
}


/**
 * Destructor for DLList
 * Remarks:
 *      The destructor is called when an instance of the class is deleted,
 *      either by calling 'delete' on a pointer or when a local copy on the
 *      stack is deleted when a function returns. The destructor must cleanup
 *      any memory or resources held by the object.
 */
DLList::~DLList() {
	if (head)
		delete head;
}


/**
 * Print the list
 * Remarks:
 *      This function prints the linked list with one number per line
 *      of the format "%d\n".
 *      Only data values may be printed, do not print any new lines for the
 *      sentinel node.
 *
 *      ex. The list S<->1<->2<->3<->S
 *      will print:
 *      "1\n2\n3\n"
 */
void DLList::print() {
	DLNode *p = new DLNode;
	p->next = head->next;
	bool empty = true;
	while (p->next != head) {
		printf("%d\n", p->next->data);
		p->next = p->next->next;
		empty = false;
	} delete p;
	if (empty == true) {
		printf("The list is empty.\n");
	}
}

/**
 * Print the list in sorted order
 * Remarks:
 *      This function prints the linked list with one number per line
 *      of the format "%d\n" starting with the lowest value first and printing
 *      in ascending order. Only data values may be printed, do not print 
 *      any new lines for the sentinel node.
 *      The list itself must remain intact. Do not sort the list itself, only the
 *      order in which the values are printed out must be sorted.
 *
 *      ex. The list Sentinel<->5<->2<->7<->Sentinel
 *      will print:
 *      "2\n5\n7\n"
 *
 *      The list must still end up as Sentinel<->5<->2<->7<->Sentinel
 *      after this function has been called.
 */
void DLList::printSorted() {
	int list[head->data];
	int count = 0;

	DLNode *p = new DLNode;
	p->next = head->next;
	while (p->next != head) {
		list[count] = p->next->data;
		p->next = p->next->next;
		count++;
	} delete p;
	
	if (count == 0) {
		printf("The list is empty.\n");
		return;
	}

	bool swapped = true;
	int j = 0;
	int tmp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < count-j; i++) {
			if (list[i] > list[i+1]) {
				tmp = list[i];
				list[i] = list[i+1];
				list[i+1] = tmp;
				swapped = true;
			}
		}
	}
	
	for (int i = 0; i < count; i++) {
		printf("%d\n", list[i]);
	}
}	

/**
 * Adds an item to the front of the DLList
 * Parameters:
 *      data - an integer value for the newest node to be added to the list
 * Remarks:
 *      Add item to the front of the DLList (sentinel->next), allocating resources for the node
 *      and fixing any pointers along the way. Please use "new" to allocate memory
 */
void DLList::insertFront(int data) {
	DLNode *e = new DLNode;
	e->data = data;
	e->next = head->next;
	e->prev = head;

	e->next->prev = e;
	e->prev->next = e;
	head->data++;
}


/**
 * Removes the tail item of the DLList
 * Parameters:
 *      data -     a reference integer value used as a return parameter. When the last node
 *                is removed, make sure to set the parameter data to the value of the node
 *                which was removed.
 * Returns:
 *      true if there was an element to remove and it was removed successfully, false otherwise
 * Remarks:
 *      Remove item to the back of the DLList (sentinel->prev), Make sure to deallocate
 *      the resources for the node which is being removed and fix any pointers along the way.
 *      Please use "delete" to deallocate memory
 */
bool DLList::removeLast(int & data) {

	if (head->data == 0) {
		return false;
	}

	DLNode *p = new DLNode;
	p->data = head->prev->data;
	p->next = head->prev->next;
	p->prev = head->prev->prev;

	data = p->data;
	delete head->prev;
	head->prev = p->prev;
	head->prev->next = head;
	delete p;
	head->data--;

    return true;
}


/**
 * Find the set difference between this list and the parameter list
 * Parameters:
 *      rhs  -  a reference of some list. No value of a node which exists in this parameter list
 *              must be returned in our difference list.
 * Returns:
 *      A pointer to a newly created list containing the difference between the current
 *      list and the right hand side list
 * Remarks:
 *      This function always returns a list which can be deallocated by the caller.
 *      This list must contain no duplicates. It contains all of the elements which exist
 *      in this object list but not in the parameter list.
 *      Ordering does not matter, only the contents do.
 *    
 *      ex.
 *      this:  Sentinel<->1<->5<->3<->3<->2<->Sentinel
 *      list:  Sentinel<->1<->2<->7<->2<->Sentinel
 *
 *      returns: Sentinel<->5<->3<->Sentinel
 */
DLList * DLList::difference(DLList& rhs) {
    return nullptr;
}

/**
 * Return a sublist of this list from the range [start, end]
 * Parameters:
 *      start - starting index of the sublist (inclusive). 0 signifies the head of the list
 *      end   - ending index of the sublist (inclusive). len-1 signifies the tail of the list
 * Returns:
 *      A pointer to a newly created list containing a range of values from this list
 * Remarks:
 *      This function always returns a list which can be deallocated by the caller. Upon an error
 *      we still return an emtpy list. There is an error if start is negative, end >= the length of the list,
 *      or start > end.
 *      The new sublist should contain its own DLNodes, not the same nodes used by this list.
 *      Keep the ordering of the sublist the same as in the original list
 *   
 *      ex.
 *      list:  Sentinel<->1<->2<->7<->2<->Sentinel
 *    
 *      getRange(0, 3) will return a copy of the same list
 *
 *      getRange(1, 2) will return
 *      sublist: Sentinel<->2<->7<->Sentinel
 */
DLList * DLList::getRange(int start, int end) {
    return nullptr;
}


/**
 * Find the set intersection between this list and the parameter list
 * Parameters:
 *      rhs  - a reference of some list. Every value which exists in both the parameter list
 *             and the right hand side list must be in the intersection list
 * Returns:
 *      A pointer to a newly created list containing the intersection between this
 *      list and the rhs list
 * Remarks:
 *      This function always returns a list which can be deallocated by the caller.
 *      This list must contain no duplicates. It contains all of the elements which exist
 *      in this object list and in the parameter list.
 *      Ordering does not matter, only the contents do.
 * 
 *      ex.
 *      this:  Sentinel<->1<->5<->3<->3<->2<->Sentinel
 *      list:  Sentinel<->1<->2<->7<->2<->Sentinel
 *
 *      returns: Sentinel<->1<->2<->Sentinel
 */
DLList * DLList::intersection(DLList& rhs) {
    return nullptr;
}

/**
 * Removes any node of this list from the range [start, end]
 * Parameters:
 *      start - starting index of the nodes to remove (inclusive). 0 signifies the head of the list
 *      end   - ending index of the nodes to remove (inclusive). len-1 signifies the tail of the list
 * Remarks:
 *      Upon an error don't remove any nodes. There is an error if start is negative, end > the length of the list,
 *      or start > end.
 *    
 *      ex.
 *      list:  Sentinel<->1<->2<->7<->2<->Sentinel
 *    
 *      removeRange(0, 3) will remove every node in the list
 *
 *      removeRange(1, 2) will change the list into
 *      list: Sentinel<->1<->2<->Sentinel
 */
void DLList::removeRange(int start, int end) {

}

int main() {
	DLList *list = new DLList();
	int value = 0;
	if (list->removeLast(value) == false) {
		printf("The list was empty.\n");
	}
	return 0;
}
