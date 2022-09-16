// Include the necessary libraries for the program to work
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>


/* 
	Graph_DAG is a class that handles the graph for this specific application
*/
template<class Type>
class Graph_DAG{
	public:
		// Node is class (structure) that storages the value of the node, if it was visited, 
		// and its neighbors
		class Node{
			public:
			Type data = {};
			std::vector<Node*> neighbors;
			bool isVisited;
			Node( Type data_in, std::vector<Node*> v_in = {}):
			data(data_in), neighbors(v_in), isVisited(false){}
		};

		// Member variable for Graph_DAG
		std::vector<Node*> v;

		/*
			topoSortRec is a recursive helper function that iterates through the graph
			and stores the visited nodes in a stack using the DFS method. It marks as 
			visited each node of the vector v, so the main function only visites each 
			node once.
		*/
		void topoSortRec(Node* curr_v, std::stack<Node*>& s){
			curr_v->isVisited = true;
			for(auto i:curr_v->neighbors)
				if(!i->isVisited)
					topoSortRec(i,s);
			s.push(curr_v);
		}

	public:
		/*
			addVertex is a function that takes as input the object data_in, creates a new node
			for this object, stores at the back of the vector v, which is a member variable 
			of the graph, and returns the index where it was stored in the vector.
		*/
		int addVertex(Type data_in){
			if(v.size() == 0){
				Node* tmp = new Node(data_in);
				v.push_back(tmp);
				return 0;
			}
			else{
				for(auto i = v.begin(); i != v.end(); ++i){
					Node* curr_n = *i;
					if (curr_n->data == data_in){
						return std::distance(v.begin(),i);
					}
				}
				Node* tmp = new Node(data_in);
				v.push_back(tmp);
				return v.size() - 1;
			}
		}

		/*
			addNeighbor is a function that takes as input two integers, a and b. These integers 
			are the index positions of the nodes that need to be added a relationship to. 
			In this application, the relationship chosen is "contained by", so b is contained 
			by a. Then, b points to a (b -> a). This is because b should be compiled before 
			compiling a. 

		*/
		void addNeighbor(int a, int b){
			// b->a
			v[b]->neighbors.push_back(v[a]);
		}

		/*
			topologicalSort is the main function used to sort the graph topologically. It creates
			a stack, which will be used to store the objects. It marks all nodes as not visited 
			to ensure that the helper function iterates through the whole graph. Checks if a node 
			was already visited by the helper function, if so do nothing, otherwise, visit the node.
			Finally, it creates a vector of object type that returns the topological order of the 
			graph, by popping n times the top element of the stack which are oredered. This result
			is returned as the result of the whole program

		*/
		std::vector<Type> topologicalSort(){
			std::stack<Node*> s;
			for( auto i:v )
				i->isVisited = false;
			
			for( auto i:v )
				if( !i->isVisited )
					topoSortRec(i,s);
			std::vector<Type> result;
			while( !s.empty() ){
				result.push_back(s.top()->data);
				s.pop();
			}
			return result;
		}
};

/*
	Main program.
	This function requires a user input text file with the libraries that need to be 
	topologycally sorted, and outputs the topological sorted order in which this libraries
	must be compiled.
*/
int main(int argc, char** argv)
{
	// First input argument is always the program name...
	char* fileName = argv[1];
	
	// Open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		// If no file is passed, do this
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
	
	// Initializes the graph object to later be populated with the information
	// retireved from the text file
	Graph_DAG<std::string> G1;

	// Extract line by line the library's name
	std::string line;

	// Initialize the index variables of the libraries for the vector
	int a, b;

	// Iterate through the whole file
	while(std::getline(fin,line))
	{
		// Checks if the line starts with '#', if not do this:
		if( *line.begin() != '#' ) {

			/*
				Add this library as a graph's vertex and return the index in which this 
				library is stored in the member variable v of G1.
				This type of library can be considered as the father, and the libraries with 
				'#' are considered as children
			*/
			a = G1.addVertex(line);
		}
		else {
			/*
				If the library contains a '#' at the beginning, they are considered as children
				of a. Then, the name of the library is extracted from the "#include <library_name>"
				structure, it needs (library_name). 
			*/
			int first_char = line.find("<") + 1;
			int last_char = line.length() - first_char - 1;

			// Create the substring with just the name of the library
			std::string pending_library = line.substr(first_char,last_char);

			/*
				Add this library as a graph's vertex ans return the index in which this 
				library is stored in the member variable v of G1.
				Due to it is a child library of a, b is contained by a.
			*/
			b = G1.addVertex(pending_library);

			// Creates the relationship between the father library a, and child library b.
			// This relationship is b is contained by a. Then, b -> a
			G1.addNeighbor(a,b);
		}

	}
	// Prints the resulting vector after the graph was topologically sorted
	// Iterates through the reulting vector.
	std::vector<std::string> res = G1.topologicalSort();
	for(auto i = res.begin(); i != res.end(); ++i){
		std::cout << *i << std::endl;
	}
	return EXIT_SUCCESS;
}
