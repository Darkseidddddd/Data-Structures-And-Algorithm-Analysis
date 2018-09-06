struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *NewPtr, *head;
    NewPtr = (struct ListNode*)malloc(sizeof(struct ListNode));
    NewPtr->next = NULL;
    head = NewPtr;
    int a = 0, b, x, y;
    while (l1 != NULL || l2 != NULL || a == 1) {
        x = (l1 == NULL) ? 0:l1->val;
        y = (l2 == NULL) ? 0:l2->val;
        b = x+y+a;
        struct ListNode *temp;
        temp = (struct ListNode*)malloc(sizeof(struct ListNode));
        temp->val = 0;
        a = 0;
        temp->next = NULL;
        if (b >= 10) {
            b %= 10;
            a = 1;
        }
        temp->val += b;
        NewPtr->next = temp;
        NewPtr = NewPtr->next;
        l1 = (l1 == NULL) ? NULL:l1->next;
        l2 = (l2 == NULL) ? NULL:l2->next;
    }
    return head->next;
}