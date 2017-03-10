#pragma once

struct fixed_arena_controller
{
    template <int N>
    fixed_arena_controller(char(&a)[N]);
    fixed_arena_controller(fixed_arena_controller&) = delete;
    ~fixed_arena_controller() = default;
    void operator=(fixed_arena_controller&) = delete;

    void*  allocate(size_t);
    size_t block_size() const;
    size_t capacity() const;
    void   clear();
    bool   empty() const;

private:
    void*  arena_;
    size_t arena_size_;
    size_t block_size_;
};

template <int N>
inline fixed_arena_controller::fixed_arena_controller(char (&a)[N]) :
    arena_(a), arena_size_(N), block_size_(0)
{
	/*empty*/
}

inline void* fixed_arena_controller::allocate(size_t size)
{
    if (!empty())
        return nullptr;    // arena already allocated

    block_size_ = size + sizeof(void*);
    size_t count = capacity();

    if (count == 0)
        return nullptr;    // arena not big enough for even one item

    char* p = (char*)arena_;
    for ( size_t i = 1 ; i < count; ++i, p += block_size_)
    {
        *reinterpret_cast<char**>(p) = p + block_size_;
    }
    *reinterpret_cast<char**>(p) = nullptr;
    return arena_;
}

inline size_t fixed_arena_controller::block_size() const
{
    return block_size_;
}

inline size_t fixed_arena_controller::capacity() const
{
    return block_size_ ? (arena_size_ / block_size_) : 0;
}

inline void fixed_arena_controller::clear()
{
    block_size_ = 0;
}

inline bool fixed_arena_controller::empty() const
{
    return block_size_ == 0;
}
