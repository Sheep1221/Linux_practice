#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR_TASKS 5
#define TASK_RUNNING 0
#define TASK_INTERRUPTIBLE 1
#define SIGALARM 14

typedef struct {
    int pid;
    int state;     //TASK_RUNNING or TASK INTERRUPTIBLE
    int counter;
    int priority;
    int signal;    //bitmask of pending signal
    int alarm;
} task_struct;


task_struct* task[NR_TASKS];
task_struct* curr_task = NULL;
int jiffies = 0;

#define FIRST_TASK (task[0])
#define LAST_TASK (task[NR_TASKS - 1])

void switch_to(int next){
    printf("Switch from curent task %d to task %d \n", curr_task->pid, task[next]->pid);
    curr_task = task[next];
}

void print_tasks(){
    printf("Current jiffies: %d\n", jiffies);
    for(int i=0; i<NR_TASKS; i++){
        if(task[i]){
            printf("Task %d: state=%d, counter=%d, priority=%d, signal=0x%x, alarm=%d\n",
                   task[i]->pid, task[i]->state, task[i]->counter,
                   task[i]->priority, task[i]->signal, task[i]->alarm);
        }
    }
    printf("\n");
}

void schedule(){
    int i, next, c;
    task_struct **p;

    // ***** Alarm + Signal wakeup handling *****
    for(p=&LAST_TASK; p>&FIRST_TASK; --p){
        if(*p){
            if((*p)->alarm && (*p)->alarm<jiffies){
                (*p)->signal |= (1 << (SIGALARM-1));
                (*p)->alarm = 0;
            }
            if((*p)->signal && (*p)->state==TASK_INTERRUPTIBLE){
                (*p)->state = TASK_RUNNING;
            }
        }
    }

    // ***** Scheduler Proper *****
    while(1){
        c = -1;
        next = 0;
        i = NR_TASKS;
        p = &task[NR_TASKS];

        while(--i){
            if(!*--p)
                continue;
            if((*p)->state==TASK_RUNNING && (*p)->counter > c){
                c = (*p)->counter;
                next = i;
            }
        }
        if(c)
            break;
        
        // Recalculate time slices (aging)
        for(p=&LAST_TASK; p>&FIRST_TASK; --p){
            if(*p)
                (*p)->counter = ((*p)->counter >> 1) + (*p)->priority;
        }
    }
    switch_to(next);
}


int main(){
    // Initialize tasks
    for (int i = 0; i < NR_TASKS; ++i) {
        task[i] = malloc(sizeof(task_struct));
        task[i]->pid = i;
        task[i]->state = TASK_RUNNING;
        task[i]->priority = rand() % 5 + 1;
        task[i]->counter = rand() % 10;
        task[i]->signal = 0;
        task[i]->alarm = (rand() % 20) + 5; // fire alarm in 5~24 ticks
    }

    curr_task = task[0];
    print_tasks();
    
    for(int tick=0; tick<20; ++tick){
        printf("=== Tick %d ===\n", tick);
        jiffies++;

        schedule();

        // Simulate CPU running current task
        if(curr_task->counter > 0)
            curr_task->counter--;

        // Make a task to go sleep
        if(tick%5==0 && task[2]){
            printf("Task %d goes to sleep (TASK_INTERRUPTIBLE)\n", task[2]->pid);
            task[2]->state = TASK_INTERRUPTIBLE;
        }
        print_tasks();
    }

    // Cleanup
    for (int i = 0; i < NR_TASKS; i++) {
        free(task[i]);
    }
    return 0;
}
