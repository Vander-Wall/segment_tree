#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_LEN 1000

void build_tree(int arr[], int tree[], int node, int start, int end){

	if (start == end){
		tree[node] = arr[start];
	}
	else{
		int mid = (start + end) / 2;
		int left_node = 2 * node + 1;
		int right_node = 2 * node + 2;

		build_tree(arr, tree, left_node, start, mid);
		build_tree(arr, tree, right_node, mid + 1, end);
		tree[node] = tree[left_node] + tree[right_node];
	}

}

void update_tree(int arr[], int tree[], int node, int start, int end, int idx, int val){ // 更新 arr[idx] = val; 
	// 先到底，然后从下往上更新，一直更新到根节点
	if (start == end){
		arr[idx] = val;
		tree[node] = val;
	}
	else{
		int mid = (start + end) / 2;
		int left_node  = 2 * node + 1;
		int right_node = 2 * node + 2;
		if (idx >= start && idx <= mid){
			update_tree(arr, tree, left_node, start, mid, idx, val);
		}
		else{
			update_tree(arr, tree, right_node, mid+1, end, idx, val);
		}
		tree[node] = tree[left_node] + tree[right_node]; 
	}
}

int query(int arr[], int tree[], int node, int start, int end, int L, int R){
	if (R < start || L > end)
		return 0;
	else if (start >= L && end <= R){
		return tree[node];
	}
	else if (start == end){
		return tree[node];
	}
	else{
		int mid = (start + end) / 2; 
		int left_node  = 2 * node + 1;
		int right_node = 2 * node + 2;
		int sum_left  = query(arr, tree, left_node,  start, mid, L, R);
		int sum_right = query(arr, tree, right_node, mid+1, end, L, R);
		return sum_left + sum_right;
	}
}

int main(){
	int arr[] = { 1, 3, 5, 7, 9, 11 };
	int size = 6;
	int tree[MAX_LEN] = { 0 };
	build_tree(arr, tree, 0, 0, size - 1);
	for (int i = 0; i < 15; i++){
		printf("tree[%d]=%d\n", i, tree[i]);
	}
	printf("-------------------\n");

	update_tree(arr, tree, 0, 0, size - 1, 4, 6);
	for (int i = 0; i < 15; i++){
		printf("tree[%d]=%d\n", i, tree[i]);
	}
	cout << query(arr, tree, 0, 0, size - 1, 2, 5) << endl;
	return 0;
}
