#include <iostream>

template <typename Type>
class Resizable_deque {
	public:

		// Constructors

		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		// Accessors

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		// Mutators

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();
		//void print(); // Function used to print the deque

	private:
		int deque_capacity;
		int deque_initial_capacity;
		int deque_size;
		int deque_front;
		int deque_back;
		Type *deque_array;
		// Any private member functions
		//   - helper function for resizing the array
		void resize();

};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////


/* Constructor: Resizable_deque( int n )
	This is the (non-) default constructor that allocates the memory for an array 
	with the initial capacity of n. The initial capacity (n) must be greater or 
	equal to 16. If n < 16, the initial capacity is set to 16.

	deque_size 				-> Number of elements in the array
	deque_front 			-> Position of the front element of the array
	deque_back 				-> Position of the back element of the array
	deque_initial_capacity 	-> Initial capacity of the array
	deque_capacity 			-> Actual capacity of the array
	deque_array 			-> Empty array initialized with the initial capacity

	This constructor assumes the initial capacity to be greater or equal to 16.
	The front and back is set to 0, so they point to the same element. The size 
	is set to 0, i.e. the array is empty.
	No errors are expected with this constructor
*/
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n )
:deque_size(0), 
deque_front(0),
deque_back(0)
{
	// Check the initial capacity of the array
	int capacity = ( n < 16 ) ? 16: n;
	deque_initial_capacity = capacity;
	deque_capacity = capacity;
	deque_array = new Type[deque_capacity];
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
{ }

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
{ }

/* Destructor: ~Resizable_deque()
	This is the destructor that deallocates any dynamically allocated memory.

	deque_array 	-> dinamically allocated array

	No errors are expected with this destructor
*/
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {

	delete [] deque_array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

/* Accessor: size()
	This function returns the number of elements in the deque 
	deque_size -> member variable 
	This accessor assumes that the deque size has been updated.
	No errors are expected with this accessor
*/

template <typename Type>
int Resizable_deque<Type>::size() const {

	return deque_size;
}

/* Accessor: capacity()
	This function returns the capacity of the underlying array.
	deque_capacity -> member variable 
	This accessor assumes that the deque capacity has been updated.
	No errors are expected with this accessor
*/

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	return deque_capacity;
}

/* Accessor: empty()
	This function returns true if the deque is empty or false otherwise.
	deque_size -> member variable 
	This accessor assumes that the deque capacity has been updated.
	No errors are expected with this accessor
*/

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Condition to determine if the deque is empty or not
	return (deque_size == 0);
}

/* Accessor: front()
	This function returns the front object of the deque.
	deque_array -> member variable 
	deque_front -> member variable
	This accessor assumes deque_front >= 0.
	An underflow error is thrown if the deque is empty.
*/

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Condition to see if the deque is empty
	if (empty())
		throw underflow();
	else
		return deque_array[deque_front];
}

/* Accessor: back()
	This function returns the back object of the deque.
	deque_array -> member variable 
	deque_back -> member variable
	This accessor assumes deque_back >= 0.
	An underflow error is thrown if the deque is empty.
*/

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Condition to see if the deque is empty
	if (empty())
		throw underflow();
	else
		return deque_array[deque_back];
}

/* Mutator: swap( Resizable_deque<Type> &deque )
	This mutator swaps all the member variables of *this deque with 
	those of the passed argument deque.
	deque_size
	deque_front
	deque_back
	deque_initial_capacity
	deque_capacity
	deque_array 
*/

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	std::swap( deque_array, deque.deque_array);
	std::swap( deque_capacity, deque.deque_capacity );
	std::swap( deque_initial_capacity, deque.deque_initial_capacity);
	std::swap( deque_size, deque.deque_size);
	std::swap( deque_front, deque.deque_front);
	std::swap( deque_back, deque.deque_back);
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {

	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {

	swap( rhs );

	return *this;
}

/* Mutator: push_front( Type const &obj )
	This mutator inserts an object (obj) at the front of the deque.
	It implements member functions and member variables. 
	It assumes a deque has been created. 
	If the array is full, the array capacity is doubled, before the object is inserted.
*/

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// Check if the array is full
	resize();
	// Check if the array is not empty
	if(!empty()){
		// If the array is not empty and the front element is at place 0
		if(deque_front == 0)
			// The front element position is moved to the last position in the deque
			deque_front = deque_capacity - 1;
		else
			// The front element position is moved to the previous position
			deque_front--;
	}
	// If the array is empty, the front element position is set to 0
	deque_array[deque_front] = obj;
	// The size of the array increases by 1
	deque_size++;
}

/* Mutator: push_back( Type const &obj )
	This mutator inserts an object (obj) at the back of the deque.
	It implements member functions and member variables. 
	It assumes a deque has been created. 
	If the array is full, the array capacity is doubled, before the object is inserted.
*/

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// Resize the array if it is full
	resize();
	// Check if the array is empty
	if(empty()){
		// If it is empty, the object is inserted at the position 0 
		deque_array[deque_back] = obj;
	}
	else{
		// if the array is not empty
		// the next position is updated by 1
		deque_back++;
		// The objected is inserted at the new position at the back
		deque_array[deque_back] = obj;
	}
	// The size of the array increases by 1
	deque_size++;
}

/* Mutator: pop_front()
	This mutator removes an object (obj) from the front of the deque.
	It implements member functions and member variables. 
	It assumes a deque has been created. 
	If the array is empty, an underflow error is thrown
	If the number of elements in the array is 1/4 or less of the array's capacity, 
	the capacity is halved. However, it cannot be halved passed the intial capacity
*/

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	// Check if the array is empty 
	if (empty()) 
		// Exception thrown
		throw underflow();
	
	// Check if the front element is different from the back element
	if(deque_front != deque_back) 
		// Calculates the position of the front element within the array
		deque_front = (deque_front + 1) % deque_capacity;
	// The size of the array decreases by 1
	deque_size--;
	// Resize the array if the number of elements is smaller than 1/4 of the capacity
	resize();
}

/* Mutator: pop_back()
	This mutator removes an object (obj) from the back of the deque.
	It implements member functions and member variables. 
	It assumes a deque has been created. 
	If the array is empty, an underflow error is thrown
	If the number of elements in the array is 1/4 or less of the array's capacity, 
	the capacity is halved. However, it cannot be halved passed the intial capacity
*/

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	// Check if the array is empty
	if (empty())
		// Exception thrown
		throw underflow();
	
	// Check if the front element is different from the back element 
	if (deque_front != deque_back)
		// Check if the back position is 0
		if (deque_back == 0)
			// In this case the back position goes to the last position of the array
			deque_back = deque_capacity - 1;
		else 
			// The back position is moved to the previous position
			deque_back--;
	// The size of the array decreases by 1
	deque_size--;
	// Resize the array if the number of elements is smaller than 1/4 of the capacity
	resize();
}

/* Mutator: clear()
	This mutator empties the deque by resetting the member variables, and the array is resized
	to the initial capacity.
	It implements member variables
	It assumes a deque has been created
*/

template <typename Type>
void Resizable_deque<Type>::clear() {
	// Resetting the member variables
	deque_size = 0;
	deque_front = 0;
	deque_back = 0;
	deque_capacity = deque_initial_capacity;
	// Delete the current array
	delete [] this->deque_array;
	// Creates the new array with the initial capacity
	deque_array = new Type[deque_initial_capacity];
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

/* Mutator: resize()
	This mutator resizes the array under 2 conditions:
	- If the array is full, it doubles the capacity of the array
	- If the number of elements is less than 1/4 of the array's capacity, it is halved,
	but it cannot be halved passed the initial capacity.
	It implements member variables
	It assumes a deque has been created
*/

template <typename Type>
void Resizable_deque<Type>::resize() {
	// Initialize a helper variable
	int capacity_old = deque_capacity;
	// Check if the deque is full
	if (deque_size == deque_capacity) {
		// Double the capacity
		deque_capacity *= 2;
	}
	// Check if the number of elements is less than 1/4 of the array's capacity, then it is halved
	// or set to the initial capacity
	else if (deque_size <= deque_capacity/4) {
		deque_capacity = std::max(deque_initial_capacity, deque_capacity/2);
	}
	// Check if the array was resized 
	if (capacity_old != deque_capacity){
		// Creates a new helper array
		auto deque_old = deque_array;
		// Resets the array
		deque_array = new Type[deque_capacity];
		// Copy all the elements of the old array into the new created array
		for ( int i = 0; i < deque_size; i++ ){
			deque_array[i] = deque_old[(i + deque_front) % capacity_old];
		}
		// Resets the front and back positions
		deque_front = 0;
		deque_back = deque_size - 1;
		// Delete the helper array
		delete [] deque_old;
	}
}

// Delete this function
// Function used to print the deque
// template <typename Type>
// void Resizable_deque<Type>::print(){ // Public in order to print the array
// 	std::cout << "F->";
// 	for( int i = 0; i < deque_size; i++ ){
// 		std::cout << deque_array[(i + deque_front) % deque_capacity] << "->";
// 	}
// 	std::cout << "B" << std::endl << std::endl;
// }
