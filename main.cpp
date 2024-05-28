#include <iostream>
using namespace std;

struct node {
  int data;
  node* left;
  node* right;
};

class BST
{
  node* root;
  node* findNode(node*, int);
  node* findMin(node*);
  node* findMax(node*);
  node* removeNode(node*, int);
  void insertNode(node*, int);
  void destroyTree(node*);
  void inOrder(node*);
  void preOrder(node*);
  void postOrder(node*);
   bool isLeafNode(node*);

public:
  BST();
  ~BST();
  void insertNode(int);
  void destroyTree();
  void display();
  node* removeNode(int);
  node* findNode(int);
  node* getRoot();
  int maxdepth();
};

BST::BST()
{
  root = NULL;
}

BST::~BST()
{
  destroyTree();
}

void BST::insertNode(int key)
{
  if (root != NULL) {
    insertNode(root, key);
  } else {
    root = new node;
    root->data = key;
    root->left = NULL;
    root->right = NULL;
  }
}

void BST::insertNode(node* leaf, int key)
{
  if (key < leaf->data){
    if (leaf->left != NULL) {
      insertNode(leaf->left, key);
    } else {
      leaf->left = new node;
      leaf->left->data = key;
      leaf->left->left = NULL;
      leaf->left->right = NULL;
    }
  } else {
    if (leaf->right != NULL) {
      insertNode(leaf->right, key);
    } else {
      leaf->right = new node;
      leaf->right->data = key;
      leaf->right->left = NULL;
      leaf->right->right = NULL;
    }
  }
}

node* BST::findNode(int key)
{
  // start from the root
  return findNode(root, key);
}

node* BST::findNode(node* leaf, int key)
{
  if (leaf == NULL) {
    return NULL;
  } else if (key == leaf->data) {
      return leaf;
  } else if (key < leaf->data){
    return findNode(leaf->left, key);
  } else return findNode(leaf->right, key);
}

node* BST::removeNode(int key)
{
  return removeNode(root, key);
}

node* BST::removeNode(node* t, int key)
{
  node* temp;

  // base case with empty node
  if (t == NULL)
    return NULL;

  if (key < t->data) {
    t->left = removeNode(t->left, key); // look in left subtree
  } else if (key > t->data) {
    t->right = removeNode(t->right, key); // look in right subtree
  }
  else {
  // key has been found.
  if (isLeafNode(t)){
    delete t;
    t = NULL;
  } else if (t->right && t->left) {
    // removing a node with two childen is tricky.
    // first we find the minimum leaf on the right side of the node we're deleting.
    // copy the data from the mimimum node to the node we're deleting.
    // finally delete the minimum node in the right subtree.
    node* temp = findMin(t->right);
    t->data = temp->data;
    t->right = removeNode(t->right, t->data);
  } else {
    temp = t;
    if (t->right == NULL)
      t = t->left;
    else if (t->left == NULL)
      t = t->right;
      delete temp;
    }
  }
  // eventually returns root node after node removal completes
  return t;
}

bool BST::isLeafNode(node* t)
{
  if (t != NULL && t->left == NULL && t->right == NULL)
    return true;
  else return false;
}

// find minimum
node* BST::findMin(node* t)
{
  if (t== NULL)
    return t;
  else if (t->left == NULL)
    return t;
  else return findMin(t->left);
}

node* BST::findMax(node* t)
{
  if (t == NULL)
    return t;
  else if (t->right == NULL)
    return t;
  else return findMax(t->right);
}

void BST::destroyTree()
{
  destroyTree(root);
}

void BST::destroyTree(node* leaf)
{
  if (leaf != NULL) {
    destroyTree(leaf->left);
    destroyTree(leaf->right);
  }

  delete leaf;
}

void BST::inOrder(node* t)
{
  if (t != NULL) {
    inOrder(t->left);
    cout << t->data <<" ";
    inOrder(t->right);
  }
}
//1. //The above code returns sorted list in ascending order

void BST::preOrder(node* t)
{
  if (t != NULL) {
    cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
  }
}

void BST::postOrder(node* t)
    {
  if (t != NULL) {
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << " ";
  }
}
void BST::display()
{
  cout<<"preOrder: ";
  preOrder(root);
  cout<<"\ninOrder: ";
  inOrder(root);
  cout<<"\npostOrder: ";
  postOrder(root);
}

// returns the max root-to-leaf depth of the tree.
// O(n)
int maxDepth(node* t)
{
  if (t == NULL) {
    return 0;
  } else {
    int ld = maxDepth(t->left);
    int rd = maxDepth(t->right);

    return (max(ld, rd) + 1);
  }
}

node* BST::getRoot()
{
  return root;
}

int main() {

  BST* tree = new BST();
  tree->insertNode(50);
  tree->insertNode(19);
  tree->insertNode(28);
  tree->insertNode(40);
  tree->insertNode(16);
  tree->insertNode(70);
  tree->insertNode(55);
  tree->insertNode(56);
  tree->insertNode(17);
  tree->insertNode(90);
  tree->display();
  cout<<"\n"<<"The depth of the tree is "<<maxDepth(tree->getRoot());

  delete tree;
  return 0;
}
