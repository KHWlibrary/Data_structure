// 변경된 enqueue 함수
void enqueue(QueueType* q, TreeNode* item)
{
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
        return;
    }
    q->data[++(q->rear)] = item;
}

// 변경된 dequeue 함수
TreeNode* dequeue(QueueType* q)
{
    if (is_empty(q)) {
        error("큐가 공백입니다.");
        return NULL;
    }
    return q->data[++(q->front)];
}