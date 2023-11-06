#include<bits/stdc++.h>
using namespace std;
struct process{
    int id, at, bt, ct, tat, wt, rt;
};

void print_table(vector<process> &p){
    int n  = p.size();
    cout<<"Process\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i= 0; i < n; i++){
        cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\n";
    } 
}

void sort_process_by_at(vector<process> &p){
    int n = p.size();
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j< n-i-1; j++){
            if (p[j].at > p[j+1].at) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void sort_process_by_ct(vector<process> &p){
    int n = p.size();
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j< n-i-1; j++){
            if (p[j].ct > p[j+1].ct) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void print_gantt_chart(vector<process> p){
    cout << "Gantt Chart: \n";
    int n = p.size();
    int index = 0;

    for(int i= 0; i <= p[n-1].ct && index < n; i++){
        if(i == p[index].ct){
            cout<<"-+-";
            index++;
        }
        else if(i == 0){
            cout<<"+";
        }
        else{
            cout<<"---";
        }
    }
    cout<<"\n";

    index = 0;
    for(int i= 0; i <= p[n-1].ct && index < n; i++){
        if(i == p[index].ct){
            cout<<p[index].id<<"| ";
            index++;
        }
        else if(i == 0){
            cout<<"|";
        }
        else{
            cout<<"   ";
        }
    }
    cout<<"\n";

    index = 0;
    for(int i= 0; i <= p[n-1].ct && index < n; i++){
        if(i == p[index].ct){
            cout<<"-+-";
            index++;
        }
        else if(i == 0){
            cout<<"+";
        }
        else{
            cout<<"---";
        }
    }
    cout<<"\n";

    index = 0;
     for(int i= 0; i <= p[n-1].ct && index < n; i++){
        if(i == p[index].ct){
            cout<<p[index].ct<<" ";
            index++;
        }
        else{
            cout<<"   ";
        }
    }
    cout<<"\n";
}

int main(){
    int n; 
    cout<<"Enter number of process :: ";
    cin>>n;

    vector<process> p(n);

    for(int i = 0; i < n; i++){   
        cout << "Process ID : "<<(i+1)<<endl;
        p[i].id = (i+1);
        cout<<"\t\tArrival time :: ";
        cin>>p[i].at;
        cout<<"\t\tBurst Time :: ";
        cin>>p[i].bt;
        p[i].rt = p[i].bt;
    }

    int qt;
    cout<<"\nEnter time quantum :: ";
    cin>>qt;

    sort_process_by_at(p);

    int curr_time = 0;
    queue<int> q;
    vector<int> visited(n,0);

    q.push(0);
    visited[0]=1;

    while(!q.empty()){
        int index = q.front();
        q.pop();
        curr_time+=min(p[index].rt,qt);
        p[index].rt -= min(p[index].rt,qt);

        if(p[index].rt == 0){
            visited[index] = 1;
            p[index].ct = curr_time;
        }

        for(int i = 0; i < n; i++){
            if(visited[i]==0 && p[i].at <= curr_time){
                q.push(i);
                visited[i] = 1;
            }
        }

        if(p[index].rt != 0){
            q.push(index);
        }
    }

    int totalTat = 0, totalWt = 0;
    float avgTat = 0, avgWt = 0;

    for(int i = 0 ; i < n ; i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTat+=p[i].tat;
        totalWt += p[i].wt;
    }

    avgTat = (float)totalTat/n;
    avgWt = (float)totalWt/n;

    print_table(p);
    cout<<endl;
    sort_process_by_ct(p);
    print_gantt_chart(p);

    cout<<"Average TAT :: "<<avgTat<<endl;
    cout<<"Average WT :: "<<avgWt<<endl;
    return 0;
}