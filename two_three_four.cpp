#include "two_three_four.h"
#include<algorithm>
#include<vector>
// Fill in the missing functions

// -----------------------------
// BigNode constructor
// -----------------------------
BigNode::BigNode()
{
    A = -1;
    B = -1;
    C = -1;
    L = M1 = M2 = R = nullptr;
}
RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

struct node *RedBlackTree::getRoot()
{
    return root;
};

void RedBlackTree::setRoot(node *newroot)
{
    root = newroot;
}

// function to perform RBT insertion of a node
node *RedBlackTree::insert(node *trav,
                           node *temp)
{	
	if (!trav) { 
        root = temp;
        temp->p = nullptr;
        temp->l = temp->r = nullptr;
        temp->c = 1;
        fixup(temp);
        return root;
    }
    node* x=trav;
	node* y=nullptr;
	while (x)
	{
		y=x;
		if(x->d>temp->d)x=x->l;
		else x=x->r;
	}
	if(y->d<temp->d){
		y->r=temp;
		y->r->c=1;
		temp->p=y;
	}
	else{
		y->l=temp;
		y->l->c=1;
		temp->p=y;
	}
	// recurse down the tree
	fixup(temp);
    return root;
}

// Helper for pretty printing (internal; not in header)
// Credits to Adrian Schneider
static void printRBTHelper(node *n, const std::string &prefix, bool isLeft)
{
    if (!n)
        return;
    std::cout << prefix;
    std::cout << (isLeft ? "|--" : "|__");
    std::cout << n->d << "(" << (n->c == 0 ? "B" : "R") << ")" << std::endl;
    printRBTHelper(n->l, prefix + (isLeft ? "│   " : "    "), true);
    printRBTHelper(n->r, prefix + (isLeft ? "│   " : "    "), false);
}

void RedBlackTree::printRBT(const std::string &prefix, bool isLeft)
{
    // public wrapper prints from root; ignore args and use root for consistency
    (void)prefix;
    (void)isLeft;
    printRBTHelper(root, "", true);
}

void RedBlackTree::rightrotate(node *temp)
{ // Function performing right rotation of the passed node
    if(!temp->l)return ;
	node* x=temp->l->r;
	node* g=temp->p;
	node* p=temp->l;
	p->r=temp;
	temp->l=x;
	if(x)x->p=temp;
	if(!g){
		root=p;
		p->p=nullptr;
	}
	else if(g->r==temp){
		p->p=g;
		g->r=p;
	}
	else{
		p->p=g;
		g->l=p;
	}
	temp->p=p;
}

void RedBlackTree::leftrotate(node *temp)
{
    // Function performing l rotation of the passed node
    if(!temp->r)return ;
	node* x=temp->r->l;
	node* p=temp->r;
	node* g=temp->p;
	p->l=temp;
	temp->r=x;
	if(x)x->p=temp;
	if(!g){
		root=p;
		p->p=nullptr;
	}
	else if(g->r==temp){
		p->p=g;
		g->r=p;
	}
	else{
		p->p=g;
		g->l=p;
	}
	temp->p=p;
}

void RedBlackTree::fixup(node *pt)
{
    // This function fixes violations
    // caused by RBT insertion
    if(!pt->p){
		pt->c=0;
		return ;
	}
	if(pt->p->c==0)return ;
	if(!pt->p->p){
		pt->p->c=0;
		return ;
	}
	node* gp=pt->p->p;
	node* p=pt->p;
	if(gp->r==p){
		if(gp->l && gp->l->c==1){
			p->c=0;
			gp->c=1;
			gp->l->c=0;
			fixup(gp);
		}
		else{
			if(p->r==pt){
				leftrotate(gp);
				gp->c=1;
				p->c=0;
				pt->c=1;
			}
			else{
				rightrotate(p);
				fixup(pt);
			}
		}
	}
	else{
		if(gp->r && gp->r->c==1){
			p->c=0;
			gp->c=1;
			gp->r->c=0;
			fixup(gp);
		}
		else{
			if(p->l==pt){
				rightrotate(gp);
				gp->c=1;
				p->c=0;
				pt->c=1;
			}
			else{
				leftrotate(p);
				fixup(pt);
			}
		}
	}
}

void RedBlackTree::inorder(node *trav)
{ // Function to print inorder traversal of the fixated tree, no changes needed here keep it as it is
    if (!trav)
        return;
    inorder(trav->l);
    std::cout << trav->d << " ";
    inorder(trav->r);
}

TwoThreeFourTree::TwoThreeFourTree()
{ // no change needed here
    tree = new RedBlackTree();
}

void TwoThreeFourTree::insert(int key)
{
    // create new node here then insert and then fix
    node* x=new node;
	x->d=key;
	x->c=1;
	x->p=nullptr;
	x->r=nullptr;
	x->l=nullptr;
	
	
	tree->insert(tree->getRoot(),x);
	
}

// just a forward declaration
static BigNode *Convert(node *root);

BigNode *TwoThreeFourTree::convert()
{
    return Convert(tree->getRoot());
}

static BigNode *Convert(node *root)
{ // Convert RB to 2-3-4 BigNode structure
	if(!root)return nullptr;
	BigNode* fina=new BigNode();
	if(root->l && root->r){
		if(root->l->c==0 && root->r->c==0){
			fina->A=root->d;
			fina->L=Convert(root->l);
			fina->R=Convert(root->r);
		}
		else if(root->l->c==1 && root->r->c==0){
			fina->A=root->l->d;
			fina->B=root->d;
			fina->L=Convert(root->l->l);
			fina->R=Convert(root->r);
			fina->M1=Convert(root->l->r);
		}
		else if(root->l->c==0 && root->r->c==1){
			fina->A=root->d;
			fina->B=root->r->d;
			fina->L=Convert(root->l);
			fina->R=Convert(root->r->r);
			fina->M1=Convert(root->r->l);
		}
		else{
			fina->A=root->l->d;
			fina->B=root->d;
			fina->C=root->r->d;
			fina->L  = Convert(root->l->l);
			fina->M1 = Convert(root->l->r);   // swapped
			fina->M2 = Convert(root->r->l);   // swapped
			fina->R  = Convert(root->r->r);
		}
	}
	else if(root->l){
		if(root->l->c==0 ){
			fina->A=root->d;
			fina->L=Convert(root->l);
			fina->R=Convert(root->r);
		}
		else{
			fina->A=root->l->d;
			fina->B=root->d;
			
			fina->L=Convert(root->l->l);
			fina->M1=Convert(root->l->r);
			fina->R=Convert(root->r);
		}
	}
	else if(root->r){
		if(root->r->c==0 ){
			fina->A=root->d;
			fina->L=Convert(root->l);
			fina->R=Convert(root->r);
		}
		else{
			fina->A=root->d;
			fina->B=root->r->d;
			fina->L=Convert(root->l);
			fina->M1=Convert(root->r->l);
			fina->R=Convert(root->r->r);
		}
	}
	else{
		fina->A=root->d;
	}
	return fina;
}


void TTF(BigNode *root)
{
    if (!root)
        return;
    if (root->L)
        TTF(root->L);
    if (root->A != -1)
        std::cout << root->A << " ";
    if (root->M1)
        TTF(root->M1);
    if (root->B != -1)
        std::cout << root->B << " ";
    if (root->M2)
        TTF(root->M2);
    if (root->C != -1)
        std::cout << root->C << " ";
    if (root->R)
        TTF(root->R);

}
