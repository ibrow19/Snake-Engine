# This module defines:
#  RAPIDXML_INCLUDE_DIR - the rapidxml include directory.

set(RAPIDXML_PATHS /usr/local/ /usr/)

find_path(RAPIDXML_INCLUDE_DIR rapidxml.hpp 
          PATH_SUFFIXES rapidxml 
          PATHS RAPIDXML_PATHS)

if (NOT RAPIDXML_INCLUDE_DIR)
    message(FATAL_ERROR "Failed to find RapidXML!")
endif (NOT RAPIDXML_INCLUDE_DIR)
