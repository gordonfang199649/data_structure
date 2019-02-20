/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream> 
using namespace std;

typedef struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
	int height;
}NodeTree;

NodeTree *new_node(int data){
	NodeTree *node = (NodeTree*)malloc(sizeof(NodeTree));
	node->data = data;
	node->left = node->right = NULL;
	node->height = 1; //基本高度
	return node;
}

int height(NodeTree *node){ //取得高度
	if(!node)
		return 0;
	return node->height;
}

int max(int a, int b){
	return (a>b)?a:b;
}

int get_blance(NodeTree *node){ 
	if(!node)
		return 0;
	return height(node->left) - height(node->right); //計算每個節點的高度 公式=左子樹高度-右子樹高度
}

NodeTree *left_rotation(NodeTree *x){
//     		x         		 y
//         /  \       		/  \ 
//        T3   y    ->	   x    z
//      	 /  \     	  /  \
//          T2   z  	 T2  T3
// z節點不隨之調整	
	NodeTree *y = x->right;
	NodeTree *T2 = y->left;
	y->left = x;
	x->right = T2;
	//更新新的根節點、與新的左子樹高度
	x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
    return y; //回傳新的樹根
}


NodeTree *right_rotation(NodeTree *y){
//     		y         		 x
//         /  \       		/  \ 
//        x   T3    ->	   z    y
//      /  \     			  /  \
//     z   T2    			 T2  T3
// z節點不隨之調整	
	NodeTree *x = x->left;
	NodeTree *T2 = y->right;
	x->right = y;
	y->left = T2;
	//更新新的根節點、與新的左子樹高度
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    return x; //回傳新的樹根
}

NodeTree *insert(NodeTree *node,int data){
	if(!node)
		return new_node(data);
	if(data<node->data)
		node->left = insert(node->left,data);
	else if(data>node->data)
		node->right = insert(node->right,data);
	else
		return node;

	node->height =  1 + max(height(node->left), height(node->right)); 
	int balance = get_blance(node);
	//LL case -> 右旋轉
	if(balance>1 && data<node->left->data)
		return right_rotation(node);

	//LR case -> 左旋轉 -> 右旋轉
	if(balance>1 && data>node->left->data){
		left_rotation(node);
		return right_rotation(node);
	}

	//RR case -> 左旋轉
	if(balance<-1 && data>node->right->data)
		return left_rotation(node);

	//RL case -> 右旋轉 -> 左旋轉
	if(balance<-1 && data<node->right->data){
		right_rotation(node);
		return left_rotation(node);
	}
}

void Print_PreOrder(NodeTree *node){
	if(!node)
		return;
	cout<<node->data<<',';
	Print_PreOrder(node->left);
	Print_PreOrder(node->right);
}

int main(){ 
  NodeTree *root = NULL; 
  root = insert(root, 10); 
  root = insert(root, 20); 
  root = insert(root, 30); 
  root = insert(root, 40); 
  root = insert(root, 50); 
  root = insert(root, 25);
  cout<<"Preorder traversal of the constructed AVL tree is"<<endl; 
  Print_PreOrder(root); 
  
  return 0; 
} 