#pragma once;

struct Node
{
	int data;
	Node* left;
	Node* right;
};

struct stackNode
{
	Node* info;
	stackNode* next;
};

struct queueNode
{
	Node* info;
	queueNode* next;
};

stackNode* newNode(Node* uz);
void push(stackNode** top, Node* uz);
Node* pop(stackNode** top);

queueNode* newQNode(Node* uz);
void enQueue(queueNode** start, Node* uz);
Node* deQueue(queueNode** start);

Node* newNode(int num);
void InitTree(Node** root, int num);
bool NullTree(Node* root);
Node* AddTree(Node* root, int num);
void FindTree(Node* root, int num, Node*& ad, Node*& adr);
Node* DelTreeUz(Node* root, int num);
Node* DelTreeP(Node* root, int num, char p);
void ViewTree1(Node* root);
void ViewTree2(Node* root);
void ViewTree3(Node* root);
void ViewTreeByLevel(Node* root);
void ViewTreeByLevelReversed(Node* root);