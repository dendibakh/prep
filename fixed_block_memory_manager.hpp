#pragma once

template <class Arena>
struct fixed_block_memory_manager
{
    template <int N>
    fixed_block_memory_manager(char(&a)[N]);

    fixed_block_memory_manager(fixed_block_memory_manager&) = delete;
    ~fixed_block_memory_manager() = default;
    void operator=(fixed_block_memory_manager&) = delete;

    void*  allocate(size_t);
    size_t block_size() const { return block_size_; };
    size_t capacity() const;
    void   clear();
    void   deallocate(void*);
    bool   empty() const { return block_size_ == 0; };

private:
    struct free_block
	{
        free_block* next;
    };
    free_block* free_ptr_;
    size_t      block_size_;
    Arena       arena_;
};

template <class Arena>
template <int N>
inline fixed_block_memory_manager<Arena>::fixed_block_memory_manager(char(&a)[N]) :
	free_ptr_(nullptr), block_size_(0), arena_(a)
{
	/* empty */
}

template <class Arena>
inline void* fixed_block_memory_manager<Arena>::allocate(size_t size)
{
    if (empty())
    {
        free_ptr_ = reinterpret_cast<free_block*>(arena_.allocate(size));
        block_size_ = size;
        if (empty())
            throw std::bad_alloc();
    }
    if (size != block_size_)
        throw std::bad_alloc();
    auto p = (char*)free_ptr_ + sizeof(void*);
    free_ptr_ = free_ptr_->next;
    return p;
}

template <class Arena>
inline void fixed_block_memory_manager<Arena>::deallocate(void* p)
{
    if (p == nullptr)
        return;
    auto fp = reinterpret_cast<free_block*>((char*)p - sizeof(void*));
    fp->next = free_ptr_;
    free_ptr_ = fp;
}

template <class Arena>
inline size_t fixed_block_memory_manager<Arena>::capacity() const
{
    return arena_.capacity();
}

template <class Arena>
inline void fixed_block_memory_manager<Arena>::clear()
{
    free_ptr_ = nullptr;
    arena_.clear();
}
