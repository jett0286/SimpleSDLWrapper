#pragma once

#include <iostream>
#include <vector>

class SSW_Command
{
	public:
		virtual void execute () = 0;
		virtual void undo ();
};

class SSW_Macro : public SSW_Command
{
	public:
		void addCommand (SSW_Command* pCommand);
		virtual void execute ();
	private:
		std::vector<SSW_Command*> vectorCommands_;
};

class SSW_QuitCommand : public SSW_Command
{
	public:
		virtual void execute ();
};