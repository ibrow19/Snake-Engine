#ifndef SNAKE_RESOURCE_MANAGER_HEADER
#define SNAKE_RESOURCE_MANAGER_HEADER

#include <iterator>
#include <error/snkexception.hpp>
#include <handle.hpp>

namespace snk {

template<typename Resource, typename Pointer, typename Reference>
class ResourceIter;

// Note: resources used with manager must have default constructor.
template<typename Resource>
class ResourceManager {
public:

    // Standard container typedefs.
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef Resource value_type;
    typedef Resource* pointer;
    typedef Resource& reference;
    typedef const Resource* const_pointer;
    typedef const Resource& const_reference;
    typedef ResourceIter<Resource, pointer, reference> iterator;
    typedef ResourceIter<Resource, const_pointer, const_reference> const_iterator;

public:

    // Make iterator friend so that it can access resources.
    friend iterator;
    friend const_iterator;

public:

    ResourceManager();

    Handle create();
    void destroy(const Handle& handle);

    Resource& dereference(const Handle& handle);
    const Resource& dereference(const Handle& handle) const;

    iterator begin();
    iterator end();
    const_iterator cbegin();
    const_iterator cend();
    
private:

    struct StoredResource {

        unsigned int counter = 0;
        Resource resource;
        
    };

private:

    unsigned int mMaxIndex;
    unsigned int mMaxCounter;

    unsigned int mCounter;

    std::vector<unsigned int> mFreeList;
    std::vector<StoredResource> mResources;

};

/// Iterator for ResourceManager.
template<typename Resource, typename Pointer, typename Reference>
class ResourceIter : public std::iterator<std::forward_iterator_tag,
                                          typename ResourceManager<Resource>::value_type,
                                          typename ResourceManager<Resource>::difference_type,
                                          Pointer,
                                          Reference> {
private:

    typedef std::iterator<std::forward_iterator_tag,
                          typename ResourceManager<Resource>::value_type,
                          typename ResourceManager<Resource>::difference_type,
                          Pointer,
                          Reference> base;
    typedef typename base::pointer pointer;
    typedef typename base::reference reference;

public:

    ResourceIter(ResourceManager<Resource>& manager, bool begin);
    
    bool operator==(const ResourceIter& rhs) const;
    bool operator!=(const ResourceIter& rhs) const;
    reference operator*();
    pointer operator->();
    ResourceIter<Resource, Pointer, Reference>& operator++();
    ResourceIter<Resource, Pointer, Reference> operator++(int);

private:

    typedef typename ResourceManager<Resource>::StoredResource Stored;

private:

    std::vector<Stored>& mResources;
    typename std::vector<Stored>::iterator mIt;

};

#include <resourcemanager.inl>

} // namespace snk

#endif
