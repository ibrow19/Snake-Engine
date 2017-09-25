#ifndef SNAKE_RESOURCE_MANAGER_HEADER
#define SNAKE_RESOURCE_MANAGER_HEADER

#include <iterator>
#include <vector>
#include <cstddef>
#include <snk/error/snkexception.hpp>
#include <snk/resource/handle.hpp>

namespace snk {

template<typename Resource, typename Tag, typename Pointer, typename Reference>
class ResourceIter;

template<typename Resource, typename Tag>
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
    typedef ResourceIter<Resource, Tag, pointer, reference> iterator;
    typedef ResourceIter<Resource, Tag, const_pointer, const_reference> const_iterator;
    
    typedef Handle<Tag> ResHandle;

public:

    // Make iterator friend so that it can access resources.
    friend iterator;
    friend const_iterator;

public:

    ResourceManager();

    /// Create a new resource, setting handle. Note, any other calls to resourcemanager
    /// functions (primarily creation and destruction) may invalidate the reference.
    /// \param handle resource handle to be initilised.
    /// \return the created resource to carry out additional initialisation.
    Resource& create(ResHandle& handle);

    // TODO: should this throw an exception if the handle is invalid or not?
    void destroy(const ResHandle& handle);

    Resource& dereference(const ResHandle& handle);
    const Resource& dereference(const ResHandle& handle) const;

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
template<typename Resource, typename Tag, typename Pointer, typename Reference>
class ResourceIter : public std::iterator<std::forward_iterator_tag,
                                          typename ResourceManager<Resource, Tag>::value_type,
                                          typename ResourceManager<Resource, Tag>::difference_type,
                                          Pointer,
                                          Reference> {
private:

    typedef std::iterator<std::forward_iterator_tag,
                          typename ResourceManager<Resource, Tag>::value_type,
                          typename ResourceManager<Resource, Tag>::difference_type,
                          Pointer,
                          Reference> base;
    typedef typename base::pointer pointer;
    typedef typename base::reference reference;

public:

    ResourceIter(ResourceManager<Resource, Tag>& manager, bool begin);
    
    bool operator==(const ResourceIter& rhs) const;
    bool operator!=(const ResourceIter& rhs) const;
    reference operator*();
    pointer operator->();
    ResourceIter<Resource, Tag, Pointer, Reference>& operator++();
    ResourceIter<Resource, Tag, Pointer, Reference> operator++(int);

private:

    typedef typename ResourceManager<Resource, Tag>::StoredResource Stored;

private:

    std::vector<Stored>& mResources;
    typename std::vector<Stored>::iterator mIt;

};

#include <snk/resource/resourcemanager.inl>

} // namespace snk

#endif
