#include "import.h"
#include "printutils.h"
#include "AST.h"
#include "boost-utils.h"

#ifdef ENABLE_CGAL
#include "CGAL_Nef_polyhedron.h"
#include "cgal.h"
#pragma push_macro("NDEBUG")
#undef NDEBUG
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#pragma pop_macro("NDEBUG")

CGAL_Nef_polyhedron *import_nef3(const std::string &filename, const Location &loc)
{
	CGAL_Nef_polyhedron *N = new CGAL_Nef_polyhedron;

	// Open file and position at the end
	std::ifstream f(filename.c_str(), std::ios::in | std::ios::binary);
	if (!f.good()) {
		LOG("",loc.firstLine(),getFormatted("Can't open import file '%1$s', import()",filename),message_group::Warning);
		return N;
	}
	
	std::string msg="";
	CGAL::Failure_behaviour old_behaviour = CGAL::set_error_behaviour(CGAL::THROW_EXCEPTION);
	try{
		N->p3.reset(new CGAL_Nef_polyhedron3);
		f >> *(N->p3);
	} catch (const CGAL::Failure_exception &e) {
		LOG("",loc.firstLine(),getFormatted("Failure trying to import '%1$s', import()",filename),message_group::Warning);
		LOG("",-1,e.what(),message_group::None);
		N = new CGAL_Nef_polyhedron;
	}
	CGAL::set_error_behaviour(old_behaviour);
	return N;
}
#endif
