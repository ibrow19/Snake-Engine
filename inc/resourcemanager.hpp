#ifndef SNAKE_RESOURCE_MANAGER_HEADER
#define SNAKE_RESOURCE_MANAGER_HEADER

#include <handle.hpp>

namespace snk {

// TODO: custom iterator over resources.
// Note: resources used with manager must have default constructor.
template<typename Resource>
class ResourceManager {
public:

    ResourceManager();
    virtual ~ResourceManager();

    Handle create();
    void destroy(const Handle& handle);

    Resource& dereference(const Handle& handle);
    const Resource& dereference(const Handle& handle) const;
    
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

#include <resourcemanager.inl>

} // namespace snk

#endif
