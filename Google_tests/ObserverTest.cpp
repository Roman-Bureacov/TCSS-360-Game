//
// Created by iwant on 8/8/2025.
//
//

#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <vector>
#include "../src/include/ObserverPattern.h" // adjust include path

// Test observer that records notifications
struct TestObserver : public Observer {
    int updateCount = 0;
    int specificCount = 0;
    std::string lastProperty;
    std::vector<std::string> allProperties;

    void Update(Subject* /*theChangedSubject*/, const std::string& thePropertyName) override {
        updateCount++;
        lastProperty = thePropertyName;
        allProperties.push_back(thePropertyName);
        if (thePropertyName == "special") {
            specificCount++;
        }
    }
};

// Minimal concrete Subject for testing
struct TestSubject : public Subject {
    using Subject::notify; // expose notify for testing
};

TEST(ObserverPatternTest, SingleObserverReceivesNotification) {
    auto obs = std::make_shared<TestObserver>();
    TestSubject subj;

    subj.attach(obs);
    subj.notify("special");

    EXPECT_EQ(obs->updateCount, 1);
    EXPECT_EQ(obs->specificCount, 1);
    EXPECT_EQ(obs->lastProperty, "special");
}

TEST(ObserverPatternTest, MultipleObserversAllReceiveNotification) {
    auto obs1 = std::make_shared<TestObserver>();
    auto obs2 = std::make_shared<TestObserver>();
    TestSubject subj;

    subj.attach(obs1);
    subj.attach(obs2);
    subj.notify("event");

    EXPECT_EQ(obs1->updateCount, 1);
    EXPECT_EQ(obs2->updateCount, 1);
    EXPECT_EQ(obs1->lastProperty, "event");
    EXPECT_EQ(obs2->lastProperty, "event");
}

TEST(ObserverPatternTest, DetachPreventsFurtherNotifications) {
    auto obs1 = std::make_shared<TestObserver>();
    auto obs2 = std::make_shared<TestObserver>();
    TestSubject subj;

    subj.attach(obs1);
    subj.attach(obs2);

    subj.notify("first");
    subj.detach(obs1);
    subj.notify("second");

    EXPECT_EQ(obs1->updateCount, 1); // no update after detach
    EXPECT_EQ(obs2->updateCount, 2); // still receives both
}

TEST(ObserverPatternTest, NotifyWithNoObserversIsSafe) {
    TestSubject subj;
    EXPECT_NO_THROW(subj.notify("anything"));
}

TEST(ObserverPatternTest, MultipleNotificationsAccumulate) {
    auto obs = std::make_shared<TestObserver>();
    TestSubject subj;

    subj.attach(obs);
    subj.notify("one");
    subj.notify("two");
    subj.notify("special");

    EXPECT_EQ(obs->updateCount, 3);
    EXPECT_EQ(obs->specificCount, 1);
    EXPECT_EQ(obs->allProperties.size(), 3u);
    EXPECT_EQ(obs->allProperties[0], "one");
    EXPECT_EQ(obs->allProperties[1], "two");
    EXPECT_EQ(obs->allProperties[2], "special");
}

TEST(ObserverPatternTest, DetachNonexistentObserverDoesNothing) {
    auto obs1 = std::make_shared<TestObserver>();
    auto obs2 = std::make_shared<TestObserver>();
    TestSubject subj;

    subj.attach(obs1);
    EXPECT_NO_THROW(subj.detach(obs2)); // obs2 was never attached
    subj.notify("ping");

    EXPECT_EQ(obs1->updateCount, 1);
    EXPECT_EQ(obs2->updateCount, 0);
}
