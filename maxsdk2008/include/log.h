//-----------------------------------------------------------------------------
// ----------------
// File ....: log.h
// ----------------
// Author...: Gus Grubba
// Date ....: November 1996
//
// History .: Nov, 27 1996 - Started
//
//-----------------------------------------------------------------------------
		
#ifndef ERRORLOG_H_DEFINED
#define ERRORLOG_H_DEFINED
#include "maxheap.h"

#define NO_DIALOG		FALSE
#define DISPLAY_DIALOG	TRUE

#define	SYSLOG_ERROR		0x00000001
#define	SYSLOG_WARN			0x00000002
#define	SYSLOG_INFO			0x00000004
#define	SYSLOG_DEBUG		0x00000008
#define SYSLOG_BROADCAST	0x00010000
#define SYSLOG_MR			0x00020000

#define	SYSLOG_LIFE_EVER	0
#define	SYSLOG_LIFE_DAYS	1
#define	SYSLOG_LIFE_SIZE	2

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//--   Frame   Range
//
	
/*! \sa  Class Interface.\n\n
\par Description:
MAX maintains a log file that contains the text of error / warning /
information / debug messages generated by the system and plug-ins. This class
is used to work with the log and send messages to it. The log file is placed in
the <b>Network</b> directory and is called <b>Max.Log</b>. To access this
facility from anywhere in MAX use the pointer returned fro the method
<b>Interface::Log()</b>. All methods of this class are implemented by the
system.  */
class LogSys: public MaxHeapOperators {

		DWORD	valTypes;
		int		logLife;
		DWORD	logDays;
		DWORD	logSize;

	 public:

		//-- Maintenance methods -----------------------------------------------
		//
		//	 Methods used internally

		//-- Queries what log types are enabled

		/*! \remarks This method is used to find out what log types are
		enabled . See
		<a href="ms-its:listsandfunctions.chm::/idx_R_list_of_system_error_log_message_types.html">List of
		System Error Log Message Types</a>. The type values are ORed together
		to create the value returned. */
		virtual		DWORD	LogTypes ( ) { return valTypes; }

		//-- Sets what log types are enabled

		/*! \remarks This method is used to set the log types that are
		enabled.
		\par Parameters:
		<b>DWORD types</b>\n\n
		See <a href="ms-its:listsandfunctions.chm::/idx_R_list_of_system_error_log_message_types.html">List of
		System Error Log Message Types</a>. */
		virtual		void	SetLogTypes ( DWORD types ) { valTypes = types; }

		//-- Logging methods ---------------------------------------------------
		//
		//	 "type"	defines the type of log entry based on LogTypes above.
		//
		//   "dialogue" is DISPLAY_DIALOGUE if you want the message to be displayed
		//   in a dialogue. The system will determine if displaying a dialogue is
		//   appropriate based on network rendering mode. If this is just some
		//   information you don't want a dialogue for, or if you are handling
		//   the dialogue yourself, just set dialogue to NO_DIALOGUE.
		//
		//
		//   "title" is optional. If non NULL, it will be used to define the module
		//   that originated the log entry (and the title bar in the dialogue).
		//
		//
	 
		/*! \remarks This method is used to log the error.
		\par Parameters:
		<b>DWORD type</b>\n\n
		Defines the type of log entry. See
		<a href="ms-its:listsandfunctions.chm::/idx_R_list_of_system_error_log_message_types.html">List of
		System Error Log Message Types</a>.\n\n
		<b>BOOL dialogue</b>\n\n
		One of the following values:\n\n
		<b>NO_DIALOG</b>\n\n
		If this entry is just some information you don't want a dialogue for,
		or if you are handling the dialogue yourself use this value.\n\n
		<b>DISPLAY_DIALOG</b>\n\n
		Use this value if you want the message to be displayed in a dialogue.
		The system will determine if displaying a dialogue is appropriate based
		on network rendering mode.\n\n
		<b>MCHAR *title</b>\n\n
		This title string is optional. If non NULL, it will be used to define
		the module.\n\n
		<b>MCHAR *text,...</b>\n\n
		This parameter (and any other additional arguments that follow) make up
		the format specification. The format matches the standard C printf()
		function.
		\par Sample Code:
		<b>TheManager-\>Max()-\>Log()-\>LogEntry(SYSLOG_ERROR, NO_DIALOG, NULL,
		_T("%s - %s\n"), ShortDesc(), errText);</b> */
		virtual		void	LogEntry		( DWORD type, BOOL dialogue, TCHAR *title, TCHAR *format,... ) = 0;

		//-- By turning on quiet mode the log system will not display any dialogues
		//-- even if it is not noetwork rendering.
		//-- The error will only be written to the log file.
		/*! \remarks This method is available in release 3.0 and later
		only.\n\n
		Enables or disables 'quiet' mode. When set to quiet mode, the
		<b>LogSys::LogEntry(...)</b> method will not bring up any dialog boxes
		-- it will act as it does in network rendering mode. Note: After
		setting quiet mode, do not forget to clear it when you are done, since
		the user will not see any error messages from the renderer while quiet
		mode is enabled.
		\par Parameters:
		<b>bool quiet</b>\n\n
		TRUE to enable; FALSE to disable. */
		virtual		void	SetQuietMode( bool quiet ) = 0;
		/*! \remarks This method is available in release 3.0 and later
		only.\n\n
		Returns TRUE if 'quiet' mode is enabled or FALSE if it's disabled. See
		<b>SetQuietMode()</b> above. */
		virtual		bool	GetQuietMode( ) = 0;
        
		//! \brief Sets additional output log file on session basis
	    /*! This method defines additional log file in specified location.
		Unlike default max.log file, the output is based on session. 
		If the given file exists, its contents are destroyed.
		\param [in] logName - output file name
	    */
		virtual     void	SetSessionLogName	( TCHAR * logName ) = 0;
		
		//! \brief Retrieves the additional output log file 
	    /*!
		\return - the output file name set in SetSessionLogName() call or NULL if no file specified. 
	    */
		virtual     TCHAR *	GetSessionLogName	( )= 0;

		//-- Log File Longevity ------------------------------------------------

		/*! \remarks Returns the conditions under which the log is deleted.
		\return  One of the following values:\n\n
		<b>SYSLOG_LIFE_EVER</b>\n\n
		The log is never deleted.\n\n
		<b>SYSLOG_LIFE_DAYS</b>\n\n
		This log is maintained for this number of days.\n\n
		<b>SYSLOG_LIFE_SIZE</b>\n\n
		The log is maintained until it reaches this many kilobytes (KB). */
		virtual		int		Longevity		( )				{ return logLife; }
		/*! \remarks Sets the conditions under which the log is deleted.
		\par Parameters:
		<b>int type</b>\n\n
		One of the following values:\n\n
		<b>SYSLOG_LIFE_EVER</b>\n\n
		The log is never deleted.\n\n
		<b>SYSLOG_LIFE_DAYS</b>\n\n
		This log is maintained for this number of days.\n\n
		<b>SYSLOG_LIFE_SIZE</b>\n\n
		The log is maintained until it reaches this many kilobytes (KB). */
		virtual		void	SetLongevity	( int type )	{ logLife = type; }
		/*! \remarks Returns the conditions under which the log is cleared.
		\return  One of the following values:\n\n
		<b>SYSLOG_LIFE_EVER</b>\n\n
		The log is never deleted.\n\n
		<b>SYSLOG_LIFE_DAYS</b>\n\n
		This log is maintained for this number of days.\n\n
		<b>SYSLOG_LIFE_SIZE</b>\n\n
		The log is maintained until it reaches this many kilobytes (KB). */
		virtual		DWORD	LogDays			( )				{ return logDays; }
		/*! \remarks Returns the size of the current log file in kilobytes
		(KB). */
		virtual		DWORD	LogSize			( )				{ return logSize; }
		/*! \remarks Set the number of days the log is maintained.
		\par Parameters:
		<b>DWORD days</b>\n\n
		The number of days to maintain the log. After this many days after
		creation the log is deleted. */
		virtual		void	SetLogDays		( DWORD days ) 	{ logDays = days; }
		/*! \remarks Set the maximum size in kilobytes (KB) of the log file.
		After this size is reached the log file is deleted.
		\par Parameters:
		<b>DWORD size</b>\n\n
		The maximum size in kilobytes (KB) of the log file. */
		virtual		void	SetLogSize		( DWORD size ) 	{ logSize = size; }

		//-- State -------------------------------------------------------------

		/*! \remarks This method is used internally. */
		virtual		void	SaveState		( void ) = 0;
		/*! \remarks This method is used internally. */
		virtual		void	LoadState		( void ) = 0;

};

#endif

//-- EOF: log.h ---------------------------------------------------------------
