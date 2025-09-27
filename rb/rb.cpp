#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	ptr x=start;
	ptr y;
	while (x)
	{
		y=x;
		if(x->data>newnodePtr->data)x=x->left;
		else x=x->right;
	}
	if(y->data<newnodePtr->data){
		y->right=newnodePtr;
		y->right->color=1;
		newnodePtr->parent=y;
	}
	else{
		y->left=newnodePtr;
		y->left->color=1;
		newnodePtr->parent=y;
	}
	// recurse down the tree
	fixup(newnodePtr);
	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	if(!loc->left)return ;
	ptr x=loc->left->right;
	ptr g=loc->parent;
	ptr p=loc->left;
	p->right=loc;
	loc->left=x;
	if(x)x->parent=loc;
	if(!g){
		root=p;
		p->parent=nullptr;
	}
	else if(g->right==loc){
		p->parent=g;
		g->right=p;
	}
	else{
		p->parent=g;
		g->left=p;
	}
	loc->parent=p;
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	if(!loc->right)return ;
	ptr x=loc->right->left;
	ptr p=loc->right;
	ptr g=loc->parent;
	p->left=loc;
	loc->right=x;
	if(x)x->parent=loc;
	if(!g){
		root=p;
		p->parent=nullptr;
	}
	else if(g->right==loc){
		p->parent=g;
		g->right=p;
	}
	else{
		p->parent=g;
		g->left=p;
	}
	loc->parent=p;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{
	if(!loc->parent){
		loc->color=0;
		return ;
	}
	if(loc->parent->color==0)return ;
	if(!loc->parent->parent){
		loc->parent->color=0;
		return ;
	}
	ptr gp=loc->parent->parent;
	ptr p=loc->parent;
	if(gp->right==p){
		if(gp->left && gp->left->color==1){
			p->color=0;
			gp->color=1;
			gp->left->color=0;
			fixup(gp);
		}
		else{
			if(p->right==loc){
				leftrotate(gp);
				gp->color=1;
				p->color=0;
				loc->color=1;
			}
			else{
				rightrotate(p);
				fixup(loc);
			}
		}
	}
	else{
		if(gp->right && gp->right->color==1){
			p->color=0;
			gp->color=1;
			gp->right->color=0;
			fixup(gp);
		}
		else{
			if(p->left==loc){
				rightrotate(gp);
				gp->color=1;
				p->color=0;
				loc->color=1;
			}
			else{
				leftrotate(p);
				fixup(loc);
			}
		}
	}

}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}


