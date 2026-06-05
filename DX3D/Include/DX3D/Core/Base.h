#pragma once

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

		Base(); // called when created
		virtual ~Base(); // called when destroyed

	protected:
		// this is the rule off five, we delete the copy and move constructors and
		// assignment operators to prevent copying or moving of the object,
		// which can lead to bugs and undefined behavior if not handled properly.
		Base(const Base&) = delete; // copy constructor, deleted to prevent copying of the object 
		Base(Base&&) = delete; // move constructor, deleted to prevent moving of the object
		Base& operator=(const Base&) = delete; // copy assignment operator, deleted to prevent copying of the object
		Base& operator=(Base&&) = delete; // move assignment operator, deleted to prevent moving of the object 
	};
} 
