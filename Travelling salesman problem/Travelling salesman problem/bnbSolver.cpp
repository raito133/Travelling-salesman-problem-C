#include "pch.h"
#include "bnbSolver.h"
#include "Node.h"


struct comp
{
	//comparator that determines if the node is better
	//a node is better if it has a lower Bound
	bool operator()(Node* lhs, Node* rhs)
	{
		return lhs->getBound() > rhs->getBound();
	}
};

void bnbSolver::solve()
{
	//initializing root and queue
	std::priority_queue<Node*, std::vector<Node*>, comp> pq;
	std::vector<int> currentVertices;
	Node* root = new Node(currentVertices, 0, *&currentMatrix.getMatrix());
	int bestPathLength = -1;
	std::vector<int> bestVertices = root->getVertices();
	pq.push(root);
	while (!pq.empty())
	{
		//take the best node from the queue
		Node* min = pq.top();
		pq.pop();
		
		//if the best node cant produce a better solution the search
		//can be ended
		if (min->getBound() < bestPathLength || bestPathLength == -1)
		{
			for (int i = 1; i < currentMatrix.getDimension(); i++)
			{

				//produce all children of the node
				if (min->visited(i))
					continue;
				Node* child = new Node(min->getVertices(), i, *&currentMatrix.getMatrix());

				//if the given node is a leaf
				if (child->getVertices().size() == currentMatrix.getDimension())
				{
					std::vector<int> currentVertices = child->getVertices();
					currentVertices.erase(currentVertices.begin());
					//calculate the cost of the path and compare with bestPathLength
					if (bestPathLength > currentMatrix.calculatePath(currentVertices) || bestPathLength == -1)
					{
						bestPathLength = currentMatrix.calculatePath(currentVertices);
						bestVertices = child->getVertices();
					}
					delete child;

				}
				else
				{
					//if a node is "promising" it is added to the queue
					if (bestPathLength > child->getBound() || bestPathLength == -1)
						pq.push(child);
					else
						delete child;
				}

			}
		}
		else
			break;
		delete min;
						
	}
	//clean, just in case
	Node* v;
	while (!pq.empty())
	{
		v = pq.top();
		pq.pop();
		delete v;
	}
	//set vertices for printing
	shortestPathVertices = bestVertices;
	
}

void bnbSolver::printShortestPath()
{
	for (const int x : shortestPathVertices)
		std::cout << x << "->";
	std::cout << "->0\n";
	shortestPathVertices.erase(shortestPathVertices.begin());
	std::cout << "Path length: " << currentMatrix.calculatePath(shortestPathVertices) << "\n";
}

bnbSolver::bnbSolver(ATSPMatrix &atspMatrix)
{
	currentMatrix = atspMatrix;
}

bnbSolver::~bnbSolver()
{
}
