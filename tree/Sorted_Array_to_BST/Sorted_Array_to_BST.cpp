/******************************************************************************
排序過陣列轉二元搜尋樹之演算法
1)取陣列中中央元素作為二元搜尋樹的樹根
2)以遞迴方式追蹤並建立左子樹和右子樹
3)重覆第一步驟

Sorted Array to Balanced BST Algorithm
1) Get the Middle of the array and make it root.
2) Recursively do same for left half and right half.

時間複雜度:O(n)	Time Complexity:O(n)
*******************************************************************************/
#include <iostream>
using namespace std;

typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
}NodeTree;

NodeTree *NewNode(int data){
	NodeTree *new_node = (NodeTree*)malloc(sizeof(NodeTree));
	new_node->data = data;
	new_node->left = new_node->right = NULL;
	return new_node;
}

NodeTree *sortedArrayToBST(int arr[],int front,int end){
	if(front>end)
		return NULL;
	NodeTree *node = NewNode(arr[(front+end)/2]);
	node -> left = sortedArrayToBST(arr,front,((front+end)/2)-1);
	node -> right = sortedArrayToBST(arr,((front+end)/2)+1,end);
	return node;
}

void Print_Preorder(NodeTree *node){
    if(!node)
        return;
	cout<<node->data<<',';
	Print_Preorder(node -> left);
	Print_Preorder(node -> right);
}   

int main(){
	int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
	int arr_size = sizeof(arr)/sizeof(*arr); 
	NodeTree *node = sortedArrayToBST(arr,0,arr_size-1);
	Print_Preorder(node);
	return 0;
}