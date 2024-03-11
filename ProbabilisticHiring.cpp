#include <iostream>
#include <cstdlib>
#include <ctime>

class Candidate {
public:
    virtual double evaluateSuccess() const {
        return -1.0;  // Dummy value, to be overridden by derived classes
    }
};

class Alice : public Candidate {
public:
    double evaluateSuccess() const {
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        return (randomValue <= 0.7) ? 0.9 : 0.6;
    }
};

class Bob : public Candidate {
public:
    double evaluateSuccess() const {
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        return (randomValue <= 0.8) ? 0.8 : 0.95;
    }
};

class HiringManager {
public:
    const Candidate* evaluateCandidates(const Candidate& candidate1, const Candidate& candidate2) const {
        double aliceSuccess = candidate1.evaluateSuccess();
        double bobSuccess = candidate2.evaluateSuccess();

        std::cout << "Alice's expected success probability: " << aliceSuccess * 100 << "%" << std::endl;
        std::cout << "Bob's expected success probability: " << bobSuccess * 100 << "%" << std::endl;

        return (aliceSuccess > bobSuccess) ? &candidate1 : &candidate2;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    Alice alice;
    Bob bob;

    HiringManager hiringManager;
    const Candidate* selectedCandidate = hiringManager.evaluateCandidates(alice, bob);

    if (selectedCandidate == &alice) {
        std::cout << "\nSelected candidate: Alice" << std::endl;
    } else {
        std::cout << "\nSelected candidate: Bob" << std::endl;
    }

    return 0;
}
