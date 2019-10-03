#include "ExpressionManager.h"
#include <string>

int main() {
    ExpressionManager trial1;
    bool ans;
    
    ans = trial1.isBalanced("{ [ ) }");
    cout << "The answer is: " << endl;
    if(ans){
        cout << "It worked!" << endl;
    }else{
        cout << "unbalanced. slow things down" << endl;
    }
    return 0;
}