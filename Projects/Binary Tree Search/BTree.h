//######################################################
//
// Binary Search Tree Class
//
//######################################################
#ifndef _MODULE_BTREE_
#define _MODULE_BTREE_

//######################################################
//
// Includes and Defines
//
//######################################################
#include "WordRef.h"

//######################################################
//
// Binary Search Tree Node Structure Definition
//
//######################################################

struct BTNodeType
{
	WordRef data;
	BTNodeType *left;
	BTNodeType *right;
	BTNodeType *parent;
};
typedef BTNodeType * BTType;

//######################################################
//
// Binary Search Tree Class Definition
//
//######################################################

class BTree
{
	public:
	
	// default constructor, copy constructor, overloaded assignment operator
		BTree();
		BTree( const BTree &other );
		BTree& operator=( const BTree &other );
		
	// destructor
		~BTree();
		
	// mutator methods
		void bt_insert( const WordRef& d );
		void bt_destroyTree();
	
	// accessor methods, other methods
		void bt_isTreeEmpty() const;
		int bt_nodeCount() const;
		int bt_treeHeight() const;
		void bt_inorderTraversal( ofstream& outFile ) const;
		void bt_preorderTraversal( ofstream& outFile ) const;
		void bt_postorderTraversal( ofstream& outFile ) const;
		BTType bt_search( const string& d ) const;
		
	private:
	
		BTNodeType *root;
		void bt_destroy( BTType bt );
		void bt_copy( BTType B, const BTType A );
		int bt_count( const BTType bt ) const;
		int bt_height( const BTType bt ) const;
		void bt_inorder( ofstream& file, const BTType bt ) const;
		void bt_preorder( ofstream& file, const BTType bt ) const;
		void bt_postorder( ofstream& file, const BTType bt ) const;
		bool bt_IsEmpty( const BTType bt ) const;
		int max( int x, int y ) const;
};

//######################################################
//
// Default Constructor
//
//######################################################
BTree::BTree()
{
	root = NULL;
}

//######################################################
//
// Copy Constructor
//
//######################################################
BTree::BTree( const BTree &other )
{
	if( other.root==NULL )
		root = NULL;
	else
		bt_copy( root, other.root );
}

//######################################################
//
// Assignment Operator (bt=bt)
//
//######################################################
BTree& BTree::operator=( const BTree &other )
{
	if( this != &other )
	{
		if( root != NULL )
			bt_destroy( root );
	
		if( other.root == NULL )
			root = NULL;
		else
			bt_copy( root, other.root );
	}
	
	return( *this );
}

//######################################################
//
// Destructor
//
//######################################################
BTree::~BTree()
{
	bt_destroy( root );
}

//######################################################
//
// Insert Method
//
//######################################################
void BTree::bt_insert( const WordRef& d ) 
{
	// create a new node
	BTType nn;
	BTType cur, prev;
	nn = cur = prev = NULL;
	nn = new BTNodeType;
	nn->data = d;
	nn->left = NULL;
	nn->right = NULL;
	nn->parent = NULL;

	// search for where to insert the node
	cur = root;
	prev = NULL;
	while( !bt_IsEmpty(cur) )
	{
		prev = cur;
		if( d.GetWord() < cur->data.GetWord() )
			cur = cur->left;
		else
			cur = cur->right;
	} // @ end of loop, cur=NULL and prev is a leaf node


	// set parent pointer for new node
	nn->parent = prev;


	// insert the node
	if( bt_IsEmpty(prev) )
		root = nn;
	else if( d.GetWord() < prev->data.GetWord() )
		prev->left = nn;
	else
		prev-> right = nn;
}

//######################################################
//
// Destroy Tree Method
//
//######################################################
void BTree::bt_destroyTree()
{
	bt_destroy( root );
}

//######################################################
//
// Is Tree Empty Method
//
//######################################################
void BTree::bt_isTreeEmpty() const
{
	bt_IsEmpty( root );
}

//######################################################
//
// Node Count Method
//
//######################################################
int BTree::bt_nodeCount() const
{
	bt_count( root );
}

//######################################################
//
// Tree Height Method
//
//######################################################
int BTree::bt_treeHeight() const
{
	bt_height( root );
}

//######################################################
//
// In Order Traversal Method
//
//######################################################
void BTree::bt_inorderTraversal( ofstream& file ) const
{
	bt_inorder( file, root );
}

//######################################################
//
// Pre Order Traversal Method
//
//######################################################
void BTree::bt_preorderTraversal( ofstream& file ) const
{
	bt_preorder( file, root );
}

//######################################################
//
// Post Order Traversal Method
//
//######################################################
void BTree::bt_postorderTraversal( ofstream& file ) const
{
	bt_postorder( file, root );
}

//######################################################
//
// Search Method
//
//######################################################
BTType BTree::bt_search( const string& d ) const
{
	BTType cur;
	cur = root;

	while( !bt_IsEmpty( cur ) && (d != cur->data.GetWord()) )
	{
		if( d < cur->data.GetWord() )
			cur = cur->left;
		else
			cur = cur->right;
	}
	
	return( cur );
}

//######################################################
//
// Destroy Method
//
//######################################################
void BTree::bt_destroy( BTType bt )
{
	if( !bt_IsEmpty(bt) )
	{
		bt_destroy(bt->left);
		bt_destroy(bt->right);
		delete bt;
		bt = NULL;
	}
}

//######################################################
//
// Copy Method
//
//######################################################
void BTree::bt_copy( BTType B, const BTType A )
{
	if( bt_IsEmpty(A) ) 
	    B = NULL;
	else
	{
		B = new BTNodeType;
		B->data = A->data;
		bt_copy( B->left, A->left );
		bt_copy( B->right, A->right );
	}
}

//######################################################
//
// Count Method
//
//######################################################
int BTree::bt_count( const BTType bt ) const
{
	if( bt_IsEmpty(bt) )
		return 0;
	else
		return( 1 + bt_count(bt->left) + bt_count(bt->right) );
}

//######################################################
//
// Height Method
//
//######################################################
int BTree::bt_height( const BTType bt ) const
{
	if( bt_IsEmpty(bt) )
		return 0;
	else
		return( 1 + max( bt_height(bt->left), bt_height(bt->right) ) );
}

//######################################################
//
// In Order Method
//
//######################################################
void BTree::bt_inorder( ofstream& file, const BTType bt ) const
{
	if( !bt_IsEmpty(bt) )
	{
		bt_inorder( file, bt->left);
		bt->data.printWord( file );
		bt_inorder( file, bt->right);
	}
}

//######################################################
//
// Pre Order Method
//
//######################################################
void BTree::bt_preorder( ofstream& file, const BTType bt) const
{
	if( !bt_IsEmpty(bt) )
	{
		bt-> data.printWord( file );
		bt_preorder( file, bt->left);
		bt_preorder(file, bt->right);
	}
}

//######################################################
//
// Post Order Method
//
//######################################################
void BTree::bt_postorder( ofstream& file, const BTType bt) const
{
	if( !bt_IsEmpty(bt) )
	{
		bt_postorder(file, bt->left);
		bt_postorder(file, bt->right);
		bt->data.printWord( file );
	}
}

//######################################################
//
// IsEmpty Method
//
//######################################################
bool BTree::bt_IsEmpty( const BTType bt ) const
{
	return( (bt == NULL) ? true : false );
}

//######################################################
//
// Max Method
//
//######################################################
int BTree::max( int x, int y ) const
{
	if( x >= y )
		return(x);
	else
		return(y);
}

#endif
