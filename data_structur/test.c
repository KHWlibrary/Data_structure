// ����� enqueue �Լ�
void enqueue(QueueType* q, TreeNode* item)
{
    if (is_full(q)) {
        error("ť�� ��ȭ�����Դϴ�.");
        return;
    }
    q->data[++(q->rear)] = item;
}

// ����� dequeue �Լ�
TreeNode* dequeue(QueueType* q)
{
    if (is_empty(q)) {
        error("ť�� �����Դϴ�.");
        return NULL;
    }
    return q->data[++(q->front)];
}