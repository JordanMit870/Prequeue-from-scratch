 // Why the angle brackets? Grader reasons.
 // Don't change this or you will be sad :(
#include <prqueue.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing; // to replace "testing::Eq"

TEST(EmptyTest, Test) {
    prqueue<int> pq;
}

////////////CORE TESTS////////////
TEST(PRQueueCore, prequeDefult){
    prqueue<int> text;
    int expected = 0;
    ASSERT_THAT(text.size(), Eq(expected))<< "size=\"" << text.size() << "\""; 
    ASSERT_THAT(text.getRoot(), Eq(nullptr))<< "root value=\"" << text.getRoot() << "\"";
}
TEST(PRQueueCore, sizeTest){
    prqueue<int> text;
    int expected = 0;
    ASSERT_THAT(text.size(), Eq(expected))<< "size=\"" << text.size() << "\"";
    text.enqueue(22,4); 
    expected++;
    ASSERT_THAT(text.size(), Eq(expected))<< "size 2=\"" << text.size() << "\"";
}
TEST(PRQueueCore, enqueueTest){ //fixed-
    prqueue<int> text;
    int expected = 0;
    //text.getRoot()->priority = 4

    text.enqueue(22,4); 
    expected++;
    ASSERT_THAT(text.size(), Eq(expected))<< "size=\"" << text.size() << "\"";
    ASSERT_THAT(text.getRoot()->priority, Eq(4))<< "root priority=\"" << text.getRoot()->priority << "\"";
    //freezes when there is more that one slot...
    text.enqueue(49,7); //issue when enqueueing more than one num...
    expected++;
    ASSERT_THAT(text.size(), Eq(expected))<< "size 2=\"" << text.size() << "\"";
    ASSERT_THAT(text.getRoot()->right->priority, Eq(7))<< "right priority=\"" << text.getRoot()->right->priority << "\"";

    text.enqueue(1,2); 
    expected++;
    ASSERT_THAT(text.size(), Eq(expected))<< "size3=\"" << text.size() << "\"";
    ASSERT_THAT(text.getRoot()->left->priority, Eq(2))<< "left priority=\"" << text.getRoot()->left->priority << "\"";

    text.enqueue(0,5); 
    expected++;
    ASSERT_THAT(text.size(), Eq(expected))<< "size4=\"" << text.size() << "\"";
    ASSERT_THAT(text.getRoot()->right->left->priority, Eq(5))<< "right->left priority=\"" << text.getRoot()->right->left->priority << "\"";
    
}
TEST(PRQueueCore, distructor){
    prqueue<int> text;
    int expected = 0;

    text.enqueue(22,4);
    text.enqueue(49,7);
    text.enqueue(1,2);
    text.enqueue(0,5); 

    text.clear();
    ASSERT_THAT(text.size(), Eq(expected))<< "size=\"" << text.size() << "\""; 
    ASSERT_THAT(text.getRoot(), Eq(nullptr))<< "root value=\"" << text.getRoot() << "\"";

}
////////////CORE TESTS////////////

////////////USING TESTS////////////
TEST(PRQueueUsing, asStringTest){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    // text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);
    //may need to change do to spacing...
    ASSERT_THAT(text.as_string(), StrEq("1 value: Ben\n2 value: Sven\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";
    // ASSERT_THAT(text.as_string(), StrEq("1 value: Ben \n 2 value: Jen \n 2 value: Sven \n 3 value: Gwen"))<< "text=\"" << text.as_string() << "\"";
}
TEST(PRQueueUsing, peekTest){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);
    string temp = text.peek();
   
    //may need to change do to spacing...
    ASSERT_THAT( temp, Eq(text.getRoot()->left->value))<< "text=\"" << text.peek() << "\"";
    ASSERT_THAT(text.as_string(), StrEq("1 value: Ben\n2 value: Sven\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";
}
TEST(PRQueueUsing, dequeueTest){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);

    string temp = text.dequeue();
    ASSERT_THAT(text.getRoot(), Ne(nullptr));
    ASSERT_THAT(temp, StrEq("Ben"));

    ASSERT_THAT(text.getRoot()->value, StrEq("Gwen"))<< "text=\"" << text.getRoot()->value << "\"";
    //may need to change do to spacing...
    ASSERT_THAT(text.getRoot()->left->value, StrEq("Sven"))<< "text=\"" << text.getRoot()->left->value << "\"";
    ASSERT_THAT(text.as_string(), StrEq("2 value: Sven\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";
    ASSERT_THAT(text.size(), Eq(2))<< "size=\"" << text.size() << "\"";
}
TEST(PRQueueUsing, oneNodeDequeueTest){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    string temp = text.dequeue();

    ASSERT_THAT(temp, StrEq("Gwen"));
    ASSERT_THAT(text.getRoot(), Eq(nullptr)) << "text=\"" << text.getRoot() << "\"";
}
////////////USING TESTS////////////

//////////DUPLICATES TESTS////////////
TEST(PRQueueDuplicates, enqueuAsStringDuplicates){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);

    ASSERT_THAT(text.as_string(), StrEq("1 value: Ben\n2 value: Jen\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";
    
    text.enqueue("Sven", 2);
    ASSERT_THAT(text.as_string(), StrEq("1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";

    ASSERT_THAT(text.getRoot()->left->priority, Eq(2));
    ASSERT_THAT(text.getRoot()->left->link->priority, Eq(2));
}
TEST(PRQueueDuplicates,clearWithDuplicents){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);

    text.clear();
    ASSERT_THAT(text.size(), Eq(0))<< "size=\"" << text.size() << "\""; 
    ASSERT_THAT(text.getRoot(), Eq(nullptr))<< "root value=\"" << text.getRoot() << "\"";
}
TEST(PRQueueDuplicates,dequeueWithDuplicates){ 
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);

    text.dequeue(); //lose Ben
    text.dequeue(); //lose Jen //breaks here-

    ASSERT_THAT(text.getRoot()->left->value, StrEq("Sven"))<< "text=\"" << text.getRoot()->left->value << "\"";
    ASSERT_THAT(text.as_string(), StrEq("2 value: Sven\n3 value: Gwen\n"))<< "text=\"" << text.as_string() << "\"";
    ASSERT_THAT(text.size(), Eq(2))<< "size=\"" << text.size() << "\"";

}
////////////DUPLICATES TESTS////////////

////////////COPY TESTS////////////
TEST(PRQueueCopying, equalOperator){ //breaking code-
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);
    prqueue<string> cases;
    cases = text;
    ASSERT_THAT(cases.getRoot()->value, StrEq("Gwen"));
    ASSERT_THAT(cases.size(), Eq(text.size()));
    ASSERT_THAT(cases.getRoot()->left->value, StrEq(text.getRoot()->left->value));
    ASSERT_THAT(cases.getRoot()->left->link->value, StrEq(text.getRoot()->left->link->value));
    prqueue<string> newTest;
    cases = newTest;
    ASSERT_THAT(cases.getRoot(), Eq(nullptr));
    
}

TEST(PRQueueCopying, copyOpeater){
    prqueue<string> text;
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);
    prqueue<string> cases(text);

    ASSERT_THAT(cases.getRoot()->value, StrEq("Gwen"));
    ASSERT_THAT(cases.size(), Eq(text.size()));
    ASSERT_THAT(cases.getRoot()->left->value, StrEq(text.getRoot()->left->value));
    ASSERT_THAT(cases.getRoot()->left->link->value, StrEq(text.getRoot()->left->link->value));
}
////////////COPY TESTS////////////

////////////EQUALITY TESTS////////////
TEST(PRQueueEquality,equalTrees){
    //a and b are equal. c equals neither
    prqueue<string> a;
    a.enqueue("Gwen", 3);
    a.enqueue("Jen", 2);
    a.enqueue("Ben", 1);
    a.enqueue("Sven", 2);

    prqueue<string> b;
    b = a;

    prqueue<string> c;
    c.enqueue("Jen", 2);
    c.enqueue("Sven", 2);
    c.enqueue("Gwen", 3);
    c.enqueue("Ben", 1);

    ASSERT_THAT(a==b, Eq(true));
    ASSERT_THAT(a==c, Eq(false));
    ASSERT_THAT(c==b, Eq(false));
}

////////////EQUALITY TESTS////////////

////////////ITERATOR TESTS////////////
TEST(PRQueueIterator,beginTest){
    prqueue<string> text;
    string v = "";
    int p = 0;

    text.begin(); //sets curr only
    text.next(v, p);
    ASSERT_THAT(p, Eq(0));
    ASSERT_THAT(v, StrEq(""));
    
    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);

    text.begin(); //sets curr only
    text.next(v, p); //should be Ben, 1
    ASSERT_THAT(p, Eq(1));
    ASSERT_THAT(v, StrEq("Ben"));
    

}
TEST(PRQueueIterator, nextHeck){
    prqueue<string> text;
    string v = "";
    int p = 0;

    text.enqueue("Gwen", 3);
    text.enqueue("Jen", 2);
    text.enqueue("Ben", 1);
    text.enqueue("Sven", 2);

    text.begin(); //sets curr only
    
    ASSERT_THAT(text.next(v, p), Eq(true)); //should be Ben, 1
    ASSERT_THAT(p, Eq(1))<< "first p =\"" << p << "\"";
    ASSERT_THAT(v, StrEq("Ben"));

    ASSERT_THAT(text.next(v, p), Eq(true)); //should be Jen, 2
    ASSERT_THAT(p, Eq(2))<< "second p =\"" << p << "\"";
    ASSERT_THAT(v, StrEq("Jen"));
    // ASSERT_THAT()

    ASSERT_THAT(text.next(v, p), Eq(true)); //should be Sven, 2 
    ASSERT_THAT(p, Eq(2))<< "third p =\"" << p << "\"";
    ASSERT_THAT(v, StrEq("Sven"));

    ASSERT_THAT(text.next(v, p), Eq(true)); //should be Gwen, 3 
    ASSERT_THAT(p, Eq(3))<< "forth p =\"" << p << "\""; //issue from returning to the parent node?
    ASSERT_THAT(v, StrEq("Gwen"));

    ASSERT_THAT(text.next(v, p), Eq(false)); //should be nullptr

    

}
TEST(PRQueueIterator, nextNodeOrder){
    prqueue<string> test;
    string v = "";
    int p = 0;

    test.begin();
    test.enqueue("Gwen", 3);
    test.begin();
    ASSERT_THAT(test.next(v, p), Eq(true)); //should be Gwen, 3
    ASSERT_THAT(p, Eq(3))<< "forth p =\"" << p << "\""; 
    ASSERT_THAT(v, StrEq("Gwen"));

    ASSERT_THAT(test.next(v, p), Eq(false)); //should be nullptr
    ASSERT_THAT(p, Eq(3)); //here- do I need to reset it??
    ASSERT_THAT(v, StrEq("Gwen"));

    test.enqueue("Tori", 3);
    test.begin();
    ASSERT_THAT(test.next(v, p), Eq(true)); //should be Gwen, 3
    ASSERT_THAT(p, Eq(3))<< "forth p =\"" << p << "\""; //issue from returning to the parent node?
    ASSERT_THAT(v, StrEq("Gwen"));

    ASSERT_THAT(test.next(v, p), Eq(true)); //should be Tori, 3
    ASSERT_THAT(p, Eq(3))<< "forth p =\"" << p << "\""; //issue from returning to the parent node?
    ASSERT_THAT(v, StrEq("Tori"));

    ASSERT_THAT(test.next(v, p), Eq(false)); //should be nullptr
    ASSERT_THAT(p, Eq(3));
    ASSERT_THAT(v, StrEq("Tori"));

    prqueue<string> t;

    t.enqueue("a", 12);
    t.enqueue("b", 6);
    t.enqueue("c", 1);
    t.enqueue("d", 13);
    t.enqueue("e", 2);
    t.enqueue("f", 6);
    t.enqueue("g", 6);
    t.enqueue("h", 12);
    t.enqueue("i", 8);
    t.enqueue("j", 7);
    t.enqueue("l", 9);

    t.begin();
    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(1));
    ASSERT_THAT(v, StrEq("c"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(2));
    ASSERT_THAT(v, StrEq("e"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(6));
    ASSERT_THAT(v, StrEq("b"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(6));
    ASSERT_THAT(v, StrEq("f"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(6));
    ASSERT_THAT(v, StrEq("g"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(7));
    ASSERT_THAT(v, StrEq("j"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(8));
    ASSERT_THAT(v, StrEq("i"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(9));
    ASSERT_THAT(v, StrEq("l"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(12));
    ASSERT_THAT(v, StrEq("a"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(12));
    ASSERT_THAT(v, StrEq("h"));

    ASSERT_THAT(t.next(v,p), Eq(true));
    ASSERT_THAT(p, Eq(13));
    ASSERT_THAT(v, StrEq("d"));

    ASSERT_THAT(t.next(v,p), Eq(false));

}
////////////ITERATOR TESTS////////////

