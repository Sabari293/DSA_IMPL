#include "two_three_four.h"
using namespace std;
int main()
{
    int n;
    if (!(cin >> n))
        return 0;

    TwoThreeFourTree *tree = new TwoThreeFourTree();
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (!(cin >> x)) break;
        tree->insert(x);
    }

    BigNode *newroot = tree->convert();
    TTF(newroot);
    cout << endl;

    return 0;
}
