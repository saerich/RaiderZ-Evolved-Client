/*
* Copyright 2010 Autodesk, Inc.  All rights reserved.
* Use of this software is subject to the terms of the Autodesk license agreement provided at the time of installation or download, 
* or which otherwise accompanies this software in either electronic or hard copy form.
*/

	


/*!	\file
	\ingroup kyruntime_pathfinding */

// primary contact: LAPA - secondary contact: NOBODY
#ifndef KY_LPFSHORTCUT_SIMPLEJUMP_H
#define KY_LPFSHORTCUT_SIMPLEJUMP_H

#include <kyruntime/pathfinding/ilpfshortcut.h>


namespace Kaim
{
/*!	This implementation of the ILpfShortcut interface causes the PathFinder to shortcut through 
	an \LpfArea whenever both of the following conditions are true:
	-	The straight-line distance of the shortcut (from the point at which the global path first enters the \LpfArea 
		to the point at which the path finally leaves the \LpfArea) is less than a distance threshold set through
		DistMax(KyFloat32). 
	-	The direct line of the shortcut is not blocked by any obstacles present in the static NavMesh, in 
		any blocking layer set for the CanGo_NavMesh modifier, or by any blocking PathObject. 
	\pp When a Bot chooses to shortcut through an \LpfArea, the Goto() method in this implementation causes 
	the Bot to jump over the \LpfArea at half of its forward movement speed. Note that the Action used by 
	your Bot must have the ActionVerticalSpeed class of ActionAttribute assigned in order for the Bot to perform the 
	vertical component of the movement generated by LpfShortcut_SimpleJump.
	\pp Note that this class is a very basic implementation of ILpfShortcut primarily intended to serve as an example for your 
	own classes.
	\ingroup kyruntime_pathfinding */
class LpfShortcut_SimpleJump: public ILpfShortcut
{
public:
	KY_DECLARE_LPFSHORTCUT(LpfShortcut_SimpleJump)


public:
	/*!	\label_constructor */
	LpfShortcut_SimpleJump():
		ILpfShortcut(),
		m_distMax(5.0f),
		m_inUse(KY_FALSE) {}

	virtual void ReInit() {m_inUse = KY_FALSE;};

	virtual KyBool GetCost(Bot* bot, const PointWrapper& from, const PointWrapper& to, 
		IConstraint& constraint, KyFloat32& cost);

	virtual KyBool CanLeave(const Bot& entity);

	virtual void InitShortcut(Vec3fList* localPath);
	virtual void ReleaseShortcut();

	virtual KyBool Goto(const PointWrapper& targetPoint, Action& action);

	/*! Retrieves the value set through a call to DistMax(KyFloat32). */
	KyFloat32 DistMax() const { return m_distMax; }

	/*! Sets the distance threshold above which the Bot will not attempt to shortcut through an \LpfArea.
		\units			meters
		\acceptedvalues	any positive value
		\defaultvalue	\c 5.0f */
	void DistMax(KyFloat32 val)
	{ 
		KY_FUNCTION("LpfShortcut_SimpleJump::DistMax");
		KY_ASSERT(val > 0.f, ("Invalid value (%.2f), 'DistMax' must be > 0.", val));
		m_distMax = val;
	}

protected:
	virtual KyResult CheckModifierDependencies(const Modifiers&,const Kaim::ILpfManager::LpfContext*);
	virtual void OnSetPathFinder() {}

	// Parameters
	KyFloat32 m_distMax; /*< Accessor for the \c DistanceMax configuration parameter. */

	// Internals
	KyBool m_inUse; /*< #KY_TRUE if the Bot is currently using the LpfShortcut_SimpleJump Modifier, or #KY_FALSE otherwise. */
	Vec3f m_entryPosition; /*< Set by InitShortcut() to the start of the shortcut (i.e. the first point in the local Path). */
	Vec3f m_exitPosition; /*< Set by InitShortcut() to the end of the shortcut (i.e. the last point in the local Path). */
};

} // namespace Kaim

#endif // KY_LPFSHORTCUT_SIMPLEJUMP_H
