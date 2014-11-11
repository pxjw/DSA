#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

template <typename T>
T max(T const& a, T const& b)
{
	return a > b ? a : b;
}

#define MAX_VAL 4000000
int preorder[MAX_VAL] = { 0 };
int postorder[MAX_VAL] = { 0 };
int g_position_pre[MAX_VAL+1] = { 0 };
int g_position_post[MAX_VAL+1] = { 0 };

int g_print_index = 0;

void print(int data)
{
	//printf("%d ", data);
	g_position_pre[g_print_index++] = data;
}



void parseSubTree(BinTree<int>& bintree, BinNodePosi(int) pos, 
				  int* preorder, int *postorder, int n)
{
	if (n <= 2)
		return;

	int l = preorder[1];
	int r = postorder[n - 2];
	int lpos_in_pre = g_position_pre[l];
	int rpos_in_pre = g_position_pre[r];
	int lpos_in_post = g_position_post[l];
	int rpos_in_post = g_position_post[r];
	BinNodePosi(int) lpos = bintree.insertAsLC(pos, l);
	BinNodePosi(int) rpos = bintree.insertAsRC(pos, r);
	parseSubTree(bintree, lpos, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);
	parseSubTree(bintree, rpos, 
				 preorder + 1 + rpos_in_pre - lpos_in_pre, 
				 postorder + rpos_in_pre - lpos_in_pre, 
				 rpos_in_post - lpos_in_post);
}

//#define _DEBUG_



int main(int /*argc*/, char** /*argv*/)
{
#ifdef _DEBUG_
	BinTree<int> tree;
	BinNodePosi(int) pp = tree.insertAsRoot(1);
	BinNodePosi(int) pl = tree.insertAsLC(pp, 2);
	BinNodePosi(int) pr = tree.insertAsRC(pp, 3);
	tree.insertAsLC(pr, 4);
	BinNodePosi(int) prp = tree.insertAsRC(pr, 5);
	tree.insertAsLC(prp, 6);
	tree.insertAsRC(prp, 7);
	tree.travPre(print);
	printf("\n");
	tree.travPost(print);
	printf("\n");
	tree.travIn(print);
	printf("\n");
	return 0;
#endif
	int n;
	if (scanf("%d\n", &n) == EOF)
		return 0;

	//int *preorder = new int[n];
	//int *postorder = new int[n];
	//g_position_pre = new int[n + 1];
	//g_position_post = new int[n + 1];
	for (int i = 0; i < n; i++) {
		if (scanf("%d\n", &preorder[i]) == EOF)
			return 0;
		g_position_pre[preorder[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		if (scanf("%d\n", &postorder[i]) == EOF)
			return 0;
		g_position_post[postorder[i]] = i;
	}

	if (n == 0) {
		return 0;
	} else if (n == 1) {
		printf("%d\n", preorder[0]);
		return 0;
	} else if (n == 2) {
		printf("%d %d\n", preorder[0], preorder[1]);
		return 0;
	}

	int p, l, r;
	p = preorder[0];
	l = preorder[1];
	r = postorder[n - 2];
	int lpos_in_pre = g_position_pre[l];
	int rpos_in_pre = g_position_pre[r];
	int lpos_in_post = g_position_post[l];
	int rpos_in_post = g_position_post[r];
	BinTree<int> bintree;
	BinNodePosi(int) pos = bintree.insertAsRoot(p);
	BinNodePosi(int) lpos = bintree.insertAsLC(pos, l);
	BinNodePosi(int) rpos = bintree.insertAsRC(pos, r);
	parseSubTree(bintree, lpos, preorder + 1, postorder, rpos_in_pre - lpos_in_pre);
	parseSubTree(bintree, rpos, preorder + rpos_in_pre, postorder + 1 + lpos_in_post, rpos_in_post - lpos_in_post);


	bintree.travIn(print);
	//printf("\n");
	for (int i = 0; i < g_print_index; i++) {
		printf("%d ", g_position_pre[i]);
	}
	return 0;
}