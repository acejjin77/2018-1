#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode {	// 연결 자료구조로 구성하기 위해 트리의 노드 정의
	char data;
	struct treeNode *left;  // 왼쪽 서브 트리에 대한 링크 필드
	struct treeNode *right; // 오른쪽 서브 트리에 대한 링크 필드
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

// 이진 트리에 대한 전위 순회 연산
void preorder(treeNode* root) {
	if (root) {
		printf("%c", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// 이진 트리에 대한 중위 순회 연산
void inorder(treeNode* root) {
	if (root) {
		inorder(root->left);
		printf("%c", root->data);
		inorder(root->right);
	}
}

// 이진 트리에 대한 후위 순회 연산
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
    int left_h = treeheight(root->left); // 왼쪽 서브트리의 높이를 순환호출을 통해 얻는다.
    int right_h = treeheight(root->right); // 같은 방법으로 오른쪽 서브트리의 높이를 얻는다.
    return 1 + (left_h > right_h ? left_h : right_h); // 둘 중 큰 값에 1을 더해 반환한다.
  }
}

void main() {
    	/* 교재: 특정트리만을 만드는 임시방편적인 방법
	// (A*B-C/D) 수식 이진 트리 만들기
	treeNode* n7 = makeRootNode('D', NULL, NULL);
	treeNode* n6 = makeRootNode('C', NULL, NULL);
	treeNode* n5 = makeRootNode('B', NULL, NULL);
	treeNode* n4 = makeRootNode('A', NULL, NULL);
	treeNode* n3 = makeRootNode('/', n6, n7);
	treeNode* n2 = makeRootNode('*', n4, n5);
	treeNode* n1 = makeRootNode('-', n2, n3);
	*/
	
	// node(LSubtree, RSubtree)로 표현된 임의의 이진트리를 입력하는 일반화된 방법
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
	// 위 트리의 경우 -(*(A,B),/(C,D))
	printtree(n1);
	
	printf("\n tree height : %d\n", treeheight(n1));

	getchar();
}
