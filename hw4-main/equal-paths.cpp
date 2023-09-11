#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int checkPath (Node* n, int depth)
{
    if (n == NULL)
    {
        return 0;
    }
    if (n->left == NULL && n->right == NULL) // no children, only node
    {
        return depth;
    }
    else if (n->left != NULL && n->right != NULL) // 2 children
    {
        int left = checkPath(n->left, 1+ depth);
        int right = checkPath(n->right, 1+ depth);
        if (left == right)
        {
            return left;
        }
        else // depth doesn't match up, tree paths not balanced
        {
            return -1;
        }
    }
    else if (n->left != NULL || n->right != NULL) // 1 child
    {
        if (n->left == NULL) // right child exists
        {
            return checkPath(n->right, depth +1);
        }
        else // left exists
        {
            return checkPath(n->left, depth+1);
        }
    }
}

bool equalPaths(Node * root)
{
    // Add your code below
    if (checkPath(root, 1) >= 0)
    {
        return true;
    }
    return false;
}

