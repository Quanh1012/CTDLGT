#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include "Graph.h"


//Default constructor
Graph::Graph()
{
    num_of_vertex = 0;
    num_of_edge = 0;
    dist = NULL;
    trace = NULL;
    check_if_visted = NULL;
    adj->clear();

}
//Parameterized constructor
Graph::Graph(int num_vextex)
{
    num_of_vertex = num_vextex;
    num_of_edge = 0;
    string weight;
    float weight_;
    cout << "Enter weight: (inf - no conncet)" << endl;

    for (int i = 0; i < num_of_vertex; i++)
    {
        for (int j = 0; j < num_of_vertex; j++)
        {
            if (i < j)
            {
                cout << "Vertex " << i << " <----> " << j << " :";
                cin >> weight;
                weight_ = checkf(weight);
                while (!weight_ && weight_ != INF)
                {
                    cout << "Enter again: ";
                    cin >> weight;
                    weight_ = checkf(weight);
                }
                float weight_ = checkf(weight);
                adj[i].push_back({ weight_, j });
                adj[j].push_back({ weight_, i });
                num_of_edge++;
            }
        }
    }
    dist = new float[num_of_vertex];
    trace = new int[num_of_vertex];
    check_if_visted = new bool[num_of_vertex];
    cout << endl;
    print_weight();

}
//Copy constructor
Graph::Graph(const Graph& g)
{
    num_of_vertex = g.num_of_vertex;
    num_of_edge = g.num_of_edge;
    dist = new float[num_of_vertex];
    trace = new int[num_of_vertex];
    check_if_visted = new bool[num_of_vertex];
    dist = g.dist;
    trace = g.trace;
    check_if_visted = g.check_if_visted;
    adj->clear();
    for (int i = 0; i < num_of_vertex; i++)
    {
        for (int j = 0; j < g.adj[i].size(); j++)
        {
            adj[i].push_back(g.adj[i].at(j));
        }
    }


}
//Check input number
int Graph::check(string num)
{
    bool check_ = 1;
    while (check_)
    {
        int strlen = num.length();
        int count = 0;
        try
        {
            for (int i = 0; i < strlen; i++)
            {
                if (num[i] < '0' || num[i] > '9')
                {
                    throw(num);
                    break;
                }
                else
                {
                    count++;
                }
            }
        }
        catch (...)
        {
            cout << "Invaild value, enter again: ";
            cin >> num;
        }
        if (count == strlen) check_ = 0;
    }
    return stoi(num);

}
//Check input weight
float Graph:: checkf(string num)
{
    bool check_ = true;
    if (num == "inf")
    {
        return INF;
    }
    else
    {
        while (check_)
        {
            int strlen = num.length();
            int count = 0;
            try
            {
                for (int i = 0; i < strlen; i++)
                {
                    if ((num[i] < '0' || num[i] > '9') && num[i] != '.')
                    {
                        throw(num);
                        break;
                    }
                    else
                    {
                        count++;
                    }
                }
            }
            catch (...)
            {
                cout << "Invaild value, enter again: ";
                cin >> num;
            }
            cout << "count"<<count<<endl;
            cout << endl << "string" << strlen;
            if (count == strlen) check_ = false;
        }
        return stof(num);
    }
}
//get number of vertex.
int Graph::getNumVertex()
{
    return num_of_vertex;
}
//get number of edge.
int Graph::getNumEdge()
{
    return num_of_edge;
}
//Set/change weight of edge
void Graph::setWeight(int vertex_first, int vertex_second, float weight)
{
    int i;
    for (i = 0; i < adj[vertex_first].size(); i++)
    {
        if (adj[vertex_first].at(i).second == vertex_second)
        {
            if (weight == INF) 
            {
                adj[vertex_first].erase(adj[vertex_first].begin() + i);//remove adjacent vertex from vector of adjacent vertex of its.
            }else adj[vertex_first].at(i).first = weight;
        }
    }
    for (i = 0; i < adj[vertex_second].size(); i++)
    {
        if (adj[vertex_second].at(i).second == vertex_first)
        {
            if (weight == INF)
            {
                adj[vertex_second].erase(adj[vertex_second].begin() + i); //remove adjacent vertex from vector of adjacent vertex of its.
            }else adj[vertex_second].at(i).first = weight;
        }
    }
    print_weight();

}
//Get weight of egde
float Graph::getWeight(int vertex_first, int vertex_second)
{
    int i;
    float get_weight = INF;
    for (i = 0; i < adj[vertex_first].size(); i++)
    {
        if (adj[vertex_first].at(i).second == vertex_second)
        {
            get_weight = adj[vertex_first].at(i).first;
        }
    }
    return get_weight;

}
//insert a new vertex to Graph
void Graph::insertVertex()
{
    string weight_;
    float weight;
    int count = 0, i;
    cout << endl << "-----------------------------------" << endl << "Insert new vertex" << endl;
    cout << "Enter weights: (inf- no conncet): " << endl;
    for (i = 0; i < num_of_vertex; i++)
    {
        cout << "Vertex " << i << " <----> " << num_of_vertex << " :";
        cin >> weight_;
        weight = checkf(weight_);
        adj[i].push_back({ weight, num_of_vertex });
        adj[num_of_vertex].push_back({ weight, i });
        count++;

    }
    num_of_vertex++;
    num_of_edge += count;
    print_weight();

}
//remove a vertex from Graph
void Graph::deleteVertex()
{
    cout << endl << "--------------------------------------" << endl << "Delete vertex" << endl;
    string vertex_;
    int vertex, i;
    cout << "Enter delete_vertex: ";
    cin >> vertex_;
    vertex = check(vertex_);
    while (vertex >= num_of_vertex)
    {
        cout << "Must fewer than " << num_of_vertex << " routers, enter again: ";
        cin >> vertex_;
        vertex = check(vertex_);
    }
    num_of_edge -= adj[vertex].size();
    while (!adj[vertex].empty())
    {
        setWeight(vertex, adj[vertex].front().second, INF);
    }
    //num_of_vertex--;
    
    print_weight();
}
/*Dijsktra algorithm using priority queue to find a shortest path from a vertex to the others vertexs in Graph.
* All elements in dist are set as infinity (INF)
* All elements in trace are set as -1
* All elements in check_if_visited are set as false.
* 1. Initialize distances of all vertices as infinite.
* 2. Creat an empty priority_queue q which is sorted greater order. Every item of q is a pair II <distance, vertex>.
* Distance is used to campare two pairs.
* 3. Insert source vertex into q and make its distance as 0.
* 4. While either q doesn't become empty
* +> Extract minimum distance vertex from q. Let the extracted vertex be u and remove it from q.
* +> Loop through all adjacent of u and do following for every vertex v.
*  --- if vertex is visited: move to next lopp (*(check_if_visted + u) = true)
*  --- else: set *(check_if_visited + u) = true.
*  --- if *(dist + v) > *(dist + u) + weight(u,v).
*  --- update *(dist + v) = *(dist + u) + weight(u,v).
*  --- set trace of v is u: *(trace + v) = u
*  --- insert pair II {*(dist + v) and v} into the q (even if v is already here)
*          
*/
void Graph::Dijsktra(int vertex_start)
{
    for (int i = 0; i < num_of_vertex; i++) {
        *(dist + i) = INF;
        *(trace + i) = -1;
        *(check_if_visted + i) = false;
    }
    *(dist + vertex_start) = 0;
    priority_queue<II, vector<II>, greater<II>> q;
    q.push({ *(dist + vertex_start), vertex_start });
    cout << endl << "----------------------------------------------" << endl;
    cout << "Vertex\tDistance from router"<< vertex_start <<endl;
    while (!q.empty())
    {
        int u = q.top().second;
        //float dist_u = q.top().first;
        q.pop();

        if (check_if_visted[u] == true) // 
            continue;

        check_if_visted[u] = true; // 
        for (auto edge : adj[u])
        {
            int v = edge.second;
            float w = edge.first;

            if (*(dist + v) > *(dist + u) + w)
            {
                *(dist + v) = *(dist + u) + w;
                q.push({ *(dist + v), v });
                *(trace + v) = u;
                cout << v  << "\t" << *(dist + v) << endl;
            }
        }
    }

}
//Store shortest path from between two vertex
vector<II> Graph::trace_shortest_path(int start_vertex, int end_vertex)
{
    vector<II> path;
    
    Dijsktra(start_vertex);
    if (end_vertex != start_vertex && *(trace + end_vertex) == -1)
    {
        path.push_back({ start_vertex, INF });
    }

    int temp;
    while (end_vertex != start_vertex)
    {
        path.push_back({ *(dist + end_vertex), end_vertex });
        temp = *(trace + end_vertex);
        end_vertex = temp;
    }
    path.push_back({ 0, start_vertex });
    return path;
}

void Graph::print_shorestpath()
{
    cout << endl << "<------------------------------------------->" << endl;
    cout << endl << "Find shortest path from router x to router y:\nEnter start-router: ";

    string start_router, end_router;
    int start_router_, end_router_, i;
    //First router
    cin >> start_router;
    start_router_ = check(start_router);
    while (start_router_ >= num_of_vertex)
    {
        cout << "Must less than " << num_of_vertex << " routers, enter again: ";
        cin >> start_router;
        start_router_ = check(start_router);
    }

    //Second router
    cout << "Enter end router: ";
    cin >> end_router;
    end_router_ = check(end_router);
    while (end_router_ >= num_of_vertex)
    {
        cout << "Must fewer than " << num_of_vertex << " routers, enter again: ";
        cin >> end_router;
        end_router_ = check(end_router);
    }
    //Shortest path
    vector<II> shortest_path = trace_shortest_path(start_router_, end_router_);
    int size = shortest_path.size();
    cout << "---------------------------------" << endl << "Router:  ";
    for (i = size - 1; i > 0; i--)
    {
        cout << shortest_path[i].second << " -----> ";
    }
    cout << shortest_path[0].second << endl;
    cout << "Path_dis: ";
    for (i = size - 1; i > 0; i--)
    {
        cout << shortest_path[i].first << " -----> ";
    }
    cout << shortest_path[0].first << endl;
}
void Graph::print_weight()
{
    cout << "Graph:" << endl << num_of_vertex << " routers - " << num_of_edge << " edges." << endl;
    cout << "Weight matrix:" << endl;
    cout << "\t";
    for (int i = 0; i < num_of_vertex - 1; i++)
    {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 1; i < num_of_vertex; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < num_of_vertex - 1; j++)
        {
            if (i > j) {
                if (getWeight(i, j) == INF) cout << "oo" << "\t";
                else cout << getWeight(i, j) << "\t";
            }
            else continue;
        }
        cout << endl;
    }
}
Graph:: ~Graph()
{
    adj->clear();
    if (dist != NULL) free(dist);
    if(trace != NULL) free(trace);
    if(check_if_visted != NULL) free(check_if_visted);
}
