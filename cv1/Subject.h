#pragma once

#include <vector>

#include "Observer.h"

using namespace std;

class Subject {
private:
    vector<Observer*> observers;

public:
    void Attach(Observer* observer) {
        observers.push_back(observer);
    }

    void Detach(Observer* observer) {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void Notify() {
        for (Observer* observer : observers) {
            observer->Update();
        }
    }
};