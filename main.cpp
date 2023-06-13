#include <iostream>
#include <stack>
#include <queue> // queue, priority_queue
#include <vector>
#include <deque>
#include <list>
#include <type_traits>
using namespace std;

template <
        template<typename...> class Adapter,
        typename T,
        typename ...Params
>
void recorrer_adaptador(Adapter<T, Params...>& adapter) {
    while (!adapter.empty()) {
        if constexpr (is_same_v<queue<T>, Adapter<T>> == true)
            cout << adapter.front() << " "; // queue
        else
            cout << adapter.top() << " "; // stack y priority queue
        adapter.pop();
    }
}

template <
        template<typename...> class Adapter,
        typename T,
        typename ...Params,
        typename Callable
>
void recorrer_adaptador(Adapter<T, Params...>& adapter, Callable caller) {
    while (!adapter.empty()) {
        if constexpr (is_same_v<queue<T>, Adapter<T>> == true)
            caller(adapter.front());
        else
            caller(adapter.top());
        adapter.pop();
    }
}


void ejemplo_stack() {
    stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.push(40);
    s1.push(50);
    s1.push(60);

    cout << s1.top() << endl;
    s1.pop();
    cout << s1.top() << endl;
    s1.pop();

    while (!s1.empty()) {
        cout << s1.top() << endl;
        s1.pop();
    }

    deque deq = {100, 200, 300, 400, 500};
    stack<int> s2(deq);
    for (int i = s2.size(); i != 0; --i) {
        cout << s2.top() << " ";
        s2.pop();
    }

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    stack<int, vector<int>> s3(vec);
    cout << endl;
    recorrer_adaptador(s3);
}

void ejemplo_queue() {
    deque deq = {10, 20, 30, 40, 50};
    queue<int> q1(deq);
    while(!q1.empty()) {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << endl;

    list lst = {10, 20, 30, 40, 50};
    queue<int, list<int>> q2(lst);
    recorrer_adaptador(q2);

    deque deq2 = {100, 200, 300, 400, 500};
    queue<int> q3(deq2);
    recorrer_adaptador(q3, [](auto item) {
       cout << item << endl;
    });

}

int main() {
//    ejemplo_stack();
    ejemplo_queue();
    return 0;
}
