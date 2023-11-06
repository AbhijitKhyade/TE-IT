#include <bits/stdc++.h>
using namespace std;
struct process{
    int id, at, bt, ct, tat, wt, rt;
};

void print_table(vector<process> &p){
    int n = p.size();
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++){
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << "\n";
    }
}

void sort_process_by_at(vector<process> &p){
    int n = p.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (p[j].at > p[j + 1].at){
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sort_process_by_ct(vector<process> &p){
    int n = p.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (p[j].ct > p[j + 1].ct){
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int find_shortest_job(vector<process> p, int current_time){
    int n = p.size();
    int sj_index = -1;
    int sj = 99999;
    for (int i = 0; i < n; i++){
        if (p[i].at <= current_time && p[i].rt > 0 && p[i].rt < sj){
            sj_index = i;
            sj = p[i].rt;
        }
    }
    return sj_index;
}

void print_gantt_chart(vector<process> p){

    cout << "Gantt Chart: \n";
    int n = p.size();
    int index = 0;

    for (int i = 0; i <= p[n - 1].ct && index < n; i++){
        if (i == p[index].ct){
            cout << "-+-";
            index++;
        }
        else if (i == 0){
            cout << "+";
        }
        else{
            cout << "---";
        }
    }
    cout << "\n";

    index = 0;
    for (int i = 0; i <= p[n - 1].ct && index < n; i++){
        if (i == p[index].ct){
            cout << p[index].id << "| ";
            index++;
        }
        else if (i == 0){
            cout << "|";
        }
        else{
            cout << "   ";
        }
    }
    cout << "\n";

    index = 0;
    for (int i = 0; i <= p[n - 1].ct && index < n; i++){
        if (i == p[index].ct){
            cout << "-+-";
            index++;
        }
        else if (i == 0){
            cout << "+";
        }
        else{
            cout << "---";
        }
    }
    cout << "\n";

    index = 0;
    for (int i = 0; i <= p[n - 1].ct && index < n; i++){
        if (i == p[index].ct){
            cout << p[index].ct << " ";
            index++;
        }
        else{
            cout << "   ";
        }
    }
    cout << "\n";
}

int main(){
    int n;
    cout << "Enter number of process: ";
    cin >> n;

    vector<process> p(n);

   for (int i = 0; i < n; i++){
        cout << "Process ID : " << (i + 1) << endl;
        p[i].id = (i + 1);
        cout << "\t\tArrival time :: ";
        cin >> p[i].at;
        cout << "\t\tBurst Time :: ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    sort_process_by_at(p);
    int curr_time = 0;
    int completed = 0;
    int sj = -1;

    while (completed < n){
        sj = find_shortest_job(p, curr_time);
        if (sj == -1){
            curr_time++;
            continue;
        }

        p[sj].rt--;
        curr_time++;

        if (p[sj].rt == 0){
            completed++;
            p[sj].ct = curr_time;
        }
    }

    int totalTat = 0, totalWt = 0;
    float avgTat = 0, avgWt = 0;

    for (int i = 0; i < n; i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTat += p[i].tat;
        totalWt += p[i].wt;
    }

    avgTat = (float)totalTat / n;
    avgWt = (float)totalWt / n;

    print_table(p);
    cout << endl;
    sort_process_by_ct(p);
    // print_table(p);
    print_gantt_chart(p);

    cout << "Average TAT :: " << avgTat << endl;
    cout << "Average WT :: " << avgWt << endl;

    return 0;
}