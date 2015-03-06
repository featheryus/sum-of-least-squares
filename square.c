/*
 * =====================================================================================
 *
 *       Filename:  sqrt.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/27/2015 01:34:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Su Yu (), yu.1.su@nsn.com
 *        Company:  Nokia
 *
 * =====================================================================================
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define R_N 100
unsigned int result[R_N];
unsigned int index_s = 0;
int has_no_answer = 1;
int *sqrt_s;
int *answer;
int queue_index = 0;

typedef struct data {
    unsigned int value;
    int index;
    int up;
    unsigned int need_handle;
    struct data *next;
    struct data *prev;
}data;
typedef struct queue {
    unsigned int num;
    data *first;
    data *last;
}queue;
data *answer_s;
queue q;
void get_the_answer(unsigned int sqrti)
{
    int i;
    result[index_s++] = sqrti;
    printf("\n get the answer \n");
    for(i=0; i < index_s; i++) {
        printf("%d ",result[i]);
    }
    printf("\n");
    index_s = 0;
}
unsigned int find_all_squart(unsigned int num, unsigned int sqrt, int * seq)
{
    int i = 0;
    seq[sqrt] = num;
    for(i = sqrt-1; i>0; i--) {
        seq[i] = num-(2*i+1);
        num = seq[i];
    }
}
int enq(struct data* d)
{
    if(0 == q.num) {
        q.first = d;
        q.last = d;
        d->next = NULL;
        d->prev = NULL;
        q.num++;
        return q.num;
    }
    q.first->prev=d;
    d->next=q.first;
    q.first=d;
    q.num++;
    return q.num;
}
data* deque()
{
    if(isempty()) {
        printf("it's empty\n");
        return NULL;
    }
    data * tmp = q.last;
    q.last=q.last->prev;
    q.num--;
    return tmp;

}
int isempty()
{
    return !(q.num);
}
void initq()
{
    q.num=0;
    q.first = q.last = NULL;
}
int find_in_detail(unsigned int num, int sqrti, int index)
{
    int i = sqrti;
    int j;
    while(has_no_answer && i>0) {
        if(1) {
            answer[index]=i;
            j=i;
            while(sqrt_s[i]+sqrt_s[j]>num && j > 0) {
                j--;
            }
            if(sqrt_s[i]+sqrt_s[j]==num) {
                answer[index+1]=j;
                has_no_answer = 0;
                break;
            }

            answer_s[queue_index%sqrti].value = j;
            answer_s[queue_index%sqrti].index = index+1;
            answer_s[queue_index%sqrti].up = i;
            answer_s[queue_index%sqrti].need_handle = num-sqrt_s[i];
            enq(&answer_s[queue_index%sqrti]);
            queue_index++;
            i--;
        }
        else {
            answer_s[queue_index%sqrti].value = 1;
            answer_s[queue_index%sqrti].index = index+1;
            answer_s[queue_index%sqrti].up = 1;
            answer_s[queue_index%sqrti].need_handle = num-1;
            enq(&answer_s[queue_index%sqrti]);
            queue_index++;
        }
    }
}

int find(unsigned int num)
{

    int num_tmp = 0;
    int sqrti = sqrt(num);
    int i = 1;
    int sum = 0;
    data first;
    data *t;
    sqrt_s = (int*)malloc((sqrti+1)*sizeof(int));
    answer = (int*)malloc((sqrti+1)*sizeof(int));
    answer_s = (data*)malloc((sqrti+1)*sizeof(struct data));
    find_all_squart(sqrti*sqrti, sqrti, sqrt_s);
    first.value=sqrti;
    first.index=1;
    first.up=0;
    first.need_handle=num;

    enq(&first);
        while(!isempty() && has_no_answer) {
        t=deque(q);
        if(t->index > 1) {
            answer[t->index-1]=t->up;
        }
        find_in_detail(t->need_handle,t->value, t->index);
    }
    while(answer[i]) {
        sum = sum+sqrt_s[answer[i]];
        printf(" %d", answer[i++]);
    }
}
int main(int argc, char*argv[])
{
    unsigned int num = atoi(argv[1]);
    find(num);
}

