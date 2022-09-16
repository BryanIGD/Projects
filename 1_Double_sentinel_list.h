#include <iostream>

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		// Constructors

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

/* Default Constructor: Double_sentinel_list()
	This is the default constructor that creates the head and tail sentinel nodes
	head -> Head sentinel node
	tail -> Tail sentinel node
	This constructor assumes that the created list is new
	No errors are expected with this constructor
*/

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_size( 0 )
{
	Double_node *head = new Double_node;
	Double_node *tail = new Double_node;
	head->next_node = tail;
	head->previous_node = nullptr;
	tail->previous_node = head;
	tail->next_node = nullptr;
	list_head = head;
	list_tail = tail;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{ }

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	this->swap(list);
}

/* Destructor: ~Double_sentinel_list()
	It deletes all the nodes in the list, including the sentinels.
	list_head -> Head sentinel node
	list_tail -> Tail sentinel node
	current_node -> It will go through the whole list to delete all nodes
	temp_node -> It is the node that will delete each node at a time
	This destructor always expect at least 2 nodes (sentinels)
	No errors are expected with this destructor
*/

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {

	Double_node *current_node = this->list_head;
	while ( current_node != list_tail ) {
		Double_node *temp_node = current_node;
		current_node = current_node->next_node;
		delete temp_node;
	}
	delete current_node;
}

/* Accessor: size()
	This function returns the size of the list 
	list_size -> member variable 
	This accessor assumes that the list size has been updated.
	No errors are expected with this accessor
*/

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;
}

/* Accessor: empty()
	This function returns true if the list is empty, or false otherwise. 
	size() -> member function 
	This accessor assumes that the list size has been updated.
	No errors are expected with this accessor
*/

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	if ( this->size() == 0 ){
		return true;
	}
	else {
		return false;
	}
}

/* Accessor: front()
	This function returns the object stored in the first/front node
	empty() -> member function
	This accessor assumes that the list has at least one element
	Throws underflow if the list is empty
*/

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if ( this->empty() ) throw underflow();

	return this->list_head->next_node->node_value;
}

/* Accessor: back()
	This function returns the object stored in the last/back node
	empty() -> member function
	This accessor assumes that the list has at least one element
	Throws underflow if the list is empty
*/

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if ( this->empty() ) throw underflow();

	return this->list_tail->previous_node->node_value; 
}

/* Accessor: begin()
	This function returns the address of the first node in the list
	This accessor assumes that the list has at least one element
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return this->list_head->next_node;
}

/* Accessor: end()
	This function returns the address of the tail sentinel node
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return this->list_tail;
}

/* Accessor: rbegin()
	This function returns the address of the last node in the list
	This accessor assumes that the list has at least one element
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return this->list_tail->previous_node;
}

/* Accessor: rend()
	This function returns the address of the head sentinel
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return this->list_head;
}

/* Accessor: find()
	This function returns the address of the first node in the list storing a value equal to the argument
	empty() -> member function
	end() -> member function
	It returns end() if non is found.
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {

	if ( this->empty() ) return this->end();

	Double_node *temp = list_head;

	while ( temp->next_node != list_tail and temp->node_value != obj )
		temp = temp->next_node;
	if ( temp->node_value == obj ) {
		return temp;
	}
	else {
		return this->end();
	}
}

/* Accessor: count()
	This function returns the number of nodes in the linked list storing a value equal to the argument
	empty() -> member function
	If none in found return 0.
*/

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {

	int cont = 0;
	if ( this->empty() ) return cont;

	Double_node *temp = list_head;

	while ( temp != list_tail ) {
		if ( temp->node_value == obj ){
			cont += 1;
		}
		temp = temp->next_node;
	}
	return cont;
}

/* Mutator: swap( Double_sentinel_list<Type> &list )
	This mutator swaps all the member variable of *this linked list with those of the passed argument list
*/

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {

	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

/* Mutator: Assignment operator 
	This assignment operator copies the argument list into the *this list 
*/
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {

	swap( rhs );

	return *this;
}

/* Mutator: Move operator 
	This assignment operator moves the nodes of the argument list into *this list, changing the argument list into an empty list
*/
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {

	swap( rhs );

	return *this;
}

/* Mutator: push_front( Type const &obj )
	This mutator inserts a node, storing obj, at the front of the list.
*/

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

	Double_node *aux = new Double_node;
	aux->node_value = obj;
	aux->next_node = list_head->next_node;
	aux->previous_node = list_head;
	list_head->next_node->previous_node = aux;
	list_head->next_node = aux;
	list_size += 1;
}

/* Mutator: push_back( Type const &obj )
	This mutator inserts a node, storing obj, at the back of the list.
*/

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	
	Double_node *aux = new Double_node;
	aux->node_value = obj;
	aux->next_node = list_tail;
	aux->previous_node = list_tail->previous_node;
	list_tail->previous_node->next_node = aux;
	list_tail->previous_node = aux;
	list_size += 1;
}

/* Mutator: pop_front()
	This mutator removes the first (non-sentinel) node on the list
	Throws underflow() if the list is empty
*/

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {

	if ( this->empty() ) throw underflow();

	Double_node *rem_node = list_head->next_node;
	list_head->next_node = rem_node->next_node;
	rem_node->next_node->previous_node = list_head;
	delete rem_node;
	list_size -= 1;
}

/* Mutator: pop_back()
	This mutator removes the last (non-sentinel) node on the list
	Throws underflow() if the list is empty
*/

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	
	if ( this->empty() ) throw underflow();

	Double_node *rem_node = list_tail->previous_node;
	list_tail->previous_node = rem_node->previous_node;
	rem_node->previous_node->next_node = list_tail;
	delete rem_node;
	list_size -= 1;
}

/* Mutator: erase( Type const &obj )
	This mutator deletes all the nodes in the linked list that have a value equal to the argument obj.
	It returns the number of deleted nodes
*/

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	int cont = 0;
	int aux = 0;
	if ( this->empty() ) return cont;
	Double_node *current_node = list_head;

	while ( current_node != list_tail ){
		if ( current_node->node_value == obj ) {
			Double_node *temp_node = current_node;
			current_node->previous_node->next_node = temp_node->next_node;
			current_node->next_node->previous_node = temp_node->previous_node;
			current_node = current_node->next_node;
			delete temp_node;
			cont += 1;
			list_size -= 1;
		}
		if ( cont == aux ) {
			current_node = current_node->next_node;
		}
		else {
			aux = cont;
		}
	}
	return cont;
}

/* Node Constructor: Double_node( nv, pn, nn )
	This is the default constructor for the nodes in the list 
	nv -> Member variable that stores the value of the node
	pn -> Member variable that points to the next Double_node
	pp -> Member variable that points to the previous Double_node
	This constructor requires a value, next pointer and previous pointer
	No errors are expected with this constructor
*/

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
node_value( nv ), 
previous_node( pn ),
next_node( nn )
{ }

/* Member function: value()
	This member function returns the value of the node
*/

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	
	return node_value; 
}

/* Member function: previous()
	This member function returns the previous pointer
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	
	return previous_node;
}

/* Member function: next()
	This member function returns the next pointer
*/

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	
	return next_node;
}
