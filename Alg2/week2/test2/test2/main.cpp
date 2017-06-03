#include <iostream>

using namespace std;

struct Proc{
    //static int count_proc;
    int num;
    bool operator >(Proc x){
        return this->num > x.num;
    }
    bool operator <(Proc x){
        return this->num < x.num;
    }
    Proc(int i){
        //num = Proc::count_proc++;
        num = i;
    }
    ~Proc(){
        //Proc::count_proc--;
    }
};
//int Proc::count_proc=0;

struct  Task{
    Proc *proc;
    long task_duration;
    int task_num;
    long start_time;
    Task(){}
    Task(Proc *proc, int task_num ,long task_duration, long start_time){
        this->proc = proc;
        this->task_num = task_num;
        this->task_duration = task_duration;
        this->start_time = start_time;
    }
    bool operator >(Task x){
        return this->task_duration > x.task_duration;
    }
    bool operator <(Task x){
        return this->task_duration < x.task_duration;
    }
};



template<class T>
class MyQueuePriority{
private:
    T* myheap;
    int max_size;
    int size;

    void Swap(int i,int j){
        if (i<=size && j<=size){
            T x = myheap[i];
            myheap[i] = myheap[j];
            myheap[j] = x;
        }
    }
    void ShiftUp(int i){
        while(i>0 && i<=size && *myheap[i]<*myheap[(i-1)/2]){
            Swap(i,(i-1)/2);
            i = (i-1)/2;
        }
    }
    void ShiftDown(int i){
        while(i<size){
            int min = i;
            if(2*i+1 <= size &&  *myheap[min]>*myheap[2*i+1]){min = 2*i+1;}
            if(2*i+2 <= size &&  *myheap[min]>*myheap[2*i+2]){min = 2*i+2;}
            if(i!=min){
                Swap(i,min);
                i=min;
            }else{
                break;
            }
        }
    }

public:
    MyQueuePriority(int n = 4){
        max_size = n;
        size = -1;
        myheap = new T[n];
    }

    bool AddElem(T elem){
        if(size<max_size){
            myheap[++size]=elem;
            ShiftUp(size);
            return true;
        }else{
            return false;
        }

    }

    T  GetElem(){
       Swap(0,size);
       T x = myheap[size--];
       ShiftDown(0);
       return x;
    }
    T GetTop(){
        if(this->Empty()) return NULL;
        return myheap[0];
    }
    bool Empty(){
        return size == -1;;
    }
};



int main()
{
    long time=0;
    int count_proc;
    int count_task;
    int cur_task = 0;
    int executed_task = 0;
    cin >> count_proc;
    cin >> count_task;
    Task *arr_task_result = new Task[count_task];
    MyQueuePriority<Proc*> *myqueue_proc = new MyQueuePriority<Proc*>(count_proc);
    MyQueuePriority<Task*> *myqueue_task = new MyQueuePriority<Task*>(count_task);

    for(int i = 0; i < count_proc; i++){
        myqueue_proc->AddElem(new Proc(i));
    }
    while(true){
        while(!myqueue_proc->Empty() && cur_task<count_task ){
            long task_dur;
            cin >> task_dur;
            myqueue_task->AddElem(new Task(myqueue_proc->GetElem(),cur_task++, time+task_dur, time));

            if(!myqueue_task->Empty() && myqueue_task->GetTop()->task_duration == time){
                Task* t1 = myqueue_task->GetElem();
                arr_task_result[t1->task_num] = *t1;
                myqueue_proc->AddElem(t1->proc);
                executed_task++;
            }
            time = time;
        }
        Task* t = myqueue_task->GetElem();
        arr_task_result[t->task_num] = *t;
        myqueue_proc->AddElem(t->proc);
        executed_task++;
        time = t->task_duration;
        while(!myqueue_task->Empty() && myqueue_task->GetTop()->task_duration == time){
            Task* t1 = myqueue_task->GetElem();
            arr_task_result[t1->task_num] = *t1;
            myqueue_proc->AddElem(t1->proc);
            executed_task++;
        }
        if (executed_task == count_task) break;

    }
    for(int i=0;i<count_task; i++){
        cout << arr_task_result[i].proc->num<< ' ';
        cout << arr_task_result[i].start_time << endl;
    }
    return 0;
}

