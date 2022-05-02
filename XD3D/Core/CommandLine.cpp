#include "stdafx.h"
#include "CommandLine.h"

static std::unordered_map<StringHash, std::string> m_Parameters;
static std::string m_CommandLine;

bool CommandLine::Parse(const char* pCommandLine)
{
	m_CommandLine = pCommandLine;
	m_Parameters.clear();
	bool quoted = false;

	int commandStart = 0;
	bool hasValue = false;
	std::string identifier;

	for (size_t i = 0; i < m_CommandLine.size(); i++)
	{
		if (m_CommandLine[i] == '\"')
		{
			quoted = !quoted;
		}
		else if (m_CommandLine[i] == '-' && !quoted)
		{
			commandStart = (int)i + 1;
		}
		else if (m_CommandLine[i] == '=' && !quoted)
		{
			identifier = m_CommandLine.substr(commandStart, i - commandStart);
			commandStart = (int)i + 1;
			hasValue = true;
		}
		else if (m_CommandLine[i] == ' ' && !quoted)
		{
			if (hasValue)
			{
				std::string value = m_CommandLine.substr(commandStart, i - commandStart);
				if (value.front() == '\"' && value.back() == '\"')
				{
					value = value.substr(1, value.length() - 2);
				}

				m_Parameters[StringHash(identifier)] = value;
				hasValue = false;
			}
			else
			{
				m_Parameters[StringHash(m_CommandLine.substr(commandStart, i - commandStart))] = "1";
			}
			commandStart = -1;
		}
	}

	if (commandStart > -1)
	{
		if (hasValue)
		{
			std::string value = m_CommandLine.substr(commandStart);
			if (value.front() == '\"' && value.back() == '\"')
			{
				value = value.substr(1, value.length() - 2);
			}

			m_Parameters[StringHash(identifier)] = value;
			hasValue = false;
		}
		else
		{
			m_Parameters[StringHash(m_CommandLine.substr(commandStart))] = "1";
		}
		commandStart = -1;
	}

	return true;
}

bool CommandLine::GetInt(const char* name, int& value, int defaultValue /*= 0*/)
{
	auto it = m_Parameters.find(name);
	if (it != m_Parameters.end())
	{
		for (char c : it->second)
		{
			if (!std::isdigit(c))
			{
				value = defaultValue;
				return false;
			}
		}
		value = std::stoi(it->second);
		return true;
	}
	value = defaultValue;
	return false;
}

bool CommandLine::GetBool(const char* parameter)
{
	return m_Parameters.find(parameter) != m_Parameters.end();
}

const std::string& CommandLine::Get()
{
	return m_CommandLine;
}
