#pragma once
#include <ostream>
#include <concepts>

class Logger
{
public:

	/**
	 * @brief Creates a logger instance.
	 *
	 * Creates an instance of the base Logger or a derived logger specified by the template parameter.
	 * If an instance already exists, it will be destroyed before creating the new one.
	 *
	 * @tparam L The type of the logger to create (must be derived from Logger). Defaults to the base Logger.
	 * @tparam Args Variadic template for the arguments to pass to the logger's constructor.
	 * @param args Arguments forwarded to the constructor of the logger.
	 */
	template <std::derived_from<Logger> L = Logger, typename... Args>
		requires std::constructible_from<L, Args...>
	static void Create(Args&&... args)
	{
		Destroy();
		s_Instance = new L(std::forward<Args>(args)...);
	}

	/**
	 * @brief Access the active logger's output stream.
	 *
	 * @return A reference to the active logger's output stream.
	 */
	static std::ostream& Instance() { return s_Instance->m_Output; }

	/**
	 * @brief Destroys the active logger instance.
	 *
	 * This method safely deletes the current logger instance if it exists.
	 */
	static void Destroy();

public:

	Logger(std::ostream& output);
	virtual ~Logger() = default;

protected:

	static inline Logger* s_Instance = nullptr;
	std::ostream& m_Output;
};
