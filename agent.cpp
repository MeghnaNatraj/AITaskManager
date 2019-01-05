#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

// Given 24 hours and upto 10 tasks that a user can perform in each hour
// our goal is to learn which task a user is most likely to pick for a certain hour. 

const int GLOBAL_NUM_HOURS = 24;
const int GLOBAL_NUM_TASKS = 10;
void softmax ();

// Representation of a task
class Task{
    public:
    	std::string name;
    	float prob;
    	int hits;
};
// Representation of an hour of a day consisting of a 
// number of tasks that a user can perform.
class Hour {
  public:
    int id;
    int no_of_tasks;
    static int no_of_ids;
    Task tasks[GLOBAL_NUM_TASKS];
  	Hour (): id {no_of_ids} { no_of_ids +=1; }
};
int Hour::no_of_ids = 0;
Hour day[GLOBAL_NUM_HOURS];

int main()
{
    std::cout << "hello";
    bool flag;
    int hour, maxtaskno;
    float maxprob;
    char menu, choice, reply, another_task;
    std::string task;

    do{
    std::cout << "\n\n******************   SCHEDULER   *************************\n";
    std::cout << "\nWhat do you wish to do :";
    std::cout << "\n\n(1)Add Tasks.\n(2)View Tasks.\n(3)Exit\n";
    std::cout << "\nEnter your choice (1/2/3) : ";
    std::cin >> choice;
    switch (choice) {
    case '1':
    do{
        std::cout << "\nEnter the HOUR :";
        std::cin >> hour;
        hour -= 1;
        maxtaskno = 0;
        maxprob = day[hour].tasks[maxtaskno].prob;
        for (int j = 0; j < GLOBAL_NUM_TASKS; j++) {
            if (day[hour].tasks[j].prob > maxprob) {
            	maxtaskno = j;
                maxprob = day[hour].tasks[maxtaskno].prob;
            }
        }
        if (maxprob > 0.5) {
            std::cout << "Do you wish to do task '" << day[hour].tasks[maxtaskno].name << "'? (y/n) : ";
            std::cin >> reply;
            if (reply == 'y' || reply == 'Y')
            {
                day[hour].tasks[maxtaskno].hits++;
                goto anothertask;
            }
        }
        std::cout << "Enter the TASK :";
        std::cin >> task;
        flag = false;
        for (int i = 0; i< GLOBAL_NUM_TASKS; i++){
            if (task.compare(day[hour].tasks[i].name) == 0) {
                day[hour].tasks[i].hits++;
                flag = true;
                break;
            }
        }
        if (flag == false) //newtask
        {
        	day[hour].tasks[day[hour].no_of_tasks].name = task;
            day[hour].tasks[day[hour].no_of_tasks].hits = 1;
            day[hour].no_of_tasks += 1;
        	day[hour].no_of_tasks %= GLOBAL_NUM_TASKS;
        }

    anothertask:
    	softmax();
    	std::cout << "\nSCHEDULE OF THE DAY\n";
        for (auto hour: day) {
            std::cout << "\nHour : " << hour.id;
            for (auto task: hour.tasks)
                if (task.hits != 0)
                    std::cout << "\n\tTask : " << task.name << "  Hits : " << task.hits << "  Probability : " << task.prob;
        }
        std::cout << "\nDo you wish to enter another task? (y/n) : ";
        std::cin >> another_task;
    	}
        while (another_task != 'n' || another_task == 'N');
        break;
    case '2':
    	//;
        std::cout << "\nSCHEDULE OF THE DAY\n";
        for (auto hour: day) {
            std::cout << "\nHour : " << hour.id;
            for (auto task: hour.tasks)
                if (task.hits != 0)
                    std::cout << "\n\tTask : " << task.name << "  Hits : " << task.hits << "  Probability : " << task.prob;
        }
        break;
    case '3':
        exit(0);
    default:
        std::cout << "\nWrong Option!!";
    }
    std::cout << "\nDo you wish to go to menu ? (y/n) : ";
    std::cin >> menu;
	}
    while (menu != 'n'  || menu != 'N');
   return 0;
}
void softmax()
{
    float sum;

    for (int i = 0; i < GLOBAL_NUM_HOURS; i++) {
    	sum = 0;
        for (int j = 0; j < GLOBAL_NUM_TASKS; j++) {
            sum += pow(2.7183, day[i].tasks[j].hits);
        }
        for (int j = 0; j < GLOBAL_NUM_TASKS; j++) {
            day[i].tasks[j].prob = pow(2.7183, day[i].tasks[j].hits)/sum;
        }
    }
}

