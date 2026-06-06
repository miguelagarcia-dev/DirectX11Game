#include <DX3D/Core/Base.h>
using namespace dx3d;

//not accessible for users, only for internal use

dx3d::Base::Base(const BaseDesc& desc): m_logger(desc.logger)
{
}

dx3d::Base::~Base()
{
}

Logger& dx3d::Base::getlogger() const noexcept
{
	return m_logger;
}
