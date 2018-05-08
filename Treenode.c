#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode {	// ���� �ڷᱸ���� �����ϱ� ���� Ʈ���� ��� ����
	char data;
	struct treeNode *left;  // ���� ���� Ʈ���� ���� ��ũ �ʵ�
	struct treeNode *right; // ������ ���� Ʈ���� ���� ��ũ �ʵ�
} treeNode;

treeNode* makeRootNode(char data, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));
	root->data = data;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

typedef treeNode * Data;

typedef struct _qnode{
    Data data;
    struct _qnode *next;
} QNode;
typedef struct _queue{
    QNode * front;
    QNode * rear;
} Queue;
 
void QueueInit(Queue * pq){
    pq->front = NULL;
    pq->rear = NULL;
}
void enqueue(Queue * pq, Data data){
    QNode * newNode = (QNode *)malloc(sizeof(QNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if(pq->front == NULL){
        pq->front = newNode;
        pq->rear = newNode;
    }else{
        pq->rear->next = newNode;
        pq->rear = newNode;
    }
}
Data dequeue(Queue * pq){
    if(pq->front == NULL){
        return NULL;
    }
    QNode * delNode = pq->front;
    Data data = delNode->data;
    pq->front = pq->front->next;
    
    free(delNode);
    return data;
}

// ���� Ʈ���� ���� ���� ��ȸ ����
void preorder(treeNode* root) {
	if (root) {
		printf("%c", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// ���� Ʈ���� ���� ���� ��ȸ ����
void inorder(treeNode* root) {
	if (root) {
		inorder(root->left);
		printf("%c", root->data);
		inorder(root->right);
	}
}

// ���� Ʈ���� ���� ���� ��ȸ ����
void postorder(treeNode* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%c", root->data);
	}
}

treeNode * readtree(void)
{
	char	c;
	treeNode	*tmp;

	switch (c = getchar()) {
	case '(':
		fprintf(stderr, "Wrong input format(-1).\n");
		exit(-1);
	case ',':
	case ')':
		return(NULL);
	default:
		tmp = (treeNode *) malloc(sizeof(treeNode));
		tmp->data = c;
	}

	switch (c = getchar()) {
	case '(':
		tmp->left = readtree();
		tmp->right = readtree();
		getchar();	// scan ')'
		return(tmp);
	case ',':
	case ')':
	case '\n':
		tmp->left = NULL;
		tmp->right = NULL;
		return(tmp);
	default:
		fprintf(stderr, "Wrong input format(-2).\n");
		exit(-2);
	}
}

void levelorder(treeNode* root) {
   if(root == NULL) return;
    Data data;
    Queue q;
    QueueInit(&q);
    enqueue(&q, root);
    while(1){
        data = dequeue(&q);
        if(data == NULL) break;
        printf("%c", data->data);
 
        if(data->left != NULL){
            enqueue(&q, data->left);
        }
        if(data->right != NULL){
            enqueue(&q, data->right);
        }    
    }

}

void printtree(treeNode* root) {
	if(root) {
		printf("%c", root->data);
		if (root->left != 0) {
			printf("(");
			printtree(root->left);
			printf(", ");
		}
		if (root->right != 0) {
			printtree(root->right);
			printf(")");
		}
	}
}

int treeheight(treeNode* root) {
	if (!root)
    return 0;
  else {
    int left_h = treeheight(root->left); // ���� ����Ʈ���� ���̸� ��ȯȣ���� ���� ��´�.
    int right_h = treeheight(root->right); // ���� ������� ������ ����Ʈ���� ���̸� ��´�.
    return 1 + (left_h > right_h ? left_h : right_h); // �� �� ū ���� 1�� ���� ��ȯ�Ѵ�.
  }
}

void main() {
    	/* ����: Ư��Ʈ������ ����� �ӽù������� ���
	// (A*B-C/D) ���� ���� Ʈ�� �����
	treeNode* n7 = makeRootNode('D', NULL, NULL);
	treeNode* n6 = makeRootNode('C', NULL, NULL);
	treeNode* n5 = makeRootNode('B', NULL, NULL);
	treeNode* n4 = makeRootNode('A', NULL, NULL);
	treeNode* n3 = makeRootNode('/', n6, n7);
	treeNode* n2 = makeRootNode('*', n4, n5);
	treeNode* n1 = makeRootNode('-', n2, n3);
	*/
	
	// node(LSubtree, RSubtree)�� ǥ���� ������ ����Ʈ���� �Է��ϴ� �Ϲ�ȭ�� ���
	treeNode* n1 = readtree();
	
	printf("\n preorder : ");
	preorder(n1);

	printf("\n inorder : ");
	inorder(n1);

	printf("\n postorder : ");
	postorder(n1);
	
	printf("\n levelorder : ");
	levelorder(n1);
	
	printf("\n list representation : "); // node(LSubtree, RSubtree)
	// �� Ʈ���� ��� -(*(A,B),/(C,D))
	printtree(n1);
	
	printf("\n tree height : %d\n", treeheight(n1));

	getchar();
}
