template<typename Resource>
ResourceManager<Resource>::ResourceManager() 
: mMaxIndex(MAX_INDEX),
  mMaxCounter(MAX_COUNTER),
  mCounter(0) {}


template<typename Resource>
Handle ResourceManager<Resource>::create() {

    unsigned int index;
    if (mCounter == mMaxCounter) {

        mCounter = 0;

    }
    if (!mFreeList.empty()) {

        index = mFreeList.back();
        mFreeList.pop_back();

    } else {

        index = mResources.size();
        mResources.push_back(StoredResource());

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

    StoredResource& res = mResources[handle.getIndex()];
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
typename ResourceManager<Resource>::iterator ResourceManager<Resource>::begin() {

    return iterator(*this, true);

}


template<typename Resource>
typename ResourceManager<Resource>::iterator ResourceManager<Resource>::end() {

    return iterator(*this, false);

}


template<typename Resource>
typename ResourceManager<Resource>::const_iterator ResourceManager<Resource>::cbegin() {

    return const_iterator(*this, true);

}


template<typename Resource>
typename ResourceManager<Resource>::const_iterator ResourceManager<Resource>::cend() {

    return const_iterator(*this, false);

}


/* Iterator implementation */
template<typename Resource, typename Pointer, typename Reference>
ResourceIter<Resource, Pointer, Reference>::ResourceIter(ResourceManager<Resource>& manager, bool begin) 
: mResources(manager.mResources),
  mIt(begin ? mResources.begin() : mResources.end()) {

    if (begin) {

        while ((mIt->counter == 0) && (mIt != mResources.end())) {
            
            ++mIt;

        }

    }
    
}


template<typename Resource, typename Pointer, typename Reference>
bool ResourceIter<Resource, Pointer, Reference>::operator==(const ResourceIter& rhs) {

    return mIt == rhs.mIt;

}


template<typename Resource, typename Pointer, typename Reference>
bool ResourceIter<Resource, Pointer, Reference>::operator!=(const ResourceIter& rhs) {

    return !(*this == rhs);

}


template<typename Resource, typename Pointer, typename Reference>
typename ResourceIter<Resource, Pointer, Reference>::reference ResourceIter<Resource, Pointer, Reference>::operator*() {

    return mIt->resource;

}


template<typename Resource, typename Pointer, typename Reference>
typename ResourceIter<Resource, Pointer, Reference>::pointer ResourceIter<Resource, Pointer,
Reference>::operator->() {

    return &(mIt->resource);

}


template<typename Resource, typename Pointer, typename Reference>
ResourceIter<Resource, Pointer, Reference>& ResourceIter<Resource, Pointer, Reference>::operator++() {

    ++mIt;
    while ((mIt->counter == 0) && (mIt != mResources.end())) {
        
        ++mIt;

    }

}


template<typename Resource, typename Pointer, typename Reference>
ResourceIter<Resource, Pointer, Reference> ResourceIter<Resource, Pointer, Reference>::operator++(int) {

    ResourceIter<Resource, Pointer, Reference> copy(*this);
    ++(*this);
    return copy;

}
