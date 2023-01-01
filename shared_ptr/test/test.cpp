#include "gtest/gtest.h"
#include "../src/shared_ptr.h"

class MemoryLeakDetector {
public:
	MemoryLeakDetector() {
		_CrtMemCheckpoint(&memState_);
	}

	~MemoryLeakDetector() {
		_CrtMemState stateNow, stateDiff;
		_CrtMemCheckpoint(&stateNow);
		int diffResult = _CrtMemDifference(&stateDiff, &memState_, &stateNow);
		if (diffResult)
			reportFailure(stateDiff.lSizes[1]);
	}
private:
	void reportFailure(unsigned int unfreedBytes) {
		FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
	}
	_CrtMemState memState_;
};

class A
{
	int a;
	int* memory;
public:
	A(int i = 0) : a(i) {
		memory = new int(4);
	}
	int get_a() const { return a; }
	~A() {
		delete(memory);
	}
};

TEST(shares_ptr, empty_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p;
	EXPECT_EQ(p.get_count(), 0);
	EXPECT_EQ(p.get(), nullptr);
}

TEST(shares_ptr, one_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p(new A(111));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ((*p).get_a(), 111);
}

TEST(shares_ptr, two_defferent_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p1(new A(111));
	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);

	shared_ptr<A> p2(new A(222));
	EXPECT_EQ(p2.get_count(), 1);
	EXPECT_NE(p2.get(), nullptr);
	EXPECT_EQ(p2->get_a(), 222);
}

TEST(shares_ptr, two_same_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p1(new A(111));
	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);

	shared_ptr p2 = p1;
	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_NE(p2.get(), nullptr);
	EXPECT_EQ(p2->get_a(), 111);

	EXPECT_EQ(p1.get_count(), 2);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);
}

TEST(shares_ptr, ptr_assignment) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p1(new A(111));
	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);

	shared_ptr<A> p2(new A(111));
	p2 = p1;
	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_NE(p2.get(), nullptr);
	EXPECT_EQ(p2->get_a(), 111);

	EXPECT_EQ(p1.get_count(), 2);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);
}

TEST(shares_ptr, reset_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p(new A(111));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ(p->get_a(), 111);

	p.reset();
	EXPECT_EQ(p.get_count(), 0);
	EXPECT_FALSE(p);

	p.reset(new A(222));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ(p->get_a(), 222);

	p.reset(new A(333));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ(p->get_a(), 333);
}

TEST(shares_ptr, reset_many_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p(new A(111));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ(p->get_a(), 111);

	shared_ptr p2(p);
	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 111);

	p.reset();
	EXPECT_EQ(p.get_count(), 0);
	EXPECT_FALSE(p);
	
	EXPECT_EQ(p2.get_count(), 1);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 111);
}

TEST(shares_ptr, swap_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p1(new A(111));
	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_TRUE(p1);
	EXPECT_EQ(p1->get_a(), 111);

	shared_ptr<A> p2(new A(222));
	EXPECT_EQ(p2.get_count(), 1);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 222);

	shared_ptr p3(p1);
	EXPECT_EQ(p3.get_count(), 2);
	EXPECT_TRUE(p3);
	EXPECT_EQ(p3->get_a(), 111);

	p1.swap(p2);

	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_TRUE(p1);
	EXPECT_EQ(p1->get_a(), 222);

	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 111);
}

TEST(shares_ptr, release_ptr) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p(new A(111));
	EXPECT_EQ(p.get_count(), 1);
	EXPECT_TRUE(p);
	EXPECT_EQ(p->get_a(), 111);

	shared_ptr p2(p);
	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 111);

	p.release();
	EXPECT_EQ(p.get_count(), 0);
	EXPECT_FALSE(p);

	EXPECT_EQ(p2.get_count(), 1);
	EXPECT_TRUE(p2);
	EXPECT_EQ(p2->get_a(), 111);
}

TEST(shares_ptr, container) {
	MemoryLeakDetector leakDetector;
	A* a = new A[10];
	shared_ptr<A[]> p1(a);
}

TEST(shares_ptr, not_default_constructible_Deleter) {
	MemoryLeakDetector leakDetector;
	shared_ptr<A> p1(new A(111));
	EXPECT_EQ(p1.get_count(), 1);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);

	shared_ptr p2 = p1;
	EXPECT_EQ(p2.get_count(), 2);
	EXPECT_NE(p2.get(), nullptr);
	EXPECT_EQ(p2->get_a(), 111);

	EXPECT_EQ(p1.get_count(), 2);
	EXPECT_NE(p1.get(), nullptr);
	EXPECT_EQ(p1->get_a(), 111);
}
