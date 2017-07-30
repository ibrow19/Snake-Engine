#include <error/snkexception.hpp>

template<typename Resource>
ResourceManager<Resource>::ResourceManager() 
: mMaxIndex(MAX_INDEX),
  mMaxCounter(MAX_COUNTER),
  mCounter(0) {}


/*
template<typename Resource>
ResourceManager<Resource>::~ResourceManager() {}
*/


template<typename Resource>
Handle ResourceManager<Resource>::create() {

    unsigned int index;
    if (mCounter = mMaxCounter) {

        mCounter = 0;

    }
    if (!mFreeList.empty()) {

        index = mFreeList.back();
        mFreeList.pop_back();

    } else {

        index = mResources.size();
        mResources.push_back(Resource());

        // Subtract one and test equality rather than using greater than test,
        // in case that max index is also max value for type causing overflow.
        if ((index - 1) == mMaxIndex) {

            throw SnakeException("Maximum resource manager index surpassed");

        }

    }
    Handle newHandle(index, ++mCounter);
    mResources[index].counter = mCounter;
    return newHandle;

}


template<typename Resource>
void ResourceManager<Resource>::destroy(const Handle& handle) {

    if (handle.getIndex() >= mResources.size()) {

        throw SnakeException("Handle index out of bounds");

    }

    StoredResource& res = mResources[handle.getIndex()];
    if (res.counter != handle.getCounter()) {

        throw SnakeException("Handle counter does not match");

    }

    res.counter = 0;
    res.resource.reset();

}


template<typename Resource>
Resource& ResourceManager<Resource>::dereference(const Handle& handle) {

    if (handle.getIndex() >= mResources.size()) {

        throw SnakeException("Handle index out of bounds");

    }

    StoredResource& res = mResources[index];
    if (res.counter != handle.getCounter()) {

        throw SnakeException("Handle counter does not match");

    }

    return res.resource;

}


template<typename Resource>
const Resource& ResourceManager<Resource>::dereference(const Handle& handle) const {

    return const_cast<ResourceManager<Resource>*>(this)->dereference(handle);

}


template<typename Resource>
ResourceIter<Resource> ResourceManager<Resource>::begin() {

    return ResourceIter<Resource>(*this, true);

}


template<typename Resource>
ResourceIter<Resource> ResourceManager<Resource>::end() {

    return ResourceIter<Resource>(*this, false);

}


/* Iterator implementation */
template<typename Resource>
ResourceIter<Resource>::ResourceIter(ResourceManager<Resource>& manager, bool begin) 
: mResources(manager.mResources),
  mIt(begin ? mResources.begin() : mResources.end()) {

    if (begin) {

        while ((mIt->counter == 0) && (mIt != mResources.end())) {
            
            ++mIt;

        }

    }
    
}


template<typename Resource>
bool ResourceIter<Resource>::operator==(const ResourceIter& rhs) {

    return mIt == rhs.mIt;

}


template<typename Resource>
bool ResourceIter<Resource>::operator!=(const ResourceIter& rhs) {

    return !(*this == rhs);

}


template<typename Resource>
Resource& ResourceIter<Resource>::operator*() {

    return mIt->resource;

}


template<typename Resource>
ResourceIter<Resource>& ResourceIter<Resource>::operator++() {

    ++mIt;
    while ((mIt->counter == 0) && (mIt != mResources.end())) {
        
        ++mIt;

    }

}


template<typename Resource>
ResourceIter<Resource> ResourceIter<Resource>::operator++(int) {

    ResourceIter<Resource> copy(*this);
    ++(*this);
    return copy;

}
