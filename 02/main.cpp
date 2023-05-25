#include <iostream>
#include "DirectedGraph.h"
#include "Time.h"


using namespace std;
int main() {
    Time start("07/01", "17:01");
    Time end("11/01 ", "16:18");
    cout << start << end << endl;
    unsigned int m = howLongBetween(start,end);
    cout << m << endl;
/*    DirectedGraph<string, double> dg(0.0);
    dg.addVertex("mali");
    dg.addEdge("mali", "abramovitch", 27.0);
    dg.addEdge("mali", "grandmizer", 27.0);
    dg.addEdge("grandmizer","mafkura", 100.0);
    dg.addEdge("mafkura", "grandmizer", 88.0);
    dg.addEdge("advanced","cpp", 11);
    dg.addEdge("advanced","grandmizer", 12);
    dg.addEdge("advanced","mafkura", 13);
    dg.addEdge("since ever","was begin", 99);
    dg.addEdge("mafkura","was begin", 99);
    dg.addEdge("was begin", "since ever", 88);
    dg.addEdge("mafkura", "since ever", 88);

    cout << "dg:\n" << dg << endl;
    deque<string> o = dg.getOutGoingVertex("advanced");
    deque<string> i = dg.getInGoingVertex("grandmizer");
    deque<string> c = dg.canBeReachedFromVertex("mali");
    ostream_iterator<string> oit(cout, ", ");
    cout << "################\n";
    copy(o.begin(), o.end(), oit);
    cout << endl;
    ostream_iterator<string> oit2(cout, ", ");
    copy(i.begin(), i.end(), oit2);
    ostream_iterator<string> oit3(cout, ", ");
    cout << "\n";
    copy(c.begin(), c.end(), oit3);
    cout << "\n\n" << endl;
    dg.removeVertex("advanced");
    dg.removeEdge("mali", "abramovitch");
    cout << dg << "\n\n\n";
    dg.addEdge("grandmizer","mafkura", 50.0);
    cout << dg << "\n\n\n";
    cout << dg("grandmizer","mafkura") << "\n\n\n";
    string r = "abramovitch";
    DirectedGraph<string, double> dg2(dg);
    dg.removeVertex(r);
    cout <<  "dg:\n" << dg << endl;
    auto dg3(move(dg2));
    cout <<  "dg3:\n" << dg3 << endl;
    dg2 = move(dg3);
    cout << "dg2:\n" << dg2 << endl;
    cout <<  "dg3:\n" << dg3 << endl;*/
    return 0;
}
