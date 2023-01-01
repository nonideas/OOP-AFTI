#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

class indices final
{
	uint32_t free_head_index_;
	uint32_t num_block_;
	std::vector<uint32_t> free_indices_;
public:
	indices() : free_head_index_(0), num_block_(0) {}
	explicit indices(const uint32_t num_block)
	: free_head_index_(0), num_block_(num_block) {
		free_indices_.resize(num_block);
		reset_indices();
	}
	indices(indices&& indices) noexcept = default;
	indices(const indices& indices) noexcept = default;

	indices& operator=(const indices& indices) noexcept = default;
	indices& operator=(indices&& indices) noexcept = default;

	~indices() = default;

	uint32_t reserve_index() {
		const uint32_t index = free_head_index_;
		if (index == num_block_) {
			throw std::out_of_range("pool is full of objects");
		}
		free_head_index_ = free_indices_[index];
		free_indices_[index] = index;
		return index;
	}
	void release_index(const uint32_t index) {
		if (index >= num_block_) {
			throw std::out_of_range("pool is full of objects");
		}
		if (free_indices_[index] != index) {
			throw std::exception("no object at this ref");
		}
		free_indices_[index] = free_head_index_;
		free_head_index_ = index;
	}
	void reset_indices() {
		free_head_index_ = 0;
		for (uint32_t i = 0; i < num_block_; ++i) {
			free_indices_[i] = i + 1;
		}
	}
	[[nodiscard]] bool is_used_index(const uint32_t index) const {
		if (index >= num_block_) {
			throw std::out_of_range("pool is full of objects");
		}
		return free_indices_[index] == index;
	}
	[[nodiscard]] uint32_t get_num_block() const noexcept {
		return num_block_;
	}
	[[nodiscard]] uint32_t get_free_indices(const uint32_t index) const noexcept {
		return free_indices_[index];
	}
	[[nodiscard]] const std::vector<uint32_t>& get_free_indices() const noexcept {
		return free_indices_;
	}
};