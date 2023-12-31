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
#include <cstdlib>
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
	void PreTraverse();

	//Helper function for PreTraverse
	void RecursivePreTraverse(Node* root);

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

	//Recursive remove function
	Node* RemoveRecursive(int key, Node* p);

	//Recursive get replacement function
	Node* getReplacement(Node* curr);

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

	//Height plus 1 called by
	int HeightPlusOne(Node* p);

	// This function returns height 
	// of a subtree rooted at "p". 
	int Height(Node* p);

	//This function gets the depth of a node
	int Depth(Node* p);

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

	//Balance helper function
	int Balance(Node* p);

	// This function intiailizes root = NULL.
	AVL();
};

//PreTraverse: Calls RecursivePreTraverse function with the root of the tree
void AVL::PreTraverse(){
	RecursivePreTraverse(GetRoot());
}

//Helper function for PreTraverse, actually does the traversing
void AVL::RecursivePreTraverse(Node* p){

	//Base Case
	if(p == NULL) return;
	//Recursive case
	else{
		cout << p->Get_key();
		RecursivePreTraverse(p->Get_left());
		RecursivePreTraverse(p->Get_right());
	}
}

//Getroot
Node* AVL::GetRoot(){
	return root;
}

//Search
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

//Add
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

//Remove
Node* AVL::Remove(int key){
	return RemoveRecursive(key, GetRoot());
}

//Recursive remove function
Node* AVL::RemoveRecursive(int key, Node* p){

	//Base Case
	if(p == NULL){
		return p;
	}
	
	//Recursive Cases
	//Search left subtree if key is less than p->Getkey()
	if(key < p->Get_key()){
		p->Set_left(RemoveRecursive(key, p->Get_left()));
	}
	//Search right subtree if key is greater than p->Getkey()
	else if(key > p->Get_key()){
		p->Set_right(RemoveRecursive(key, p->Get_right()));
	}
	else{
		//If left child is NULL
		if(p->Get_left() == NULL){
			Node* temp = p->Get_right();
			delete p;
			return temp;
		}
		//If right child is NULL
		else if(p->Get_right() == NULL){
			Node* temp = p->Get_left();
			delete p;
			return temp;
		}
		//Get replacement
		else{
			Node* replacement = getReplacement(p);
			p->Set_key(replacement->Get_key());
			p->Set_right(RemoveRecursive(key, p->Get_right()));
		}
	}

	return p;
}

//Recursive get replacement function
Node* AVL::getReplacement(Node* curr){
	curr = curr->Get_right();
    while(curr != NULL && curr->Get_left() != NULL)
        curr = curr->Get_left();
    return curr;
}

// This function adds a new node 
// stored at "p" to AVL and performs 
// necessary rotations to restore 
// the AVL property.
void AVL::Add_AVL(Node* p){
	
	//First add node ignoring BST properties
	Node* curr = Add(p);

	//Check every node on path from curr to root for violation. Handle violations if they exist
	while(curr != NULL){
		string violationMSG = CheckViolation(curr);

		//Left-Left
		if(violationMSG == "LL"){
			curr = Rotate_cw(curr);
		}
		//Right-Right
		else if(violationMSG == "RR"){
			curr = Rotate_cc(curr);
		}
		//Left-Right
		else if(violationMSG == "LR"){
			Rotate_cc(curr->Get_left());
			curr = Rotate_cw(curr);
		}
		//Right-Left
		else if(violationMSG == "RL"){
			Rotate_cw(curr->Get_right());
			curr = Rotate_cc(curr);
		}
		else if(violationMSG == "NO"){
			curr = curr->Get_parent();
		}
	}

}
// - "NO" if no violation 
// - "LL" if it is left-left violation 
// - "RR" if it is right-right violation
// - "LR" if it is left-right violation
// - "RL" if it is right-left violation


// This function removes a node 
// with "key" from AVL and performs 
// necessary rotations to restore 
// the AVL property.
void AVL::Remove_AVL(int key){

	//Standard BST removal
	Node* curr = Remove(key);

	//Check every node on path from curr to root for violation. Handle violations if they exist
	while(curr != NULL){
		string violationMSG = CheckViolation(curr);

		//Left-Left
		if(violationMSG == "LL"){
			curr = Rotate_cw(curr);
		}
		//Right-Right
		else if(violationMSG == "RR"){
			curr = Rotate_cc(curr);
		}
		//Left-Right
		else if(violationMSG == "LR"){
			Rotate_cc(curr->Get_left());
			curr = Rotate_cw(curr);
		}
		//Right-Left
		else if(violationMSG == "RL"){
			Rotate_cw(curr->Get_right());
			curr = Rotate_cc(curr);
		}
		else if(violationMSG == "NO"){
			curr = curr->Get_parent();
		}
	}

}

//Returns the height plus one recursivly
int AVL::HeightPlusOne(Node* root){
	//Base Case
	if (root == nullptr) {
        return 0; // An empty tree has a height of 0.
    }
	//Recursive call for left
    int leftHeight = HeightPlusOne(root->Get_left());
	//Recursive call for right
    int rightHeight = HeightPlusOne(root->Get_right());

    // Return leftHeight plus 1 if its bigger, rightHeight + 1 if it is not
    if (leftHeight > rightHeight) return 1 + leftHeight;
 	else return 1 + rightHeight;
}

//Calls height plus one, decrements value, returns result
int AVL::Height(Node* root) {
	int height = HeightPlusOne(root);
	return --height;
}

//Depth
int AVL::Depth(Node* p){

	Node* curr = p;
	int depth = 0;

	while(curr != NULL){
		depth++;
		curr = curr->Get_parent();
	}

	return depth;
}

//Rotate CW
Node* AVL::Rotate_cw(Node* p){

	Node* A = p->Get_left();
	Node* D = A->Get_right();

	Node* psParent = p->Get_parent();

	//Set A's parent to p's parent. Could be a node or NULL
	A->Set_parent(psParent);

	//Set p's left child to D. Could be a node or NULL
	p->Set_left(D);

	//If D is a node and not NULL, set its parent to p
	if(D != NULL) D->Set_parent(p);

	//Set p's parent to A
	p->Set_parent(A);

	//Set A's right to p
	A->Set_right(p);

	//If A's parent is not NULL, this tree was not rotated at the root
	if(psParent != NULL){

		if(psParent->Get_left() == NULL){
			A->Get_parent()->Set_right(A);
		}
		else if(psParent->Get_right() == NULL){
			A->Get_parent()->Set_left(A);
		}
		else{
			if(psParent->Get_left()->Get_key() == p->Get_key()){
				A->Get_parent()->Set_left(A);
			}
			else{
				A->Get_parent()->Set_right(A);
			}
		}
	}
	
	//If A's parent is NULL, A is the new root
	else{ 
		root = A;
	}

	return A;
}

// This function performs counter 
// clock-wise rotation at node "p". 
// It only does rotation and does 
// not consider the type of violation 
// scenario. It can return a proper address.
Node* AVL::Rotate_cc(Node* p){
	
	Node* B = p->Get_right();
	Node* E = B->Get_left();

	Node* psParent = p->Get_parent();

	//Set B's parent to p's parent. Could be a node or NULL
	B->Set_parent(psParent);

	//Set p's right child to E. Could be a node or NULL
	p->Set_right(E);

	//If E is a node and not NULL, set its parent to p
	if(E != NULL) E->Set_parent(p);

	//Set p's parent to B
	p->Set_parent(B);

	//Set B's left to p
	B->Set_left(p);

	//If B's parent is not NULL, this tree was not rotated at the root
	if(psParent != NULL){

		if(psParent->Get_left() == NULL){
			B->Get_parent()->Set_right(B);
		}
		else if(psParent->Get_right() == NULL){
			B->Get_parent()->Set_left(B);
		}
		else{
			if(psParent->Get_left()->Get_key() == p->Get_key()){
				B->Get_parent()->Set_left(B);
			}
			else{
				B->Get_parent()->Set_right(B);
			}
		}
	}
	
	//If B's parent is NULL, A is the new root
	else{ 
		root = B;
	}

	return B;
}

// This function checks if there 
// is a violation at a node p, and 
// return the violation scenario. 
// It returns a string of 
// - "NO" if no violation 
// - "LL" if it is left-left violation 
// - "RR" if it is right-right violation
// - "LR" if it is left-right violation
// - "RL" if it is right-left violation
string AVL::CheckViolation(Node* p){
	
	//Get the balance of p with helper function
	int pBalance = Balance(p);

	int pLeftBal, pRightBal;

	//Get the balance of p's left child
	if(p->Get_left() != NULL){
		pLeftBal = Balance(p->Get_left());
	}
	else{
		pLeftBal = 0;
	}

	//Get the balance of p's right child
	if(p->Get_right() != NULL){
		pRightBal = Balance(p->Get_right());
	}
	else{
		pRightBal = 0;
	}
	
	//If there is a violation, determine case

	//Left-Left
	if(pBalance > 1 && pLeftBal >= 0){
		return "LL";
	}
	//Right-Right
	else if(pBalance < -1 && pRightBal <= 0){
		return "RR";
	}
	//Left-Right
	else if(pBalance > 1 && pLeftBal < 0){
		return "LR";
	}
	else if(pBalance < -1 && pRightBal > 0){
		return "RL";
	}
	else{
		return "NO";
	}
}

//Balance helper function
int AVL::Balance(Node* p){
	
	int leftHeight, rightHeight;

	//Get height of left subtree
	leftHeight = Height(p->Get_left());

	//Get height of right sub tree
	rightHeight = Height(p->Get_right());

	int balance = leftHeight - rightHeight;

	return balance;
}

//Constructor
AVL::AVL(){
	root = NULL;
}

// --------------
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

		temp = new Node;
		temp->Set_key(key_temp);

		if (mode_avl == 0)
		{
			tree.Add(temp);
		}
		else if (mode_avl == 1) {
			tree.Add_AVL(temp);
		}
	}

	// Mode 0: test "Add" function.
	if (mode_test == 0) {
		tree.PreTraverse();
	}
	// Mode 1: test "Add_AVL" function
	else if (mode_test == 1) {
		tree.PreTraverse();
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
		tree.PreTraverse();
	}
	// Mode 4: test "Remove_AVL" function 
	else if (mode_test == 4) {
		tree.Remove_AVL(key_search);
		tree.PreTraverse();
	}
	// Mode 5: test "Height" function 
	else if (mode_test == 5) {
		cout << tree.Height(tree.GetRoot());
	}
	
	return 0;
}

