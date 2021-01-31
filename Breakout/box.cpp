#include "box.h"


Box::Box() {
	m_is_delete = false;
	m_is_inner = false;
}

void Box::Delete() {
	m_is_delete = true;
}

void Box::OnContact() {}
