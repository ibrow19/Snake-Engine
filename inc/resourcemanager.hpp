#ifndef SNAKE_RESOURCE_MANAGER_HEADER
#define SNAKE_RESOURCE_MANAGER_HEADER

#include <handle.hpp>

namespace snk {

template<typename Resource>
class ResourceIter;

// TODO: custom iterator over resources.
// Note: resources used with manager must have default constructor.
template<typename Resource>
class ResourceManager {
public:

    // Make iterator friend so that it can access resources.
    friend class ResourceIter<Resource>;

public:

    // Standard container typedefs.
    typedef ResourceIter<Resource> iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef Resource value_type;
    typedef Resource* pointer;
    typedef Resource& reference;

public:

    ResourceManager();
    // virtual ~ResourceManager();

    Handle create();
    void destroy(const Handle& handle);

    Resource& dereference(const Handle& handle);
    const Resource& dereference(const Handle& handle) const;

    ResourceIter<Resource> begin();
    ResourceIter<Resource> end();
    
private:

    struct StoredResource {

        unsigned int counter;
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
template<typename Resource>
class ResourceIter {
public:

    ResourceIter(ResourceManager<Resource>& manager, bool begin);
    
    bool operator==(const ResourceIter& rhs);
    bool operator!=(const ResourceIter& rhs);
    Resource& operator*();
    ResourceIter<Resource>& operator++();
    ResourceIter<Resource> operator++(int);

    // TODO: ->, const iterator, reverse iterator, traits.

private:

    typedef typename ResourceManager<Resource>::StoredResource Stored;

private:

    std::vector<Stored>& mResources;
    typename std::vector<Stored>::iterator mIt;

};

#include <resourcemanager.inl>

} // namespace snk

#endif
