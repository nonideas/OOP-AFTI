#pragma once
#include <functional>

template <class Type, class TDeleter>
concept is_deleter = requires(Type* point, TDeleter del) {
    { del(point) } -> std::same_as<void>;
};

template<class Type, class TDeleter = std::default_delete<Type>>
    requires is_deleter<std::remove_extent_t<Type>, TDeleter>
class shared_ptr final {
    using type_data = std::remove_extent_t<Type>;
private:
    type_data* data_ = nullptr;
    uint32_t* count_ = nullptr;
    TDeleter deleter_;

public: // Constructors and destructor.
    shared_ptr() noexcept 
        requires (std::is_default_constructible_v<TDeleter>)
        : deleter_() {}
    explicit  shared_ptr(type_data* p_obj) noexcept 
        requires (std::is_default_constructible_v<TDeleter>) 
        : data_(p_obj), deleter_() {
        if (p_obj) {
            count_ = new uint32_t(1);
        }
    }
	explicit shared_ptr(TDeleter del) noexcept : deleter_(del) {}
    shared_ptr(type_data* p_obj, const TDeleter& del) noexcept 
        : data_(p_obj), deleter_(del) {
        if (p_obj) {
            count_ = new uint32_t(1);
        }
    }
    // Move constructor.
    shared_ptr(shared_ptr&& other_shared_ptr) noexcept
        : data_(other_shared_ptr.data_), count_(other_shared_ptr.count_) {
        other_shared_ptr.data_ = nullptr;
        other_shared_ptr.count_ = nullptr;
    }
    shared_ptr(const shared_ptr& other_shared_ptr) noexcept
        : data_(other_shared_ptr.data_), count_(other_shared_ptr.count_) {
        increment_count();
    }
    ~shared_ptr() {
        release();
    }
public: // Assignment.
    shared_ptr& operator=(shared_ptr&& other_shared_ptr) noexcept {
        if (this == &other_shared_ptr) {
            return *this;
        }
        release();
        swap(other_shared_ptr);
        return *this;
    }
    shared_ptr& operator=(type_data* p_object) {
        *this = shared_ptr(p_object);
        return *this;
    }
    shared_ptr& operator=(const shared_ptr& other_shared_ptr) noexcept {
        if (this == &other_shared_ptr) {
            return *this;
        }
        release();
        data_ = other_shared_ptr.data_;
        count_ = other_shared_ptr.count_;
        increment_count();
        return *this;
    }
public: // Observers.
     // Dereference the stored pointer.
    type_data& operator*() const {
        return *data_;
    }
    // Return the stored pointer.
    type_data* operator->() const {
        return data_;
    }
    // Return the stored pointer.
    [[nodiscard]] type_data* get() const {
        return data_;
    }
    // Return count_
    [[nodiscard]] uint32_t get_count() const {
        return count_ ? *count_ : 0;
    }
    // Return a reference to the stored deleter_.
    TDeleter& get_deleter() {
        return deleter_;
    }
    // Return false if the stored pointer is null.
    explicit operator bool() const {
        return data_ != nullptr;
    }
public: // Modifiers.
    // Release ownership of any stored pointer.
    void release() {
        if (count_ != nullptr) {
            if (*count_ == 1) {
                deleter_(data_);
                delete count_;
            }
            else {
                --(*count_);
                count_ = nullptr;
                data_ = nullptr;
            }
        }
    }
    // Replace the stored pointer.
    void reset(type_data* p_object = nullptr) {
        release();
        data_ = p_object;
        if (data_) {
            count_ = new uint32_t(1);
        }
        else {
            count_ = nullptr;
        }
    }
    // Exchange the pointer with another object.
    void swap(shared_ptr& other_shared_ptr) noexcept {
        std::swap(data_, other_shared_ptr.data_);
        std::swap(count_, other_shared_ptr.count_);
    }

private:
    void increment_count() const {
        if (count_ != nullptr) {
            ++(*count_);
        }
    }
};