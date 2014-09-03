#pragma once

#include <forward_list>

namespace HE 
{
	namespace HyenaEngine
	{
		class CEngineCore;
		class CEngineProxy;

		using EngineCore = CEngineCore;
		using ArgsList = std::forward_list < const std::string >;

		class CEngineCore
		{
		private:
			CEngineCore();
			~CEngineCore();

		public:
			void Initialize(ArgsList& listArgs);
			void Start();

			static EngineCore& Instance();

		private:
			void Cleanup() HE_noexcept;

			

		private:
		};

		class EngineInitializeException : public std::exception
		{
		public:
			EngineInitializeException() {}
			explicit EngineInitializeException(const std::string& sMessage) HE_noexcept
				: m_sMessage(std::string{ sMessage })
			{ }
			explicit EngineInitializeException(std::string&& sMessage) HE_noexcept
				: m_sMessage(std::string{ sMessage })
			{ }

			virtual const char* what() const override HE_noexcept
			{
				return m_sMessage.c_str();
			}

		private:
			std::string m_sMessage;
		};

		class EngineRuntimeException : public std::exception
		{
		public:
			EngineRuntimeException() {}
			explicit EngineRuntimeException(const std::string& sMessage)
				: m_sMessage(std::string{ sMessage })
			{ }
			explicit EngineRuntimeException(std::string&& sMessage)
				: m_sMessage(std::string{ sMessage })
			{ }

			virtual const char* what() const override HE_noexcept
			{
				return m_sMessage.c_str();
			}

		private:
			std::string m_sMessage;
		};

	} 
}