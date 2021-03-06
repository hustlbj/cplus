//:C++from1to2.h
#include "list.h"
#include "tree.h"

extern bool g_InvalidInput;
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);
double Power(double base, int exponent);
void Print1ToMaxOfNDigits(int n);
char* AddTowBigDigits(char* number1, char* number2);
void ReprderOddEven(int* pData, unsigned int length);
ListNode* FindKthToTail(ListNode* pHead, unsigned int k);
ListNode* ReverseList(ListNode* pHead);
ListNode* Merge(ListNode* pHead1, ListNode* pHead2);
bool HasSubTree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);
void MirrorRecursively(BinaryTreeNode* pNode);
void PrintMatrixClockwisely(int* numbers, int columns, int rows);