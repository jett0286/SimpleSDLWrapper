#pragma once

#include <iostream>
#include <vector>

class SSW_Command_Base
{
	public:
		virtual void execute () = 0;
		virtual void undo ();
};

class SSW_Command_Macro : public SSW_Command_Base
{
	public:
		void addCommand (SSW_Command_Base* pCommand);
		virtual void execute ();
	private:
		std::vector<SSW_Command_Base*> vectorCommands_;
};

class SSW_Command_Quit : public SSW_Command_Base
{
	public:
		virtual void execute ();
};