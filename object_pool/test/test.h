#pragma once
#include "../src/object_pool.h"

#include "gtest/gtest.h"

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

class Point {
	int m_x, m_y;
	int* ptr;
public:
	Point()
		: m_x(0), m_y(0) {
		ptr = (int*)std::malloc(10);
	}
	Point(int x, int y)
		: m_x(x), m_y(y) {
		ptr = (int*)std::malloc(10);
	}
	~Point() {
		std::free(ptr);
	}
};

TEST(point, createZeroObj) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);
}

TEST(point, createObj) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
}

TEST(point, freeRef) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);
	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	pp.free_element(p1);
}

TEST(point, freeNumber) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);
	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	pp.free_element(0);
}

TEST(point, freeAll) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	pp.free_all();
}

TEST(point, freeMiddle) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(10);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	Point& p3 = pp.alloc(1, 0);
	pp.free_element(p2);
	Point& p4 = pp.alloc(0, 1);
	EXPECT_TRUE(&p3 > &p4);
}

TEST(point, allocToFullPool) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	Point& p3 = pp.alloc(1, 0);
	EXPECT_THROW(pp.alloc(1, 0), std::out_of_range);
}

TEST(point, freeOfFullPool) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	Point& p3 = pp.alloc(1, 0);
	pp.free_element(p2);
	Point& p4 = pp.alloc(0, 1);
	EXPECT_TRUE(&p3 > &p4);
}

TEST(point, freeRefOutOfRange) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	Point& p_out = *(&p2 + 2);
	EXPECT_THROW(pp.free_element(p_out), std::out_of_range);
}

TEST(point, freeRefTwice) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	pp.free_element(p2);
	EXPECT_THROW(pp.free_element(p2), std::exception);
}

TEST(point, moveSemantics) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);

	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);
	object_pool pp_new1(std::move(pp));
	object_pool<Point> pp_new2 = std::move(pp_new1);

	object_pool<Point> pp2(0);
	object_pool<Point> pp2_new = std::move(pp2);
}

TEST(point, assignment_empty) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(0);

	object_pool pp_new = std::move(pp);
}

TEST(point, assignment_once) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);
	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);

	object_pool pp_new = std::move(pp);
}

TEST(point, assignment) {
	MemoryLeakDetector leakDetector;
	object_pool<Point> pp(3);
	Point& p1 = pp.alloc();
	Point& p2 = pp.alloc(0, 1);

	object_pool<Point> pp_new(3);
	Point& p_new1 = pp_new.alloc();
	Point& p_new2 = pp_new.alloc(0, 1);
	pp_new = std::move(pp);
}


//--------------------------------------------------//

TEST(indices, defoult_constructor) {
	indices indices;
	EXPECT_EQ(indices.get_num_block(), 0);
}

TEST(indices, constructor) {
	indices indices(3);
	EXPECT_EQ(indices.get_num_block(), 3);
	for (uint32_t i = 0; i < indices.get_num_block(); ++i) {
		EXPECT_EQ(indices.get_free_indices(i), i + 1);
	}
}

TEST(indices, reserve_index_out_of_range) {
	indices indices;
	EXPECT_THROW(indices.reserve_index(), std::out_of_range);
}

TEST(indices, reserve_index) {
	indices indices(3);
	indices.reserve_index();
	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(0), 0);
}

TEST(indices, reserve_all_indices) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();
	indices.reserve_index();
	EXPECT_EQ(indices.get_num_block(), 3);
	for (uint32_t i = 0; i < indices.get_num_block(); ++i) {
		EXPECT_EQ(indices.get_free_indices(i), i);
	}
}

TEST(indices, release_exception) {
	indices indices(3);
	EXPECT_THROW(indices.release_index(0), std::exception);
}

TEST(indices, release_first_index_in_full_container) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();
	indices.reserve_index();
	indices.release_index(0);
	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(0), 3);
}

TEST(indices, release_middle_index_in_full_container) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();
	indices.reserve_index();
	indices.release_index(1);
	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(1), 3);
}

TEST(indices, release_last_index_in_full_container) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();
	indices.reserve_index();
	indices.release_index(2);
	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(2), 3);
}

TEST(indices, release_first_index) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();
	indices.release_index(0);
	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(0), 2);
}

TEST(indices, assignment_empty) {
	indices i1;
	indices i2 = std::move(i1);
	EXPECT_EQ(i2.get_num_block(), 0);
}

TEST(indices, assignment) {
	indices i1(3);
	i1.reserve_index();
	i1.reserve_index();
	indices i2 = std::move(i1);
	EXPECT_EQ(i2.get_num_block(), 3);
	EXPECT_EQ(i2.get_free_indices(0), 0);
}

TEST(indices, move_ctor) {
	indices i1(3);
	i1.reserve_index();
	i1.reserve_index();
	indices i2(std::move(i1));
	EXPECT_EQ(i2.get_num_block(), 3);
	EXPECT_EQ(i2.get_free_indices(0), 0);
}

TEST(indices, reset_indices_empty) {
	indices indices;
	EXPECT_EQ(indices.get_num_block(), 0);

	indices.reset_indices();
	EXPECT_EQ(indices.get_num_block(), 0);
}

TEST(indices, reset_indices) {
	indices indices(3);
	indices.reserve_index();
	indices.reserve_index();

	indices.reset_indices();

	EXPECT_EQ(indices.get_num_block(), 3);
	EXPECT_EQ(indices.get_free_indices(0), 1);
	EXPECT_EQ(indices.get_free_indices(1), 2);
}