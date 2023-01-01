#pragma once
#include "indices.h"
#include <numeric>

template <class TypeObject> class object_pool;



template <class TypeObject>
class object_pool final
{
	TypeObject* objects_;
	indices indices_;
public:
	explicit object_pool(const uint32_t num_block) : indices_(num_block) {
		objects_ = static_cast<TypeObject*>(operator new[](sizeof(TypeObject) * num_block));
	}
	object_pool(object_pool&& obj_pool) noexcept
		: objects_(obj_pool.objects_), indices_(std::move(obj_pool.indices_)) {
		obj_pool.objects_ = nullptr;
	}
	~object_pool() {
		destruct_all();
		operator delete[](objects_);
	}
	object_pool& operator=(object_pool&& obj_pool) noexcept {
		if (this == &obj_pool) {
			return *this;
		}
		destruct_all();
		operator delete[](objects_);
		objects_ = obj_pool.objects_;
		indices_ = std::move(obj_pool.indices_);
		obj_pool.objects_ = nullptr;
		return *this;
	}

	template <class... Params>
	TypeObject& alloc(Params&&... params) {
		const uint32_t index = indices_.reserve_index();
		new (objects_ + index) TypeObject(std::forward<Params>(params)...);
		return *(objects_ + index);
	}
	void free_element(TypeObject& ref_free) {
		TypeObject* ptr_free = &ref_free;
		if (ptr_free < objects_ || ptr_free >= (objects_ + indices_.get_num_block())) {
			throw std::out_of_range("ref_free is out of objects_ memory");
		}
		const auto index = static_cast<uint32_t>(ptr_free - objects_);
		indices_.release_index(index);
		ptr_free->~TypeObject();
	}
	void free_element(uint32_t index) {
		if (index >= indices_.get_num_block()) {
			throw std::out_of_range("index is out of objects_ pool");
		}
		indices_.release_index(index);
		TypeObject* ptr_free = objects_ + index;
		ptr_free->~TypeObject();
	}
	void free_all() {
		destruct_all();
		indices_.reset_indices();
	}
	object_pool(const object_pool&) = delete;
	object_pool& operator=(const object_pool&) = delete;
private:
	void destruct_all() {
		for (uint32_t index = 0; index < indices_.get_free_indices().size(); ++index) {
			if (indices_.is_used_index(index)) {
				free_element(index);
			}
		}
	}
};
