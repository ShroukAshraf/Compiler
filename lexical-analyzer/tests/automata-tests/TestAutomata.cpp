#include "TestAutomata.hpp"

TestAutomata::TestAutomata() {}

TestAutomata::~TestAutomata(){};

void TestAutomata::SetUp(){

};

void TestAutomata::TearDown(){};

TEST(TestAutomata, CreateNodeZeroParametersNFA_1) {
  Automata *automataNfa = new NFA((int)'a', (int)'z');
  for (int expectedNodeId = 0; expectedNodeId < 100; expectedNodeId++) {
    stateID realNodeId = automataNfa->createNode();
    EXPECT_EQ(realNodeId, expectedNodeId);
  }
  delete automataNfa;
}

TEST(TestAutomata, CreateNodeZeroParametersDFA_2) {
  Automata *automataDfa = new DFA;
  for (int expectedNodeId = 0; expectedNodeId < 100; expectedNodeId++) {
    stateID realNodeId = automataDfa->createNode();
    EXPECT_EQ(realNodeId, expectedNodeId);
  }
  delete automataDfa;
}

TEST(TestAutomata, CreateNodeNonZeroParametersNFA_3) {
  Automata *nfa = new NFA((int)'a', (int)'z');
  stateID realNodeId = nfa->createNode(ACCEPTED, 10, "id");
  testNodeCreation(nfa, realNodeId, 0, true, false, 0, ACCEPTED, "id", 10, 1);
  delete nfa;
}

TEST(TestAutomata, CreateNodeNonZeroParametersDFA_4) {
  Automata *dfa = new DFA;
  stateID realNodeId = dfa->createNode(ACCEPTED, 10, "id");
  testNodeCreation(dfa, realNodeId, 0, true, false, 0, ACCEPTED, "id", 10, 1);
  delete dfa;
}

TEST(TestAutomata, AddingTransitionsNfa_5) {
  Automata *nfa = new NFA((int)'a', (int)'z');
  int rootNodeId = nfa->createNode(INTERMEDIATE, 0, "");
  EXPECT_EQ(rootNodeId, 0);
  EXPECT_EQ(nfa->getStateType(0), INTERMEDIATE);
  for (int i = 1; i <= 26; i++) {
    int currentNodeId = nfa->createNode(ACCEPTED, 50 - i, "id");
    testNodeCreation(nfa, currentNodeId, i, true, false, 0, ACCEPTED, "id",
                     50 - i, i + 1);
  }
  int to = 1;
  for (char trans = 'a'; trans <= 'z'; trans++, to++) {
    nfa->addTransition(trans, rootNodeId, to);
  }
  testTrans(nfa->getAllAttributes(), 'a', 'z');
}

void testTrans(std::set<char> trans, char startTrans, char endTrans) {
  int sz = (int)endTrans - (int)startTrans + 1;
  ASSERT_TRUE(sz == (int)trans.size());
  std::set<char>::iterator iter = trans.begin();
  while (iter != trans.end()) {
    EXPECT_TRUE(startTrans <= endTrans);
    EXPECT_EQ(*iter, startTrans);
    iter++;
    startTrans++;
  }
}

void testNodeCreation(Automata *automata, stateID realNodeId, stateID nodeId,
                      bool acceptance, bool phi, int rootId,
                      StateType stateType, std::string tokenClass,
                      int precedence, int numberOfStates) {
  EXPECT_EQ(nodeId, realNodeId);
  EXPECT_EQ(automata->isAccepted(realNodeId), acceptance);
  EXPECT_EQ(automata->isPHI(realNodeId), phi);
  EXPECT_EQ(automata->getRootID(), rootId);
  EXPECT_EQ(automata->getStateType(realNodeId), stateType);
  EXPECT_EQ(automata->getTokenClass(realNodeId), tokenClass);
  EXPECT_EQ(automata->getPrecedence(realNodeId), precedence);
  EXPECT_EQ(automata->getNumberOfStates(), numberOfStates);
}
