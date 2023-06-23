#include "Model.h"
#include <deque>

using namespace std;

int main() {
    deque<weak_ptr<Agent>> adq;
    deque<weak_ptr<Structure>> sdq;

    shared_ptr<Structure> c1 = make_shared<Castle>("Rivendale", 20,10, 100);
    shared_ptr<Structure> c2 = make_shared<Castle>("Blackness", 10,20, 20);
    shared_ptr<Structure> c3 = make_shared<Castle>("Sunnybrook", 30,0, 50);
    shared_ptr<Structure> f1 = make_shared<Farm>("Campbell", 20,20, 10,4);
    shared_ptr<Structure> f2 = make_shared<Farm>("Shire", 10,10, 2,3);
    shared_ptr<Structure> f3 = make_shared<Farm>("Dunvegan", 0,30, 6,3);

    sdq.push_back(c1);
    sdq.push_back(c2);
    sdq.push_back(c3);
    sdq.push_back(f1);
    sdq.push_back(f2);
    sdq.push_back(f3);

    shared_ptr<Agent> iriel = make_shared<Peasant>("Iriel", 0,0);
    shared_ptr<Agent> merry = make_shared<Peasant>("Merry", 0,0);
    shared_ptr<Agent> pippin = make_shared<Peasant>("Pippin", 0,0);
    shared_ptr<Agent> zug = make_shared<Peasant>("Zug", 0,0);
    shared_ptr<Agent> loki = make_shared<Thug>("Loki", 14,14);
    shared_ptr<Agent> gog = make_shared<Thug>("Gog", 24,24);
    shared_ptr<Agent> wallace = make_shared<Knight>("Wallas", sdq[0], sdq);
    adq.push_back(iriel);
    adq.push_back(merry);
    adq.push_back(pippin);
    adq.push_back(zug);
    adq.push_back(loki);
    adq.push_back(gog);
    adq.push_back(wallace);
    dynamic_pointer_cast<Knight>(adq[6].lock())->setDestination(sdq[2]); // wallace
    dynamic_pointer_cast<Peasant>(adq[3].lock())->addTask(sdq[3], sdq[2]); //Zug
    dynamic_pointer_cast<Thug>(adq[4].lock())->setCourse(180, 30); // Loki
    dynamic_pointer_cast<Thug>(adq[5].lock())->setCourse(270, 30); // Gog
    int c = 1;
    for (int i = 0; i < adq.size(); ++i) {
        adq[i].lock()->broadcastCurrentState();
    }
    while(c){
        cout << c <<endl;
        for (int i = 0; i < sdq.size(); ++i) {
            sdq[i].lock()->update();
            sdq[i].lock()->broadcastCurrentState();
        }
        for (int i = 0; i < adq.size(); ++i) {
            adq[i].lock()->update();
            adq[i].lock()->broadcastCurrentState();
        }
        cout << endl;
        --c;
    }
}


