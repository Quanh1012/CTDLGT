#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include "Graph.h"

int main()
{
    Graph a;
    //Menu
    cout << "----------------------------------------------------------------" << endl;
    cout << "1. Creat a graph of routers\t\t2. Number of routers" << endl;
    cout << "3. Number of edges         \t\t4. Change weight" << endl;
    cout << "5. Print weight of edge    \t\t6. Insert a router" << endl;
    cout << "7. Remove router           \t\t8. Print weight" << endl;
    cout << "9. Print shortest path from router x to router y" << endl;
    cout << "10. Finish" << endl;
    cout << "----------------------------------------------------------------" << endl;

    //Choose 
    string option;
    int option_;
    bool check_option = true;

    while (check_option)
    {
        cout << "Choose a number: ";
        cin >> option;
        option_ = a.check(option);
        while (option_ < 1 || option_ > 10)
        {
            cout << "Must be between 1 and 10, enter again: ";
            cin >> option;
            option_ = a.check(option);
        }
        if (option_ == 1)
        {
            string num;
            cout << "Enter the number of routers (must greater than 1): ";
            cin >> num;
            int number_router = a.check(num);
            while (number_router < 2)
            {
                cout << "Invaild value, enter again: ";
                cin >> num;
                number_router = a.check(num);
            }
            a = Graph(number_router);
        }
        else
        {
            if (a.getNumVertex() == 0)
            {
                string num;
                cout << "Enter the number of routers (must greater than 1): ";
                cin >> num;
                int number_router = a.check(num);
                while (number_router < 2)
                {
                    number_router = a.check(num);
                }
                a = Graph(number_router);
            }
            if (option_ == 2)
            {
                cout << "Number of routers: " << a.getNumVertex() << endl;
            }
            else if (option_ == 3)
            {
                cout << "Number of edges: " << a.getNumEdge() << endl;
            }
            else if (option_ == 4 || option_ == 5)
            {
                string first_router, second_router, weight;
                int first_router_, second_router_;
                float weight_;
                //First router
                cout << "Enter first router: ";
                cin >> first_router;
                first_router_ = a.check(first_router);
                while (first_router_ >= a.getNumVertex())
                {
                    cout << "Must less than " << a.getNumVertex() << " routers, enter again: ";
                    cin >> first_router;
                    first_router_ = a.check(first_router);
                }

                //Second router
                cout << "Enter second router: ";
                cin >> second_router;
                second_router_ = a.check(second_router);
                while (second_router_ >= a.getNumVertex())
                {
                    cout << "Must fewer than " << a.getNumVertex() << " routers, enter again: ";
                    cin >> second_router;
                    second_router_ = a.check(second_router);
                }

                //weight
                //First router
                if (option_ == 4)
                {
                    cout << "Enter weight - noconnect: inf: ";
                    cin >> weight;
                    weight_ = a.checkf(weight);
                    a.setWeight(first_router_, second_router_, weight_);
                }
                else
                {
                    cout << "Weight " << first_router_ << " <-----> " << second_router_ << " : " << a.getWeight(first_router_, second_router_);
                }

            }
            else if (option_ == 6)
            {
                a.insertVertex();
            }
            else if (option_ == 7)
            {
                a.deleteVertex();
            }
            else if (option_ == 8)
            {
                a.print_weight();
            }
            else if (option_ == 9)
            {
                a.print_shorestpath();
            }
            else
            {
                check_option = false;
            }

        }
        cout <<"=========================================="<< endl;
    }
    cout << "Done";


}
