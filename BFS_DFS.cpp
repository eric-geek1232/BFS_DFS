/*By Eric 20/01/2021 -DFS & BFS- */
#include <iostream>
#include <queue>

#define CONVERT_CHAR_TO_INDEX(caracter) (caracter - 'A') 
#define CONVERT_INT_TO_CHAR(integer) (char(integer))

using namespace std;

// LINKED LIST STRUCTURE
struct Node
{
	char vertex;
	bool isVisited;
	Node *next;
};

class Graph
{
	private:
		Node **adjacencyList;
		queue<Node*> queue;
		int nVertices;
		
		Node *createVertex(char vertex);
		void insertList(Node *&edges, char vertex);
		void printList(Node *edges);
		void DFS(Node *edges);
		void BFS(Node *edges);
		
	public:
		Graph();
		Graph(int nVertices);
		void setAdjacencyList();
		void showAdjacencyList();
		void startBFS(char start);
		void startDFS(char start);
		void resetNodesVisited();
		bool isEmpty();
};

Graph::Graph()
{
	nVertices = 0;
}

Graph::Graph(int nVertices)
{
	this->nVertices = nVertices;
	adjacencyList = new Node*[nVertices];
	
	for (int v = 0; v < nVertices; v++) {
		// CREATE HASH TABLE
		adjacencyList[v] = NULL;
		insertList(adjacencyList[v], CONVERT_INT_TO_CHAR(v + 65));
	}
}

Node *Graph::createVertex(char vertex)
{
	Node *newNode = new Node();
	
	newNode->vertex = vertex;
	newNode->next = NULL;
	newNode->isVisited = false;
	
	return newNode; 
}

void Graph::setAdjacencyList()
{
	char vertex;
	char noPath;
	char currentVertex;
	
	for (int v = 0; v < nVertices; v++) {
		currentVertex = CONVERT_INT_TO_CHAR(v + 65);
		cout<< "\n\n\t Add the routes of "<< currentVertex<< endl;
		
		// CREATE ROUTE
		do {
			cout<< "\n [Warning]-Would you like to add routes? [s/n]: ";
			cin>> noPath;
			
			noPath = toupper(noPath);
			
			if (noPath != 'S') {
				break;
			}
			
			cout<< "\n\n "<< currentVertex<< "--> ";
			cin>> vertex;
			
			vertex = toupper(vertex);
			
			// INSERT ROUTE
			int index = CONVERT_CHAR_TO_INDEX(vertex);
			insertList(adjacencyList[index], currentVertex);
			insertList(adjacencyList[v], vertex);
			
		} while (noPath == 'S');
		
		cout<< "\n";
	}
}

void Graph::insertList(Node *&edges, char point)
{
	// INSERT ALWAYS AT THE END OF THE LIST
	if (edges == NULL) {
		Node *newNode = createVertex(point);
		edges = newNode;
		return;		
	}
	
	// KEEP ITERATING
	insertList(edges->next, point);
}

void Graph::showAdjacencyList()
{
	cout<< "\n\n\t\t\tShowing Adjacency List...\n"<< endl;
	cout<< "\n\t\tVertices\n"<< endl;
	
	// ITERATE EACH OF THE LISTS
	for (int v = 0; v < nVertices; v++) {
		printList(adjacencyList[v]);
		cout<< "\n\n";	
	}	
}

void Graph::printList(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) {
		return;
	}
	
	cout<< " ("<< edges->vertex<< ")   ";
	
	// KEEP ITERATING
    	printList(edges->next);
}

void Graph::startDFS(char start)
{	
	cout<< " ("<< start<< ")-->";
	int index = CONVERT_CHAR_TO_INDEX(start);
	
	adjacencyList[index]->isVisited = true;
	DFS(adjacencyList[index]->next);
}

void Graph::DFS(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) {
		return;	
	}
    
    	// GET NEIGHBOR
    	int index = CONVERT_CHAR_TO_INDEX(edges->vertex);
    
    	if (!adjacencyList[index]->isVisited) {
    		// RECURSIVE FUNCTION
    		startDFS(adjacencyList[index]->vertex);
    		return;
	}
	
	// GO DEEPLY
	DFS(edges->next);
}

void Graph::startBFS(char start)
{
	cout<< " ("<< start<< ")";
	int index = CONVERT_CHAR_TO_INDEX(start);
	
	adjacencyList[index]->isVisited = true;
	BFS(adjacencyList[index]->next);
}

void Graph::BFS(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) {
		// DEQUEUE AND CONTINUE WITH THE NEXT NODE
		if (!queue.empty()) {
			Node *next = queue.front();
			cout<< "-->("<< next->vertex<< ")";
			queue.pop();
			
			BFS(next->next);	
		}
		
		return;	
	}
    
    	// GET NEIGHBOR
    	int index = CONVERT_CHAR_TO_INDEX(edges->vertex);
    
    	// ENQUEUE
    	if (!adjacencyList[index]->isVisited) {
    		adjacencyList[index]->isVisited = true;
    		queue.push(adjacencyList[index]);
	}
	
	// CONTINUE WITH THE NEXT NODE
    	BFS(edges->next);
}

bool Graph::isEmpty() 
{
	return nVertices == 0 ? true : false; 
}

void Graph::resetNodesVisited()
{
	for (int v = 0; v < nVertices; v++) {
		adjacencyList[v]->isVisited = false;
	}
}

int main()
{
	Graph *graph = new Graph();
	char start;
	int nVertices;
	
	int option;
	
	do {
		cout<< "\t DFS AND BFS\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Create Graph"<< endl;
		cout<< " [2] BFS"<< endl;
		cout<< " [3] DFS"<< endl;
		cout<< " [4] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				delete graph;
				
				cout<< "\n\n Type the number of vertices ";
				cin>> nVertices;
				
				graph = new Graph(nVertices);
				
				graph->setAdjacencyList();
				break;
				
			case 2:
				if (!graph->isEmpty()) {
					graph->resetNodesVisited();
					graph->showAdjacencyList();
					
					cout<< "\n From what which point would you like to start? ";
					cin>> start;
					
					start = toupper(start);
					
					cout<< "\n\n Sort: ";
					graph->startBFS(start);
					cout<< "\n"<< endl;	
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
			
			case 3:
				if (!graph->isEmpty()) {
					graph->resetNodesVisited();
					graph->showAdjacencyList();
					
					cout<< "\n From what which point would you like to start? ";
					cin>> start;
					
					start = toupper(start);
					
					cout<< "\n\n Sort: ";
					graph->startDFS(start);
					cout<< "\n"<< endl;	
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
				
			case 4:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 4);
	
	return 0;
}
