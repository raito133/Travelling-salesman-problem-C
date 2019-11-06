#include "pch.h"
#include "bnbSolver.h"
#include "Node.h"


struct comp
{
	bool operator()(Node* lhs, Node* rhs)
	{
		return lhs->getBound() > rhs->getBound();
	}
};

void bnbSolver::solve()
{
	std::priority_queue<Node*, std::vector<Node*>, comp> pq;
	std::vector<int> currentVertices;
	Node* root = new Node(currentVertices, 0, *&currentMatrix.getMatrix());
	int bestPathLength = -1;
	std::vector<int> bestVertices = root->getVertices();
	pq.push(root);
	while (!pq.empty())
	{
		Node* min = pq.top();
		pq.pop();
		if (min->getBound() < bestPathLength || bestPathLength == -1)
		{
			for (int i = 1; i < currentMatrix.getDimension(); i++)
			{

				if (min->visited(i))
					continue;
				Node* child = new Node(min->getVertices(), i, *&currentMatrix.getMatrix());

				if (child->getVertices().size() == currentMatrix.getDimension())
				{
					std::vector<int> currentVertices = child->getVertices();
					currentVertices.erase(currentVertices.begin());
					if (bestPathLength > currentMatrix.calculatePath(currentVertices) || bestPathLength == -1)
					{
						bestPathLength = currentMatrix.calculatePath(currentVertices);
						bestVertices = child->getVertices();
					}
					delete child;

				}
				else
				{
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
	//clean
	Node* v;
	while (!pq.empty())
	{
		v = pq.top();
		pq.pop();
		delete v;
	}
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
