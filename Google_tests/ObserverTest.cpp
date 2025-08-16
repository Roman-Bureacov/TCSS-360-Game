//
// Created by iwant on 8/8/2025.
// test to verify if the observer pattern works properly
//

#include "../src/include/ObserverPattern.h"
#include "gtest/gtest.h"

std::string testString = "test string bingbingwahoo!";

struct A : Observer {
    int myInt = 0;
    int mySpecificInt = 0;

    void Update(Subject *theChangedSubject, const std::string &thePropertyName) override {
        myInt++;
        if (thePropertyName == testString) mySpecificInt++;
    }
};

struct B : Subject {

};


TEST(ObserverTest, SubjectIsNotified) {
    A a = A();
    B b = B();

    b.attach(std::unique_ptr<Observer>(&a));

    b.notify(testString);

    ASSERT_EQ(a.myInt, 1);
    ASSERT_EQ(a.mySpecificInt, 1);
}
