#include "Item.h"

using namespace std ;

Item::Item(const string& name,
		   const string& desc,
		   Item::TYPE type) : m_name(name),
		   				      m_desc(desc) {
    m_type = type ;
}
