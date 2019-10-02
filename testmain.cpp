#include "ExpressionManager.h"
#include <string>

int main() {
    ExpressionManager trial1;
    string ans;
    
    ans = trial1.postfixEvaluate("1 2 + 3 /");
    cout << "The answer is: " << ans << "|" << endl;
    return 0;
}