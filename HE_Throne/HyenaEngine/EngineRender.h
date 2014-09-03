#pragma once

#include <forward_list>
#include <string>

namespace HE
{
	namespace HyenaEngine
	{
		class CEngineRender;

		using EngineRender = CEngineRender;
		using ArgsList = std::forward_list < const std::string > ;

		class CEngineRender
		{
		public:
			void Initialize(ArgsList& listArgs);
			void OnUpdate();
		};
	}
}

