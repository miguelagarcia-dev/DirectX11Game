#pragma once
#include <DX3D/Core/Common.h>
//public api for users
// this is the base class for all classes in the dx3d engine, it provides common 
// functionality and interfaces for all classes, such as reference counting, logging, etc.
//grouping common base classes, such as non-copyable, non-movable, etc into this 
// namespace, so that users can easily inherit from them when needed

namespace dx3d
{
	class Base
	{
	public:
		//constructor and destructor

		explicit Base(const BaseDesc& desc); // called when created
		virtual ~Base(); // called when destroyed
		virtual Logger& getlogger() const noexcept final; //noexcept means to tell the compiler it doesnt throw excs
	protected:
		// this is the rule off five, we delete the copy and move constructors and
		// assignment operators to prevent copying or moving of the object,
		// which can lead to bugs and undefined behavior if not handled properly.
		Base(const Base&) = delete; // copy constructor, deleted to prevent copying of the object 
		Base(Base&&) = delete; // move constructor, deleted to prevent moving of the object
		Base& operator=(const Base&) = delete; // copy assignment operator, deleted to prevent copying of the object
		Base& operator=(Base&&) = delete; // move assignment operator, deleted to prevent moving of the object 

	//single tone, one instnace and global access, but hard to track dependaincies. 
	protected: 
		// this single tone means we need to provide external dependances through injection, we will use a specific
		// grouping type injection called aggreation, since its usally done one bu one 
		
		Logger& m_logger; 
	};
} 
