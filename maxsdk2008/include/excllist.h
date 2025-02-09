#ifndef __EXCLLIST__H
#define __EXCLLIST__H

#include <ioapi.h>

#ifndef NT_INCLUDE
#define NT_INCLUDE			  1
#define NT_AFFECT_ILLUM		  2
#define NT_AFFECT_SHADOWCAST  4
#endif

typedef INode* INodePtr;

/*! \sa  Class INode, Class ILoad,  Class ISave,  Class IMergeManager\n\n
\par Description:
This class is available in release 4.0 and later only.\n\n
This class represents an exclusion list and is a direct parallel to the
NameTab, and converting from using one to the other is fairly simple.  */
class ExclList : public InterfaceServer {
	ULONG flags;
	Tab<ULONG> handles;
	public:
		/*! \remarks Constructor. */
		ExclList() { flags = NT_AFFECT_ILLUM|NT_AFFECT_SHADOWCAST; }
		/*! \remarks Sets the specified flag to the specified value.
		\par Parameters:
		<b>ULONG f</b>\n\n
		The flag(s) to set. One or more of the following values:\n\n
		<b>NT_INCLUDE</b>\n\n
		This bit is used to indicate "Include" mode.\n\n
		<b>NT_AFFECT_ILLUM</b>\n\n
		This bit is used to indicate the "Illumination" check box in the
		exclusion list dialog.\n\n
		<b>NT_AFFECT_SHADOWCAST</b>\n\n
		This bit is used to indicate the "Shadow Casting" check box in the
		exclusion list dialog.\n\n
		<b>BOOL b=1</b>\n\n
		The value to set. */
		void SetFlag(ULONG f, BOOL b=1) { if (b) flags|=f; else flags &= ~f; }
		/*! \remarks Returns TRUE if the specified flag(s) are set; otherwise
		FALSE.
		\par Parameters:
		<b>ULONG f</b>\n\n
		The flag(s) to set. One or more of the following values:\n\n
		<b>NT_INCLUDE</b>\n\n
		This bit is used to indicate "Include" mode.\n\n
		<b>NT_AFFECT_ILLUM</b>\n\n
		This bit is used to indicate the "Illumination" check box in the
		exclusion list dialog.\n\n
		<b>NT_AFFECT_SHADOWCAST</b>\n\n
		This bit is used to indicate the "Shadow Casting" check box in the
		exclusion list dialog. */
		BOOL TestFlag(ULONG f) const { return (flags&f)?1:0; }
		/*! \remarks This method returns the number of handles in the table.
		*/
		int Count() const { return handles.Count(); }
		/*! \remarks Index operator. */
		CoreExport INode* operator[] (const int i);
		/*! \remarks This method allows you to set a specified entry in the
		table to the specified node.
		\par Parameters:
		<b>int i</b>\n\n
		The index in the table.\n\n
		<b>INode *node</b>\n\n
		The node to set. */
		CoreExport void Set(int i, INode *node);
		/*! \remarks Assignment operator. */
		CoreExport ExclList& operator=(const ExclList& e);
		/*! \remarks Assignment operator. */
		CoreExport ExclList& operator=(const NameTab& n);
		/*! \remarks Returns the index of the node passed; otherwise returns
		-1.
		\par Parameters:
		<b>INode *node</b>\n\n
		The node to find. */
		CoreExport int FindNode(INode *node);
		/*! \remarks Appends the specified node to the end of the list.
		\par Parameters:
		<b>INode *node</b>\n\n
		The node to add.
		\return  Returns the number of items in the list prior to appending. */
		CoreExport int AddNode(INode *node);
		/*! \remarks Removes thes node from the list.
		\par Parameters:
		<b>INode *node</b>\n\n
		The node to remove. */
		CoreExport void RemoveNode(INode *node);
		/*! \remarks Removes the 'i-th' name from the list.
		\par Parameters:
		<b>int i</b>\n\n
		Specifies the index of the node to remove. */
		CoreExport void RemoveNode(int i);
		/*! \remarks Sets the size of the list. If the new size is smaller
		than the current size entries are deleted.
		\par Parameters:
		<b>int num</b>\n\n
		Specifies the size of the list. */
		CoreExport void SetSize(int num);     
		/*! \remarks Sets the size of the list. If the new size is smaller
		than the current size entries are deleted.
		\par Parameters:
		<b>int num</b>\n\n
		Specifies the size of the list. */
		void SetCount(int num) { SetSize(num); } 
		/*! \remarks Loads this ExclList from disk.
		\par Parameters:
		<b>ILoad *iload</b>\n\n
		This class provides methods to load data from disk.
		\return  \sa  <a href="ms-its:listsandfunctions.chm::/idx_R_list_of_ioresults.html">List of IO
		Results</a>. */
		CoreExport IOResult Load(ILoad *iload);
		/*! \remarks Saves this ExclList to disk.
		\par Parameters:
		<b>ISave *isave</b>\n\n
		This class provides methods to save data to disk.
		\return  \sa  <a href="ms-its:listsandfunctions.chm::/idx_R_list_of_ioresults.html">List of IO
		Results</a>. */
		CoreExport IOResult Save(ISave *isave);
		/*! \remarks This method takes care of setting the merge manager
		interface.
		\par Parameters:
		<b>IMergeManager* imm</b>\n\n
		A pointer to the merge manager interface. */
		CoreExport void OnMerge(IMergeManager* imm);
	};	

#endif
