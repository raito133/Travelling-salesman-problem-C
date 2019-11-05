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
	Node* root = new Node(currentVertices, 0, *&currentMatrix.getMatrix());
	int bestPathLength = -1;
	std::vector<int> bestVertices = root->getVertices();
	pq.push(root);
	while (!pq.empty())
	{
		Node* min = pq.top();
		pq.pop();
		/*if (min->getVertices().size() == currentMatrix.getDimension())
		{
			bestVertices = min->getVertices();
			break;
		}*/
		if (min->getBound() <= bestPathLength || bestPathLength == -1)
		{
			for (int i = 1; i < currentMatrix.getDimension(); i++)
			{

				if (min->visited(i))
					continue;
				Node* child = new Node(min->getVertices(), i, *&currentMatrix.getMatrix());

				if (child->getVertices().size() == currentMatrix.getDimension())
				{
					std::vector<int> currentVertices = child->getVertices();
					for (const int x : child->getVertices())
						std::cout << x << " ";
					std::cout << "\n";
					currentVertices.erase(currentVertices.begin());
					if (bestPathLength > currentMatrix.calculatePath(currentVertices) || bestPathLength == -1)
					{
						std::cout << "\nBestPathLength: " << bestPathLength << " vs " << currentMatrix.calculatePath(currentVertices) << "\n";
						bestPathLength = currentMatrix.calculatePath(currentVertices);
						bestVertices = child->getVertices();
					}
					delete child;


				}
				else
				{
					if (bestPathLength >= child->getBound() || bestPathLength == -1)
					{
						/*std::cout << "galaz: ";
						for (const int x : child->getVertices())
						std::cout << x << " ";
						std::cout << "Bound: " << child->getBound() << std::endl;*/
						pq.push(child);
					}
					else
					{
						/*std::cout << "Odrzucam galaz: ";
						for (const int x : child->getVertices())
						std::cout << x << " ";
						std::cout << "Bound: " << child->getBound() << std::endl;*/
						delete child;
					}

				}


			}
		}
		else
		{
			/*std::cout << "Skip: " << min->getBound() << " vs " << bestPathLength;*/
			break;
		}
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
	for (const int x : bestVertices)
		std::cout << x << " ";
	bestVertices.erase(bestVertices.begin());
	std::cout << "Path length: " << currentMatrix.calculatePath(bestVertices) << "\n";
	
}

bnbSolver::bnbSolver(ATSPMatrix &atspMatrix)
{
	currentMatrix = atspMatrix;
}

bnbSolver::~bnbSolver()
{
}
