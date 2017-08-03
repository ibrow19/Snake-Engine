template<typename Resource, typename Tag>
ResourceManager<Resource, Tag>::ResourceManager() 
: mMaxIndex(MAX_INDEX),
  mMaxCounter(MAX_COUNTER),
  mCounter(0) {}


template<typename Resource, typename Tag>
typename ResourceManager<Resource, Tag>::ResHandle ResourceManager<Resource, Tag>::create() {

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
    ResHandle newHandle(index, ++mCounter);
    mResources[index].counter = mCounter;
    return newHandle;

}


template<typename Resource, typename Tag>
void ResourceManager<Resource, Tag>::destroy(const ResHandle& handle) {

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


template<typename Resource, typename Tag>
Resource& ResourceManager<Resource, Tag>::dereference(const ResHandle& handle) {

    if (handle.getIndex() >= mResources.size()) {

        throw SnakeException("Handle index out of bounds");

    }

    StoredResource& res = mResources[handle.getIndex()];
    if (res.counter != handle.getCounter()) {

        throw SnakeException("Handle counter does not match");

    }

    return res.resource;

}


template<typename Resource, typename Tag>
const Resource& ResourceManager<Resource, Tag>::dereference(const ResHandle& handle) const {

    return const_cast<ResourceManager<Resource, Tag>*>(this)->dereference(handle);

}


template<typename Resource, typename Tag>
typename ResourceManager<Resource, Tag>::iterator ResourceManager<Resource, Tag>::begin() {

    return iterator(*this, true);

}


template<typename Resource, typename Tag>
typename ResourceManager<Resource, Tag>::iterator ResourceManager<Resource, Tag>::end() {

    return iterator(*this, false);

}


template<typename Resource, typename Tag>
typename ResourceManager<Resource, Tag>::const_iterator ResourceManager<Resource, Tag>::cbegin() {

    return const_iterator(*this, true);

}


template<typename Resource, typename Tag>
typename ResourceManager<Resource, Tag>::const_iterator ResourceManager<Resource, Tag>::cend() {

    return const_iterator(*this, false);

}


/* Iterator implementation */
template<typename Resource, typename Tag, typename Pointer, typename Reference>
ResourceIter<Resource, Tag, Pointer, Reference>::ResourceIter(ResourceManager<Resource, Tag>& manager, bool begin) 
: mResources(manager.mResources),
  mIt(begin ? mResources.begin() : mResources.end()) {

    if (begin) {

        while ((mIt != mResources.end()) && (mIt->counter == 0) ) {
            
            ++mIt;

        }

    }
    
}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
bool ResourceIter<Resource, Tag, Pointer, Reference>::operator==(const ResourceIter& rhs) const {

    return mIt == rhs.mIt;

}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
bool ResourceIter<Resource, Tag, Pointer, Reference>::operator!=(const ResourceIter& rhs) const {

    return !(*this == rhs);

}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
typename ResourceIter<Resource, Tag, Pointer, Reference>::reference
ResourceIter<Resource, Tag, Pointer, Reference>::operator*() {

    return mIt->resource;

}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
typename ResourceIter<Resource, Tag, Pointer, Reference>::pointer
ResourceIter<Resource, Tag, Pointer, Reference>::operator->() {

    return &(mIt->resource);

}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
ResourceIter<Resource, Tag, Pointer, Reference>& 
ResourceIter<Resource, Tag, Pointer, Reference>::operator++() {

    ++mIt;
    while ((mIt != mResources.end()) && (mIt->counter == 0)) {
        
        ++mIt;

    }
    return *this;

}


template<typename Resource, typename Tag, typename Pointer, typename Reference>
ResourceIter<Resource, Tag, Pointer, Reference> 
ResourceIter<Resource, Tag, Pointer, Reference>::operator++(int) {

    ResourceIter<Resource, Tag, Pointer, Reference> copy(*this);
    ++(*this);
    return copy;

}
