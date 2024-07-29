#include <iostream>

#include "command.h"

void SSW_Command::undo ()
{
	std::cout << "WARNING: Executing undefined undo\n";
	return;
}

void SSW_Macro::addCommand (SSW_Command* pCommand)
{
	vectorCommands_.push_back (pCommand);
}

void SSW_Macro::execute ()
{
	for (SSW_Command* pCommand : vectorCommands_)
	{
		pCommand->execute ();
	}
}

void SSW_QuitCommand::execute ()
{
	exit (EXIT_SUCCESS);
}