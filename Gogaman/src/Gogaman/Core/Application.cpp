#include "pch.h"
#include "Application.h"

#include "Logging/Log.h"
#include "Base.h"

#include "Config.h"
#include "Time.h"

#include "Gogaman/Input/Input.h"

#include "Gogaman/Events/EventManager.h"

#include "Gogaman/BoundingVolumeSystem.h"
#include "Gogaman/Rendering/ModelMatrixSystem.h"
#include "Gogaman/Rendering/RenderingSystem.h"

#include "Gogaman/Rendering/FlexShader/Token.h"
#include "Gogaman/Rendering/FlexShader/Lexer.h"

namespace Gogaman
{
	Application *Application::s_Instance = nullptr;

	Application::Application()
		: m_IsRunning(true)
	{
		GM_ASSERT(s_Instance == nullptr, "Failed to construct application | Instance already exists");
		s_Instance = this;

		GM_LOG_CORE_SET_LEVEL(Info);

		m_Window = std::make_unique<Window>("Gogaman", GM_CONFIG.screenWidth, GM_CONFIG.screenHeight, VerticalSynchronization::Disabled);

		m_World.AddSystem(std::make_unique<ModelMatrixSystem>());
		m_World.AddSystem(std::make_unique<BoundingVolumeSystem>());
		m_World.AddSystem(std::make_unique<RenderingSystem>());
		m_World.Initialize();
	}

	Application::~Application()
	{
		m_World.Shutdown();

		m_Window.reset();
		Window::Shutdown();
	}
	
	void Application::Run()
	{
		auto LoadShader = [](const char *filepath)
		{
			FILE *file = fopen(filepath, "rb");
			
			fseek(file, 0, SEEK_END);
			uint32_t size = ftell(file);
			rewind(file);

			char *buffer = new char[size + 1u];
			fread(buffer, size, 1, file);

			fclose(file);

			buffer[size] = '\0';

			std::string source = buffer;
			delete[] buffer;

			return source;
		};

		const std::string source = LoadShader("D:/dev/Gogaman/Gogaman/Shaders/test.txt");

		const auto tokens = FlexShader::Tokenize(source);

		const std::string names[]{
			"Number",
			"Identifier",
			"String",
			"Colon",
			"Semicolon",
			"LeftParenthesis",
			"RightParenthesis",
			"LeftSquareBracket",
			"RightSquareBracket",
			"LeftBrace",
			"RightBrace",
			"Equal",
			"Less",
			"Greater",
			"Plus",
			"Minus"
		};

		for(const FlexShader::Token i : tokens)
		{
			std::cout << names[(uint8_t)i.type] << ": " << i.lexeme << std::endl;
		}

		while(m_IsRunning)
		{
			Time::Update();
			Input::Update();

			m_World.Update();
			m_World.Render();
			
			m_Window->Update();

			EventManager::GetInstance().DispatchEvents();
		}
	}
}