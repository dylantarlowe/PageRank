#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;

class AdjacencyList
{
    private:
        //Think about what member variables you need to initialize
        // map: from link, to link, inputs

    public:
        //Think about what helper functions you will need in the algorithm};
        std::map<string,int> linkMap;
        std::map<string,vector<pair<string,double>>> graph;
        vector<double> rVect;
        void PageRank(int n);
        void insertEdge(string from, string to);
        void updateOutRank(string from);
        void insertLinkMap(string from, string to, int &key);
        void setRVector();
        void multiply();
};

void AdjacencyList::multiply() {
    // take each from, to and multiply it by the r vector
    // you multiply across the row of the matrix. [from][to] value * rVector[to];
    // go down the column to multiply, then move onto the next column
    vector<double> temp(rVect.size());
    std::fill(temp.begin(), temp.end(), 0);
    // right now I have <string, vector pair <string, int>
    // get indexes by using the linkMap
    int x;
    int y;
    for (auto iterCol = graph.begin(); iterCol != graph.end(); iterCol++) {
        for (auto iterRow = graph[iterCol->first].begin(); iterRow != graph[iterCol->first].end(); iterRow++) {
            // multiply to r vect and add it to
            // multiply by rVect[from], store in the row of the to
            y = linkMap[iterCol->first];
            x = linkMap[iterRow->first];
            temp[x] += iterRow->second * rVect[y];
        }
    }
    rVect = temp;
}


void AdjacencyList::updateOutRank(string from) {
    // keep track of each from and how many the from points to, that is the size of vector... the mValue is 1/outputs
    for (auto iter = graph[from].begin(); iter != graph[from].end(); iter++) {
        iter->second = double(double(1) / double(graph[from].size()) );
    }
}

void AdjacencyList::setRVector() {
    // sets initial values for r vector
    float x = this->linkMap.size();
    for (int i = 0; i < x; i++)  {
        rVect.push_back(double(1) / double(x));
    }
}

void AdjacencyList::PageRank(int n)  {
    // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages
    // and rounding rank to two decimal places

    // create the rVect, each element is 1 / size
    setRVector();

    for (int i = 0; i < n; i++) {
        multiply();
    }

    // access the link map, then its corresponding value in the rVect
    for (auto iter = linkMap.begin(); iter != linkMap.end(); iter++) {
        cout << setprecision(2) << iter->first << " ";
        printf("%.2f", rVect[iter->second]);
        cout << endl;
    }
}

// create a map that stores <link, key> for the adjacent list
void AdjacencyList::insertLinkMap(string from, string to, int &key) {
    if (linkMap.find(from) == linkMap.end()) {
        linkMap.insert(pair<string,int> (from,key));
        key++;
    }
    if (linkMap.find(to) == linkMap.end()) {
        linkMap.insert(pair<string, int>(to, key));
        key++;
    }
};

void AdjacencyList::insertEdge(string from, string to) {
    // mValue = 1 / numOutputs
    graph[from].push_back(std::make_pair(to,0));
    // update the "matrix" value
    updateOutRank(from);
    if(graph.find(to) == graph.end())
        graph[to] = {};
}



int main() {
    int no_of_lines, power_iterations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_iterations;
    AdjacencyList adjList;
    int key = 0;
    for(int i = 0; i < no_of_lines; i++) {
        std::cin>>from;
        std::cin>>to;

        adjList.insertEdge(from, to);
        adjList.insertLinkMap(from,to, key);
    }

    adjList.PageRank(power_iterations - 1);
}