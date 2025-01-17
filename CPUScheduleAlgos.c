#include<stdio.h>
#include<stdlib.h>

struct Node {
    int process;
    int arrival;
    int burst;
    int response;
    int start;
    int priority;
    int visited;
    int complete;
    int turn;
    int work;
    struct Node *link;
};

struct Node *head = NULL, *temp, *p, *q, *r, *a, *b;

struct Node *insert() {
    int i, n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Process %d\n", i+1);
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->process = i + 1;
        printf("Enter the arrival, burst, and priority: ");
        scanf("%d %d %d", &temp->arrival, &temp->burst, &temp->priority);
        temp->visited = 0;
        temp->link = NULL;

        if(head == NULL || temp->arrival < head->arrival) {
            temp->link = head;
            head = temp;
        } else {
            q = head;
            while(q->link != NULL && q->link->arrival < temp->arrival) {
                q = q->link;
            }
            temp->link = q->link;
            q->link = temp;
        }
    }
    return head;
}

struct Node *First() {
    struct Node *phead = NULL;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->link = NULL;
    p = head;
    int sys = 0;
    temp->start = p->arrival + sys;
    temp->response = temp->start - temp->arrival;
    temp->complete = temp->start + p->burst;
    temp->turn = temp->complete - p->arrival;
    temp->work = temp->turn - p->burst;
    sys = p->arrival + p->burst;
    phead = temp;
    q = temp;
    p = p->link;
    while(p != NULL) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->link = NULL;
        if(p->arrival > sys) {
            temp->start = p->arrival;
            temp->response = temp->start - p->arrival;
            temp->complete = temp->start + p->burst;
            temp->turn = temp->complete - p->arrival;
            temp->work = temp->turn - p->burst;
            sys = sys + p->burst;
            q->link = temp;
            q = temp;
        } else {
            temp->start = p->complete;
            temp->response = temp->start - p->arrival;
            temp->complete = temp->start + p->burst;
            temp->turn = temp->complete - p->arrival;
            temp->work = temp->turn - p->burst;
            sys = p->arrival + p->burst;
            q->link = temp;
            q = temp;
        }
        p = p->link;
    }
    return phead;
}

struct Node *Shortjob() {
    p = head;
    while(p != NULL) {
        a = p->link;
        while(a != NULL) {
            if(p->burst > a->burst) {
                int temp1 = p->arrival;
                p->arrival = a->arrival;
                a->arrival = temp1;

                int temp2 = p->process;
                p->process = a->process;
                a->process = temp2;

                int temp3 = p->burst;
                p->burst = a->burst;
                a->burst = temp3;
            }
            a = a->link;
        }
        p = p->link;
    }

    struct Node *phead = NULL;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->link = NULL;
    p = head;
    int sys = 0;
    temp->start = p->arrival + sys;
    temp->response = temp->start - p->arrival;
    temp->complete = temp->start + p->burst;
    temp->turn = temp->complete - p->arrival;
    temp->work = temp->turn - p->burst;
    phead = temp;
    q = temp;
    p = p->link;
    int count = 0;
    while(p != NULL && count != 4) {
        if(sys > p->arrival && p->visited != 1) {
            temp = (struct Node*)malloc(sizeof(struct Node));
            temp->link = NULL;
            p->visited = 1;
            temp->start = p->complete;
            temp->response = temp->start - p->arrival;
            temp->complete = temp->start + p->burst;
            temp->turn = temp->complete - p->arrival;
            temp->work = temp->turn - p->burst;
            sys = sys + p->burst;
            q->link = temp;
            q = temp;
            p = head;
            count++;
        }
        p = p->link;
    }
    return phead;
}

struct Node *priority() {
    struct Node *qhead = NULL;
    p = head;
    while(p != NULL) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->link = NULL;
        if(qhead == NULL || p->priority < qhead->priority) {
            temp->process = p->process;
            temp->arrival = p->arrival;
            temp->burst = p->burst;
            temp->priority = p->priority;
            temp->visited = 1;
            temp->link = qhead;
            qhead = temp;
        } else {
            q = qhead;
            while(q->link != NULL && q->link->priority < p->priority) {
                q = q->link;
            }
            temp->process = p->process;
            temp->arrival = p->arrival;
            temp->burst = p->burst;
            temp->visited = 1;
            temp->priority = p->priority;
            temp->link = q->link;
            q->link = temp;
        }
        p = p->link;
    }

    struct Node *phead = NULL;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->link = NULL;
    p = qhead;
    int sys = 0;
    temp->start = p->arrival + sys;
    temp->response = temp->start - p->arrival;
    temp->complete = temp->start + p->burst;
    temp->turn = temp->complete - p->arrival;
    temp->work = temp->turn - p->burst;
    sys = p->arrival + p->burst;
    phead = temp;
    p = p->link;
    int count = 0;
    while(p != NULL && count != 4) {
        if(sys > p->arrival && p->visited != 0) {
            temp = (struct Node*)malloc(sizeof(struct Node));
            temp->link = NULL;
            p->visited = 0;
            temp->start = p->complete;
            temp->response = temp->start - p->arrival;
            temp->complete = temp->start + p->burst;
            temp->turn = temp->complete - p->arrival;
            temp->work = temp->turn - p->burst;
            sys = sys + p->burst;
            q->link = temp;
            q = temp;
            p = qhead;
            count++;
        }
        p = p->link;
    }
    return phead;
}

struct Node *roundrobin() {
    p = head;
    while(p != NULL) {
        a = p->link;
        while(a != NULL) {
            if(p->arrival > a->arrival) {
                int temp1 = p->arrival;
                p->arrival = a->arrival;
                a->arrival = temp1;

                int temp2 = p->process;
                p->process = a->process;
                a->process = temp2;

                int temp3 = p->burst;
                p->burst = a->burst;
                a->burst = temp3;
            }
            a = a->link;
        }
        p = p->link;
    }

    int countin = 0, sys = 0, s = 2;
    struct Node *phead = NULL, *qhead = NULL, *h = NULL;
    q = head;
    while(q != NULL) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->link = NULL;
        temp->burst = q->burst;
        if(qhead == NULL) {
            temp->link = qhead;
            qhead = temp;
            h = temp;
        } else {
            h->link = temp;
            h = temp;
        }
        q = q->link;
    }
    p = head;
    while(p != NULL) {
        if(s >= p->burst && p->burst != 0) {
            sys = sys + p->burst;
            p->burst = 0;
            p->complete = sys;
            countin++;
        } else if(s < p->burst) {
            p->burst = p->burst - s;
            sys = sys + s;
            p->complete = sys;
        }
        p = p->link;
        if(p == NULL && countin != 4) {
            p = head;
        }
    }
    p = head;
    r = qhead;
    while(p != NULL && r != NULL) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->link = NULL;
        temp->start = p->arrival;
        temp->response = 0;
        temp->complete = p->complete;
        temp->turn = temp->complete - p->arrival;
        temp->work = temp->turn - r->burst;
        if(phead == NULL) {
            temp->link = phead;
            phead = temp;
            a = temp;
        } else {
            a->link = temp;
            a = temp;
        }
        p = p->link;
        r = r->link;
    }
    return phead;
}

void display1(struct Node *phead) {
    p = phead;
    int count = 0;
    double res = 0, com = 0, turn = 0, work = 0;
    printf("|Start time\t|Response time\t|Completion time\t|Turnaround time\t |Waiting time\n");
    while(p != NULL) {
        printf("|%d\t\t|%d\t\t|%d\t\t\t|%d\t\t\t|%d\t\t|", p->start, p->response, p->complete, p->turn, p->work);
        printf("\n");
        res = res + p->response;
        com = com + p->complete;
        turn = turn + p->turn;
        work = work + p->work;
        p = p->link;
        count++;
    }
    double avg1 = res / count;
    double avg2 = com / count;
    double avg3 = turn / count;
    double avg4 = work / count;
    printf("|\t\t|%f\t\t|%f\t\t|%f\t\t|%f\t\t|\n", avg1, avg2, avg3, avg4);
}

void display() {
    if(head == NULL) {
        printf("List is empty\n");
    } else {
        a = head;
        printf("|Process|Arrival|Burst  |Priority| \n");
        while(a != NULL) {
            printf("|%d\t|%d\t|%d\t|%d\t|\n", a->process, a->arrival, a->burst, a->priority);
            a = a->link;
        }
        printf("\n");
    }
}

int main() {
    head = insert();
    display();
    
    printf("FCFS\n");
    printf("\n\n");
    q = First();
    display1(q);
    
    printf("SJF\n");
    printf("\n\n");
    a = Shortjob();
    display1(a);
    
    printf("Priority Scheduling\n");
    printf("\n\n");
    r = priority();
    display1(r);
    
    printf("Round Robin Scheduling\n");
    printf("\n\n");
    b = roundrobin();
    display1(b);
    
    return 0;
}
