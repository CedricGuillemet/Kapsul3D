#ifndef Ptr_INCLUDED
#define Ptr_INCLUDED

#pragma warning( disable : 4786 ) 

#include <set>
#include <map>

using std::map;
using std::set;
using std::pair;

#include <assert.h>

template <class T>
struct WeakPtr;

template <class T>
struct Ptr;


struct WeakPtrBase {

  virtual void invalidate() = 0;
};


struct PtrRefBase {

  PtrRefBase() : count(0) {}

  virtual ~PtrRefBase();

  inline void adopt(WeakPtrBase* ptr) {
    pair<WeakPtrs::iterator, bool> i = weak_ptrs.insert(ptr);
    assert(i.second);
  }


  inline void disown(WeakPtrBase* ptr) {
    int i = weak_ptrs.erase(ptr);
    assert(i);
  }

  typedef map<void*, PtrRefBase*> Refs;
  static Refs* refs;

 protected:

  int count;

 private:

  typedef set<WeakPtrBase*> WeakPtrs;
  WeakPtrs weak_ptrs;

 public:

  struct Init {
    Init() {
      if (count==0) {
	PtrRefBase::refs = new Refs;
      }
      ++count;
    }
    ~Init() {
      if (--count==0) {
	assert(refs);
	delete refs;
	refs = 0;
      }
    }
   private:
    static int count;
  };

};

static PtrRefBase::Init init;

template <class T>
struct PtrRef : PtrRefBase {

  PtrRef(T* p) : ptr(p) {}
  virtual ~PtrRef() {
    delete ptr; 
  }

 private:

  friend struct Ptr<T>;
  friend struct WeakPtr<T>;

  T* ptr;
};


template <class T>
struct Ptr {

  template <class U>
  Ptr(const Ptr<U>& that) {
    U* that_ptr = that;
    T* ptr = that_ptr;  // compiler checks that a U is a T
    setRef(ptr);
  }

  Ptr() : ref(0) {}
  Ptr(T* ptr) {
    setRef(ptr);
  }

  Ptr(const Ptr<T>& that) : ref(that.ref) {
    if (ref) ++ref->count;
  }

  template <class U>
  Ptr<T>& operator=(const Ptr<U>& that) {
    clearRef();
    U* that_ptr = that;
    T* ptr = that_ptr;  // compiler checks that a U is a T
    setRef(ptr);
    return *this;
  }

  Ptr<T>& operator=(const Ptr<T>& that) {
    if (that.ref) ++that.ref->count;
    clearRef();
    ref = that.ref;
    return *this;
  }

  Ptr<T>& operator=(T* ptr) {
    clearRef();
    setRef(ptr);
    return *this;
  }

  Ptr(const WeakPtr<T>&);

  ~Ptr() {
    clearRef();
  }


  friend bool operator==(const Ptr<T> & a, const Ptr<T> & b) {
    return a.ref == b.ref;
  }
  friend bool operator<(const Ptr<T> & a, const Ptr<T> & b) {
    return a.ref < b.ref;
  }

  operator T*() const {return ref?ref->ptr:0;}

  T* operator->() {assert(ref && ref->ptr); return ref->ptr;}
  const T* operator->() const {assert(ref && ref->ptr); return ref->ptr;}

 private:

  void clearRef() {
    if (ref && --ref->count==0) {
      PtrRefBase::Refs::iterator i = PtrRefBase::refs->find(ref->ptr);
      assert(i!=PtrRefBase::refs->end());
      delete (*i).second;
      PtrRefBase::refs->erase(i);
    }
  }

  void setRef(T* ptr) {
    if (ptr) {
      PtrRefBase::Refs::iterator f = 
	PtrRefBase::refs->lower_bound(ptr);
      if (f == PtrRefBase::refs->end() || (*f).first != ptr)
	f = PtrRefBase::refs->insert(f, 
				     pair<T*,PtrRef<T>*>(ptr, 
							 new PtrRef<T>(ptr)));
      ref = reinterpret_cast<PtrRef<T>*>((*f).second);
      ++ref->count;
    } else {
      ref = 0;
    }
  }

  friend struct WeakPtr<T>;
  
  PtrRef<T>* ref;
};


template <class T>
struct WeakPtr : WeakPtrBase {

  WeakPtr() : ref(0) {}
  WeakPtr(const WeakPtr<T>& that) 
    : ref(that.ref) {
      if (ref) {
	ref->adopt(this);
      }
  }

  WeakPtr(const Ptr<T>&);
  ~WeakPtr() {
    if (ref) ref->disown(this);
  }

  WeakPtr<T>& operator=(const WeakPtr<T>& that) {
    if (ref) ref->disown(this);
    ref = that.ref;
    if (ref) ref->adopt(this);
    return *this;
  }

  operator T*() {return ref?ref->ptr:0;}

  T* operator->() {assert(ref && ref->ptr); return ref->ptr;}

  virtual void invalidate() {ref = 0;}

 private:
  
  friend struct Ptr<T>;
  friend struct PtrRef<T>;

  PtrRef<T>* ref;
};


template <class T>
Ptr<T>::Ptr(const WeakPtr<T>& that) : ref(that.ref) {
  if (ref) ++ref->count;
}

template <class T>
WeakPtr<T>::WeakPtr(const Ptr<T>& that) : ref(that.ref) {
  if (     ref->adopt(this);
}

#endif
