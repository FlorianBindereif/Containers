#pragma once

class mynullptr_t
{
	public:
		template<class T> 
		operator T*() const
			{ return 0; }
		template<class C, class T>
			operator T C::*() const
			{ return 0; }
};

const mynullptr_t mynullptr;