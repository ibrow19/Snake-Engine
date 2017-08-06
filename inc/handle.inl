template<typename Tag>
Handle<Tag>::Handle()
: mIndex(0),
  mCounter(0) {}


template<typename Tag>
Handle<Tag>::Handle(unsigned int index, unsigned int counter)
: mIndex(index),
  mCounter(counter) {}


template<typename Tag>
unsigned int Handle<Tag>::getIndex() const {

    return mIndex;

}


template<typename Tag>
unsigned int Handle<Tag>::getCounter() const {

    return mCounter;

}
