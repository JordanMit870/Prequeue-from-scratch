#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
 public:
  struct NODE {
    int priority;
    T value;
    NODE* parent;
    NODE* left;
    NODE* right;
    NODE* link;  // Link to duplicates -- Part 2 only
  };

 private:
  NODE* root;
  size_t sz;

  // Utility pointers for begin and next.
  NODE* curr;
  NODE* temp;  // Optional

  // TODO_STUDENT: add private helper function definitions here
 void clearRecursion(NODE* currNode) const { //needs to take curr input
    if(currNode == nullptr){
      return;
    }
    clearRecursion(currNode->left);
    clearRecursion(currNode->right);
   
    while(currNode!= nullptr){ //to delete all duplicates
      NODE* currTemp = currNode;
      currNode = currNode->link;
      delete currTemp;
    }
    
    
    // delete currNode; //not needed anymore. Handled above

  }

 void asStringRecursion(NODE* curr, ostringstream &final) const { //adds to the string
    if(curr == nullptr){
      return;
    }
    asStringRecursion(curr->left, final); 
    final << to_string(curr->priority) <<" value: " << curr->value << "\n"; //may need to change spacing...
    asStringRecursion(curr->link, final);
    asStringRecursion(curr->right, final);
   

  }

  T peekRecursion(NODE* curr) const{
    if(curr-> left == nullptr ){ //bottom of the list
      return curr->value;
    }
    return peekRecursion(curr->left); //used to pass back the last node
  }

  T dequeueRecursion(NODE* curr){ //issue is here...
    if(curr-> left == nullptr ){ //bottom of the list
      if(curr->link != nullptr){ //if linked node exists also is the issue
        T val = curr->value;
        if(curr->parent != nullptr){ //if parent exists
          if(curr->parent->priority > curr->priority){
            curr->parent->left = curr->link;
          }
          else{
            curr->parent->right = curr->link;
          }
          curr->link->parent = curr->parent;
         }
         if(curr == root){ //if linked list is root
          root = curr->link;
          curr->link->parent = nullptr;
         }
        if(curr->right !=nullptr){ //if right node exists
          curr->right->parent = curr->link;
          curr->link->right = curr->right;
        }
        delete curr;
        curr = nullptr;
        return val;
    }
      if(curr == this->root){ //If the root is the lowest node
        if(root->right == nullptr){ //if there is no child
          //issue...
          T val = curr->value;
          delete curr;
          this->root = nullptr;
          return val;
        }
        else{ //if there is a child in the root 
          this->root = curr-> right;
          curr->right->parent = nullptr;
          T val = curr->value;
          delete curr; //maybe because I'm deleting the root?
          return val;
        }
      }
      else if(curr->right != nullptr){ //if right node exists
        curr->right->parent = curr->parent; //
        curr->parent->left = curr->right;
        T val = curr->value;
        delete curr;
        return val;
      }
      //lowest left root
      T val = curr->value;
      curr->parent->left = nullptr;
      delete curr; 
      return val;
    }
    return dequeueRecursion(curr->left); //used to pass back the last node
  }
  
  NODE* copyRecursion(NODE* oldCurr){
     if(oldCurr == nullptr){
      return nullptr;
    }

    NODE* newNode = new NODE; //to make space
    newNode->value = oldCurr->value;
    newNode->priority = oldCurr->priority;
    newNode->left = copyRecursion(oldCurr->left);
    newNode->link = copyRecursion(oldCurr->link);
    newNode->right = copyRecursion(oldCurr->right);

    if(newNode->left != nullptr){
      newNode->left->parent = newNode;
    }
    if(newNode->right != nullptr){
      newNode->right->parent = newNode;
    }
    return newNode;

  }

  bool equalHelper(NODE* root, NODE* other) const {
    if(root == nullptr && other == nullptr){
      return true;
    }
    
   if((root->value == other->value) && (root->priority == other->priority)){
      if(equalHelper(root->left,other->left) == false){
        return false;
      }
      if( equalHelper(root->link,other->link) == false){
        return false;
      }
      if( equalHelper(root->right,other->right) == false){
        return false;
      }
      return true;
   }

   return false;
    
  }

  NODE* highestPriority(NODE* curr) { //issue here...
    if(curr == nullptr){
      return nullptr;
    }
    if(curr->left == nullptr ){ //bottom of the list
      return curr;
    }
    return highestPriority(curr->left); //used to pass back the last node
  }


 public:
  /// Creates an empty `prqueue`.
  ///
  /// Runs in O(1).
  prqueue() {
    // TODO_STUDENT
    // this-> priority = 0;
    // this-> value = null;
    // this->parent = nullptr;
    // this->left = nullptr;
    // this->right = nullptr

    this->sz = 0;
    this->root = nullptr;
    this->curr = nullptr;


  }

  /// Returns the number of elements in the `prqueue`.
  ///
  /// Runs in O(1).
  size_t size() const {
    // TODO_STUDENT
    return this->sz;
  }

  /// Returns a pointer to the root node of the BST.
  ///
  /// Used for testing the internal structure of the BST. Do not edit or
  /// change.
  ///
  /// Runs in O(1).
  NODE* getRoot() {
    // TODO_STUDENT
    return this->root;
  }

  /// Adds `value` to the `prqueue` with the given `priority`.
  ///
  /// Uses the priority to determine the location in the underlying tree.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  void enqueue(T value, int priority) { 
    // TODO_STUDENT
    NODE* newNode = new NODE; //to make space
    newNode->value = value;
    newNode->priority = priority;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    newNode->link = nullptr;
   
    if(this->root == nullptr){ //if empty
    
      this->root = newNode;
      sz++;
    }
    else{
     NODE* currNode =  getRoot(); //so I can iterate through?
     
      while(currNode != nullptr){
        if(newNode->priority < currNode->priority){ //go left
            if(currNode->left == nullptr){
              currNode->left = newNode;
              newNode->parent =currNode;
               sz++;
               return;
            }
            else{
              currNode = currNode->left;
            }
          }
        else if(newNode->priority == currNode->priority){ //All duplicents 
            newNode->parent = currNode;
          while(currNode->link != nullptr){
            currNode = currNode->link;
          }
          currNode->link = newNode;
          sz++;
          return;
        }
        else if(newNode->priority > currNode->priority){//go right
        // else{ //goes right and will grab duplicets I think
            if(currNode->right == nullptr){
            currNode->right = newNode;
            newNode->parent = currNode;
            sz++;
             return;
          }
          else{
            currNode = currNode->right;
            }
          }
       
       }
    }
  }

  /// Returns the value with the smallest priority in the `prqueue`, but does
  /// not modify the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  T peek() const { //make a helper that returns the node. Then I can also use it for dequeue
    // TODO_STUDENT
    if(root == nullptr){
      return T{};
    }
    T lastNode;
    lastNode = peekRecursion(root);
    return lastNode;
  }
 
  /// Returns the value with the smallest priority in the `prqueue` and
  /// removes it from the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  T dequeue() {
    // TODO_STUDENT
    if(root == nullptr){
      return T{};
    }
    
    T lastNode;
    NODE* tempCurr = root;
    lastNode = dequeueRecursion(tempCurr);
    // delete tempCurr;
    // tempCurr = nullptr;
    sz--;
    return lastNode;
  }
 

  /// Converts the `prqueue` to a string representation, with the values
  /// in-order by priority.
  ///
  /// Example:
  ///
  /// ```c++
  /// prqueue<string> names;
  /// names.enqueue("Gwen", 3);
  /// names.enqueue("Jen", 2);
  /// names.enqueue("Ben", 1);
  /// names.enqueue("Sven", 2);
  /// ```
  ///
  /// Calling `names.as_string()` would return the following multi-line
  /// string:
  ///
  /// ```text
  /// 1 value: Ben
  /// 2 value: Jen
  /// 2 value: Sven
  /// 3 value: Gwen
  /// ```
  ///
  /// Runs in O(N), where N is the number of values.
  string as_string() const { //make recursion helper function
    // TODO_STUDENT 
    ostringstream final;
   asStringRecursion(root, final);

    return final.str();
  }
 
  /// Empties the `prqueue`, freeing all memory it controls.
  ///
  /// Runs in O(N), where N is the number of values.
  void clear() {
    // TODO_STUDENT
    //call helper funtion. delete what it returns
    if(this->root == nullptr){ // if empty
      return;
    }
      clearRecursion(this->root);
      this->root = nullptr;
      sz = 0;
  }
 

  /// Destructor, cleans up all memory associated with `prqueue`.
  ///
  /// Runs in O(N), where N is the number of values.
  ~prqueue() {
    // TODO_STUDENT
    clear();
  }

  /// Copy constructor.
  ///
  /// Copies the value-priority pairs from the provided `prqueue`.
  /// The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N), where N is the number of values in `other`.
  prqueue(const prqueue& other) {
    // TODO_STUDENT
    sz = 0;
    root = nullptr;

    if(other.size() != 0){
      NODE* oldCurr = other.root; // to iterate through
      sz = other.size();

      root = copyRecursion(oldCurr);  //send oldCurr into the function to add to new prequeu
      //recurrsion left
      //recurrion link
      //recurrsion right
      //update parents...
    }

  }
  
  /// Assignment operator; `operator=`.
  ///
  /// Clears `this` tree, and copies the value-priority pairs from the
  /// provided `prqueue`. The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N + O), where N is the number of values in `this`, and O is
  /// the number of values in `other`.
  prqueue& operator=(const prqueue& other) {
    
    // TODO_STUDENT
    if(this == &other){
      return *this;
    }
    clear();
    sz = 0;
    root = nullptr;

    if(other.size() != 0){
      NODE* oldCurr = other.root; // to iterate through
      sz = other.size();

      root = copyRecursion(oldCurr);  //send oldCurr into the function to add to new prequeu
      //recurrsion left
      //recurrion link
      //recurrsion right
      //update parents...
    }
    return *this;
  }

  /// Checks if the contents of `this` and `other` are equivalent.
  ///
  /// Two `prqueues` are equivalent if they have the same priorities and
  /// values, as well as the same internal tree structure.
  ///
  /// These two `prqueue`s would be considered equivalent, because
  /// they have the same internal tree structure:
  ///
  /// ```c++
  /// prqueue<string> a;
  /// a.enqueue("2", 2);
  /// a.enqueue("1", 1);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// and
  ///
  /// ```c++
  /// prqueue<string> b;
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// a.enqueue("1", 1);
  /// ```
  ///
  /// While this `prqueue`, despite containing the same priority-value pairs,
  /// would not be considered equivalent, because the internal tree structure
  /// is different.
  ///
  /// ```c++
  /// prqueue<string> c;
  /// a.enqueue("1", 1);
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// Runs in O(N) time, where N is the maximum number of nodes in
  /// either `prqueue`.
  ///
  bool operator==(const prqueue& other) const {
    // TODO_STUDENT function
    if(size() != other.size()){
      return false;
    }
    //send roots through the

    return equalHelper(root, other.root);
    // return false;
  }

 
  /// Resets internal state for an iterative inorder traversal.
  ///
  /// See `next` for usage details.
  ///
  /// O(H), where H is the maximum height of the tree.
  void begin() { //idk what I'm doing??!!??
    // TODO_STUDENT
    curr = highestPriority(root); //gives me lowest node/highest priority
    // next(curr->value, curr->priority);
  }
 
  /// Uses the internal state to return the next in-order value and priority
  /// by reference, and advances the internal state. Returns true if the
  /// reference parameters were set, and false otherwise.
  ///
  /// Example usage:
  ///
  /// ```c++
  /// pq.begin();
  /// T value;
  /// int priority;
  /// while (pq.next(value, priority)) {
  ///   cout << priority << " value: " << value << endl;
  /// }
  /// ```
  ///
  /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
  /// H is the height of the tree, and M is the number of duplicate
  /// priorities.
  bool next(T& value, int& priority) { //help-
    // TODO_STUDENT
    if (curr == nullptr) {
      return false;
    }
    //update values before move
    value = curr->value;
    priority = curr->priority;
    //everything below is after moving the node. No need to update

    if(curr->link != nullptr){
      curr = curr->link;
      return true;
    }

    while(curr->parent != nullptr && curr->priority == curr->parent->priority){
      curr = curr-> parent; //previous nodes are link's parents
    }

    if(curr->right != nullptr){
      curr = curr->right;
      while(curr->left != nullptr){
        curr = curr->left;
      }
      return true;
    }
    else{ //for parents and root node
        while(curr->parent != nullptr){
          if(curr != curr->parent->right){ //if I don't need to skip a node
            curr = curr->parent;
            return true;
          }
          curr = curr->parent;
        }
        curr =  nullptr; //back to the root
        return true;
      }

   // do in order traversal to set the "curr" variable
   // Also check for duplicates!!
    return false;
  }


};
