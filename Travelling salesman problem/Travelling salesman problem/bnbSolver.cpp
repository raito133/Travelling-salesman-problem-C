#include "pch.h"
#include "bnbSolver.h"
#include "Node.h"

//void bnbSolver::solve()
//{
//	std::vector<int> currentVertices;
//	
//	Node* root = new Node(currentVertices, 0, currentMatrix.getMatrix());
//	Node* currentNode = root;
//	int bestBound;
//	Node* nextNode = root;
//	while (currentNode->vertices.size() != currentMatrix.getDimension())
//	{
//		bestBound = -1;
//		for (int i = 1; i < currentMatrix.getDimension(); i++)
//		{
//			if (currentNode->visited(i))
//				continue;
//
//			Node* child = new Node(currentNode->vertices, i, currentMatrix.getMatrix());
//			if (child->getBound() < bestBound || bestBound == -1)
//			{
//				bestBound = child->getBound();
//				nextNode = child;
//			}
//		}
//		currentNode = nextNode;
//	}
//	std::vector<int> finalVertices;
//	finalVertices = currentNode->vertices;
//	finalVertices.erase(finalVertices.begin());
//	std::cout << "0->";
//	for (const int x : finalVertices)
//		std::cout << x << "->";
//	std::cout << "0";
//	std::cout << "\nPath length: " << currentMatrix.calculatePath(finalVertices);
//}

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
	Node* root = new Node(currentVertices, 0, currentMatrix.getMatrix());
	int bestPartialPath = -1;
	std::vector<int> bestVertices = root->getVertices();
	pq.push(root);
	int iterations = 0;
	while (!pq.empty())
	{
		Node* min = pq.top();
		pq.pop();
		if (min->getVertices().size() == currentMatrix.getDimension())
		{
			bestVertices = min->getVertices();
			break;
		}
		
		if (min->getBound() > bestPartialPath)
		{
			for (int i = 1; i < currentMatrix.getDimension(); i++)
			{

				if (min->visited(i))
					continue;
				Node* child = new Node(min->getVertices(), i, currentMatrix.getMatrix());
				if (currentMatrix.calculatePartialPath(child->getVertices())< bestPartialPath || bestPartialPath == -1)
				{
					bestPartialPath = currentMatrix.calculatePartialPath(child->getVertices());
					bestVertices = child->getVertices();
				}
				if (bestPartialPath < child->getBound())
				{
					pq.push(child);
				}
				else
					delete child;
			}
		}
		delete min;
		iterations++;
						
	}
	//clean
	Node* v;
	while (!pq.empty())
	{
		v = pq.top();
		pq.pop();
		delete v;
	}
	for (const int x : bestVertices)
		std::cout << x << " ";
	bestVertices.erase(bestVertices.begin());
	std::cout << "Path length: " << currentMatrix.calculatePath(bestVertices) << "\n";
	
}

bnbSolver::bnbSolver(ATSPMatrix atspMatrix)
{
	currentMatrix = atspMatrix;
}

bnbSolver::~bnbSolver()
{
}
