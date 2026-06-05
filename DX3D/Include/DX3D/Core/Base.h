#pragma once

//public api for users
//grouping common base classes, such as non-copyable, non-movable, etc into this namespace, so that users can easily inherit from them when needed
namespace dx3d
{
	class Base
	{
	public:
		//constructor and destructor

		Base(); // called when created
		virtual ~Base(); // called when destroyed

	};

} 
