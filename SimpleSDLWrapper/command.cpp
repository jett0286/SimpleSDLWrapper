#include <iostream>

#include "command.h"

void SSW_Command_Base::undo ()
{
	std::cout << "WARNING: Executing undefined undo\n";
	return;
}

void SSW_Command_Macro::addCommand (SSW_Command_Base* pCommand)
{
	vectorCommands_.push_back (pCommand);
}

void SSW_Command_Macro::execute ()
{
	for (SSW_Command_Base* pCommand : vectorCommands_)
	{
		pCommand->execute ();
	}
}

void SSW_Command_Quit::execute ()
{
	exit (EXIT_SUCCESS);
}