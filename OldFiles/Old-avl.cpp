//
// ========================================
// HW13: Implement a Binary Search Tree 
//       which can be converted to AVL Tree 
// ========================================
// 
// In this assignment, we will implement 
// an AVL tree which can also do standard 
// Binary Search Tree adding and removal.  
// 
// The Node class and AVL class are both 
// partly defined for you. 
// 
// ***************************************
// You can add new variables and functions 
// in both classes. However, you should 
// implement the following given functions 
// because they will be called in the main 
// function to test part of your implementation. 
// (Check "main" function for more details.)
// 1. PreTraverse()
// 2. GetRoot()
// 3. Add()
// 4. Remove()
// 5. Add_AVL()
// 6. Remove_AVL()
// 7. Height()
// Other given functions are only recommended. 
// ***************************************
// 

#include <iostream>
using namespace std;

class Node {
private:
	int key;
	Node* p_left; 
	Node* p_right;
	Node* p_parent;
public:
	void Set_key(int x);
	int Get_key();
	void Set_left(Node *p);
	void Set_right(Node* p);
	void Set_parent(Node* p);
	Node* Get_left();
	Node* Get_right();
	Node* Get_parent();
	Node();
};

void Node::Set_key(int x){
	key = x;
}
int Node::Get_key(){
	return key;
}
void Node::Set_left(Node* p){
	p_left = p;
}
void Node::Set_right(Node* p){
	p_right = p;
}
void Node::Set_parent(Node* p){
	p_parent = p;
}
Node* Node::Get_left(){
	return p_left;
}
Node* Node::Get_right(){
	return p_right;
}
Node* Node::Get_parent(){
	return p_parent;
}
Node::Node(){
	key = -1;
	p_left = NULL;
	p_right = NULL;
	p_parent = NULL;
}

class AVL {
private:
	
	// This is root of the AVL
	Node* root;

public:

	// This function implements pre-order 
	// traverse, starting from the root, 
	// and prints the traveres sequence 
	// (with no space between nodes). 
	// You can use the function you implemented 
	// in HW10 (by slightly modifying it). 
	// This function is only used to test 
	// if your updated AVL/BST is correct. 
	void PreTraverse(Node* p);

	// This function returns the root node. 
	// Normally we don't need it. Here we 
	// just it to evaluate your Height function.
	// See main function test case 5 for details.
	Node* GetRoot();

	// This function performs search 
	// on the current AVL with "key".
	// It returns address of a matching 
	// node, or returns NULL if no 
	// matching node is found. 
	Node* Search(int key);

	// This function adds a new node at 
	// "p" to AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST adding.)
	// It can return a proper address.
	Node* Add(Node* p);

	// This function removes a node with 
	// "key" from AVL without considering 
	// any violation of AVL property. 
	// (So just standard BST removal.) 
	// For simplicty, to fill holes, let 
	// us only use the recursive algorithm 
	// that looks for the max/min node in 
	// the left/right subtress of the hole. 
	// It can return a proper address.
	Node* Remove(int key);

	// This function adds a new node 
	// stored at "p" to AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Add_AVL(Node* p);

	// This function removes a node 
	// with "key" from AVL and performs 
	// necessary rotations to restore 
	// the AVL property.
	void Remove_AVL(int key);

	// This function returns height 
	// of a subtree rooted at "p". 
	int Height(Node* p);

	// This function performs clock-wise
	// rotation at node "p". It only does
	// rotation and does not consider 
	// the type of violation scenario.
	// It can return a proper address.
	Node* Rotate_cw(Node* p);

	// This function performs counter 
	// clock-wise rotation at node "p". 
	// It only does rotation and does 
	// not consider the type of violation 
	// scenario. It can return a proper address.
	Node* Rotate_cc(Node* p);

	// This function checks if there 
	// is a violation at a node p, and 
	// return the violation scenario. 
	// It returns a string of 
	// - "NO" if no violation 
	// - "LL" if it is left-left violation 
	// - "RR" if it is right-right violation
	// - "LR" if it is left-right violation
	// - "RL" if it is right-left violation
	string CheckViolation(Node* p);

	// This function intiailizes root = NULL.
	AVL();
};

// This function implements pre-order 
// traverse, starting from the root, 
// and prints the traveres sequence 
// (with no space between nodes). 
// You can use the function you implemented 
// in HW10 (by slightly modifying it). 
// This function is only used to test 
// if your updated AVL/BST is correct. 
void AVL::PreTraverse(Node* p){
	
	//Base Case
	if(p == NULL) return;
	//Recursive case
	else{
		cout << p->Get_key();
		PreTraverse(p->Get_left());
		PreTraverse(p->Get_right());
	}
}

//Get root
Node* AVL::GetRoot(){
	return root;
}

// Search
Node* AVL::Search(int key){

	//Pointer starts at the root
	Node* curr = GetRoot();

	//Run while the curr pointer is not NULL
	while(curr != NULL){

		//Found key
		if(key == curr->Get_key()){
			return curr;
			break;
		}
		//Search left subtree
		else if(key < curr->Get_key()){
			curr = curr->Get_left();
		}
		//Search right subtree
		else{
			curr = curr->Get_right();
		}
	}

	return NULL;
}

// This function adds a new node at 
// "p" to AVL without considering 
// any violation of AVL property. 
// (So just standard BST adding.)
// It can return a proper address.
Node* AVL::Add(Node* p){

	int key = p->Get_key();

	Node* nodeToAdd = new Node();
	
	nodeToAdd->Set_key(key);
	
	//If the tree is empty, set the new node as the root
	if(root == NULL){
		root = nodeToAdd;
		return nodeToAdd;
	}

	Node* curr = root;
	Node* parent = NULL;

	//Modified search alorithm, that keeps track of the current node and its parent
	while(curr != NULL){

		parent = curr;

		if(key < curr->Get_key()){
			curr = curr->Get_left();
		}
		else{
			curr = curr->Get_right();
		}
	}

	//When current is NULL, parent is at the node we need to add p too
	nodeToAdd->Set_parent(parent);

	if(key < parent->Get_key()){
		parent->Set_left(nodeToAdd);
	}
	else{
		parent->Set_right(nodeToAdd);
	}

	return nodeToAdd;
}

// Function to find the minimum
// valued node in a BST
Node * minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->Get_left() != NULL){
		current = current->Get_left();
	} 

    return current;
}

// This function removes a node with 
// "key" from AVL without considering 
// any violation of AVL property. 
// (So just standard BST removal.) 
// For simplicty, to fill holes, let 
// us only use the recursive algorithm 
// that looks for the max/min node in 
// the left/right subtress of the hole. 
// It can return a proper address.
Node* AVL::Remove(int key){

}


// This function intiailizes root = NULL.
AVL::AVL(){
	root = NULL;
}



// --------------1
// Main Function 
// --------------
int main()
{
	// mode_test: indicate which function to test 
	// model_avl: if 1, we do adding with AVL property
	//            if 0, we do adding without AVL property 
	//            (so just standard bst adding)
	// key_temp:  keys of nodes to add to AVL initially
	// key_search:key of node for search/remove
	int mode_test, mode_avl, key_temp, key_search;
	
	Node* temp;

	// This is our AVL tree object.
	AVL tree;

	cin >> mode_test >> mode_avl >> key_search;

	while (cin >> key_temp) {

		temp->Set_key(key_temp);

		if (mode_avl == 0)
		{
			tree.Add(temp);
		}
		else if (mode_avl == 1) {
			//tree.Add_AVL(temp);
		}
	}


	// Mode 0: test "Add" function.
	if (mode_test == 0) {
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 1: test "Add_AVL" function
	else if (mode_test == 1) {
		//tree.PreTraverse();
	}
	// Mode 2: test "Search" function 
	else if (mode_test == 2) {
		temp = tree.Search(key_search);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_key();
		}		
	}
	// Mode 3: test "Remove" function 
	else if (mode_test == 3) {
		tree.Remove(key_search);
		tree.PreTraverse(tree.GetRoot());
	}
	// Mode 4: test "Remove_AVL" function 
	else if (mode_test == 4) {
		//tree.Remove_AVL(key_search);
		//tree.PreTraverse();
	}
	// Mode 5: test "Height" function 
	else if (mode_test == 5) {
		//cout << tree.Height(tree.GetRoot());
	}


	return 0;
}

