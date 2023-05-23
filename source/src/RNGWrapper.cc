#include "RNGWrapper.hh"
#include "Randomize.hh"

template CLHEP::HepRandomEngine* RNGWrapper<CLHEP::HepRandomEngine>::m_obj;

template double (CLHEP::HepRandomEngine::*RNGWrapper<CLHEP::HepRandomEngine>::m_func)(void);

/*
In RNGWrapper.cc, the RNGWrapper class is explicitly instantiated
for CLHEP::HepRandomEngine (a RNG provided by the CLHEP library).

With this wrapper, you can easily change the RNG without
 modifying the code that uses it, simply by providing
a different RNG object and method to the set function.

Note: In C++ template definitions must be in the header file,
otherwise you will get linker errors. The definitions for static
member variables are in the header file in this case.
*/
