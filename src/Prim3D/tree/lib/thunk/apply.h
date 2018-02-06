#ifndef apply_INCLUDED
#define apply_INCLUDED

#include <thunk/Void.h>

#include <set.h>

Void apply(const set< Thunk0<Void> >& thunks) {

  for(set< Thunk0<Void> >::const_iterator i = thunks.begin();
      i!=thunks.end();
      ++i) {

    (*i)();
  }

  return nothing;
}


template <class A1>
Void apply(const set< Thunk1<A1, Void> >& thunks, const A1& a1) {

  for(set< Thunk1<A1, Void> >::const_iterator i = thunks.begin();
      i!=thunks.end();
      ++i) {

    (*i)(a1);
  }

  return nothing;
}



template <class A1, class A2>
Void apply(const set< Thunk2<A1, A2, Void> >& thunks, 
	   const A1& a1, const A2& a2) {

  for(set< Thunk2<A1, A2, Void> >::const_iterator i = thunks.begin();
      i!=thunks.end();
      ++i) {

    (*i)(a1, a2);
  }

  return nothing;
}

  
#endif
