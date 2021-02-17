#pragma once
#ifndef ENUM
#define ENUM

	// This class is used to share the variable of an enum accross different classes without having to rewrite the enum definition.
namespace my_enums
{
	enum class Locations { SEARCH, LOCATION, DATE, HASHTAG, USER, DONALDTRUMP, BATHSPAUNIVERSITY };
}
#endif
