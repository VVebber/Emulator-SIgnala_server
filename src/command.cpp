#include "command.h"

Command::Command(QString command) : m_command(command)
{
  m_variableData = "";
}

bool Command::isCommand(QString str)
{
  return m_command == str;
}

void Command::setVariableData(QString str)
{
  m_variableData = str;
}

QString Command::getVariableData()
{
  return m_variableData;
}
