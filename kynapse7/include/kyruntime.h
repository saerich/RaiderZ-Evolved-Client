/*
* Copyright 2010 Autodesk, Inc.  All rights reserved.
* Use of this software is subject to the terms of the Autodesk license agreement provided at the time of installation or download, 
* or which otherwise accompanies this software in either electronic or hard copy form.
*/

/*! \file 
	\brief Includes all necessary files for integrating \SDKName into your \gameOrSim at runtime. */

#ifndef KyRuntime_GlobalInclude_H
#define KyRuntime_GlobalInclude_H

#include <kyruntime/agents/agentutils.h>
#include <kyruntime/agents/fleeagent.h>
#include <kyruntime/agents/fleeingtraversal.h>
#include <kyruntime/agents/fleeingtraversalconfig.h>
#include <kyruntime/agents/followagent.h>
#include <kyruntime/agents/gotoagent.h>
#include <kyruntime/agents/hideagent.h>
#include <kyruntime/agents/hidingtraversal.h>
#include <kyruntime/agents/hidingtraversalconfig.h>
#include <kyruntime/agents/shootagent.h>
#include <kyruntime/agents/testagent.h>
#include <kyruntime/agents/wanderagent.h>
#include <kyruntime/agents/wandertraversal.h>
#include <kyruntime/agents/wandertraversalconfig.h>
#include <kyruntime/asyncmanagement/asyncmanager.h>
#include <kyruntime/asyncmanagement/asyncmodule.h>
#include <kyruntime/attributes/actionacceleration.h>
#include <kyruntime/attributes/actioncrouch.h>
#include <kyruntime/attributes/actionforceposition.h>
#include <kyruntime/attributes/actionjump.h>
#include <kyruntime/attributes/actionrotate.h>
#include <kyruntime/attributes/actionshoot.h>
#include <kyruntime/attributes/actionspeed.h>
#include <kyruntime/attributes/actionsteering.h>
#include <kyruntime/attributes/actiontorsorotate.h>
#include <kyruntime/attributes/actionverticalspeed.h>
#include <kyruntime/attributes/bodycanfly.h>
#include <kyruntime/attributes/bodyeyeposition.h>
#include <kyruntime/attributes/bodygunposition.h>
#include <kyruntime/attributes/bodyheaddirection.h>
#include <kyruntime/attributes/bodymaxspeed.h>
#include <kyruntime/attributes/bodyteamside.h>
#include <kyruntime/attributes/bodytorsoorientation.h>
#include <kyruntime/attributes/bodyvisualacuteness.h>
#include <kyruntime/attributes/pathobjectoutline.h>
#include <kyruntime/bodyinfomanagement/bodyinfo.h>
#include <kyruntime/bodyinfomanagement/bodyinfofilter.h>
#include <kyruntime/bodyinfomanagement/bodyinfomanager.h>
#include <kyruntime/bodyinfomanagement/distancefilter.h>
#include <kyruntime/bodyinfomanagement/frustumfilter.h>
#include <kyruntime/bodyinfomanagement/unconditionalfilter.h>
#include <kyruntime/core/action.h>
#include <kyruntime/core/bitarray.h>
#include <kyruntime/core/body.h>
#include <kyruntime/core/bot.h>
#include <kyruntime/core/circulararray.h>
#include <kyruntime/core/collision.h>
#include <kyruntime/core/contiguousarray.h>
#include <kyruntime/core/engine.h>
#include <kyruntime/core/global.h>
#include <kyruntime/core/inextmovemanager.h>
#include <kyruntime/core/infolib.h>
#include <kyruntime/core/iworldobserver.h>
#include <kyruntime/core/metaclass.h>
#include <kyruntime/core/pointinfo.h>
#include <kyruntime/core/pointinfo_body.h>
#include <kyruntime/core/pointinfo_entity.h>
#include <kyruntime/core/pointwrapper.h>
#include <kyruntime/core/service.h>
#include <kyruntime/core/shape.h>
#include <kyruntime/core/stringmap.h>
#include <kyruntime/core/team.h>
#include <kyruntime/core/timemanager.h>
#include <kyruntime/core/varrestorer.h>
#include <kyruntime/core/world.h>
#include <kyruntime/core/worldutils.h>
#include <kyruntime/debugger/debuggerbody.h>
#include <kyruntime/debugger/debuggerbuffer.h>
#include <kyruntime/debugger/debuggerbyteconverter.h>
#include <kyruntime/debugger/debuggerdump.h>
#include <kyruntime/debugger/debuggererrorutils.h>
#include <kyruntime/debugger/debuggererrorvalues.h>
#include <kyruntime/debugger/debuggerlocalmemoryreader.h>
#include <kyruntime/debugger/debuggerlogbuffer.h>
#include <kyruntime/debugger/debuggermemorychunk.h>
#include <kyruntime/debugger/debuggermemoryhandle.h>
#include <kyruntime/debugger/debuggernetarray.h>
#include <kyruntime/debugger/debuggernetbuffer.h>
#include <kyruntime/debugger/debuggernetbyteconverter.h>
#include <kyruntime/debugger/debuggernetfield.h>
#include <kyruntime/debugger/debuggernetfieldcollection.h>
#include <kyruntime/debugger/debuggernetipendpoint.h>
#include <kyruntime/debugger/debuggernetmessage.h>
#include <kyruntime/debugger/debuggernetmessagestore.h>
#include <kyruntime/debugger/debuggernetserver.h>
#include <kyruntime/debugger/debuggernetserverconfig.h>
#include <kyruntime/debugger/debuggernetsocket.h>
#include <kyruntime/debugger/debuggerobjecthandle.h>
#include <kyruntime/debugger/debuggerpathobject.h>
#include <kyruntime/debugger/debuggersharedcamera.h>
#include <kyruntime/debugger/debuggershareddrawing.h>
#include <kyruntime/debugger/debuggersharedlog.h>
#include <kyruntime/debugger/debuggertypes.h>
#include <kyruntime/debugger/debuggervector3d.h>
#include <kyruntime/debugger/remotedebugging.h>
#include <kyruntime/finitestatemachine/defaultstate.h>
#include <kyruntime/finitestatemachine/defaulttransition.h>
#include <kyruntime/finitestatemachine/fsm.h>
#include <kyruntime/finitestatemachine/istate.h>
#include <kyruntime/finitestatemachine/itransition.h>
#include <kyruntime/gapda/gapmanager.h>
#include <kyruntime/gapda/goto_asyncgapda.h>
#include <kyruntime/gapda/goto_asyncgapda_asyncmodule.h>
#include <kyruntime/gapda/goto_asyncgapda_asyncmodule_st.h>
#include <kyruntime/gapda/goto_gapda.h>
#include <kyruntime/graph/additionalgraphstitcher.h>
#include <kyruntime/graph/additionalstitchedgraph.h>
#include <kyruntime/graph/astarcontext.h>
#include <kyruntime/graph/astartraversal.h>
#include <kyruntime/graph/astartraversalconfig.h>
#include <kyruntime/graph/blob/virtualgraphblob.h>
#include <kyruntime/graph/blob/virtualgraphedgeblob.h>
#include <kyruntime/graph/blob/virtualgraphedgeblobbuilder.h>
#include <kyruntime/graph/blob/virtualgraphlinkblob.h>
#include <kyruntime/graph/blob/virtualgraphlinkblobbuilder.h>
#include <kyruntime/graph/blob/virtualgraphvertexblob.h>
#include <kyruntime/graph/blob/virtualgraphvertexblobbuilder.h>
#include <kyruntime/graph/connectvertex.h>
#include <kyruntime/graph/database.h>
#include <kyruntime/graph/databasemanager.h>
#include <kyruntime/graph/databasemanagercallbacks.h>
#include <kyruntime/graph/edgedata.h>
#include <kyruntime/graph/edgeiteratoraroundvertex.h>
#include <kyruntime/graph/edgeiteratorinworld.h>
#include <kyruntime/graph/edgelocker.h>
#include <kyruntime/graph/edgelockervolume.h>
#include <kyruntime/graph/graphcellgrid.h>
#include <kyruntime/graph/graphcellgridcallbacks.h>
#include <kyruntime/graph/graphcellptr.h>
#include <kyruntime/graph/graphcellsafeptr.h>
#include <kyruntime/graph/graphcellstitcher.h>
#include <kyruntime/graph/graphconstraints.h>
#include <kyruntime/graph/graphedgeptr.h>
#include <kyruntime/graph/graphedgesafeptr.h>
#include <kyruntime/graph/graphmanager.h>
#include <kyruntime/graph/graphmanagervisualrepresentation.h>
#include <kyruntime/graph/graphsafeptr.h>
#include <kyruntime/graph/graphstitchdatamanager.h>
#include <kyruntime/graph/graphvertexptr.h>
#include <kyruntime/graph/graphvertexsafeptr.h>
#include <kyruntime/graph/nearestedges.h>
#include <kyruntime/graph/nearestvertices.h>
#include <kyruntime/graph/path.h>
#include <kyruntime/graph/pointinfo_astarid.h>
#include <kyruntime/graph/pointinfo_vertexptr.h>
#include <kyruntime/graph/pointinfo_vertexsafeptr.h>
#include <kyruntime/graph/propagationtraversal.h>
#include <kyruntime/graph/propagationtraversalconfig.h>
#include <kyruntime/graph/stitchedgraph.h>
#include <kyruntime/graph/stitchedgraphcell.h>
#include <kyruntime/graph/traversal.h>
#include <kyruntime/graph/traversalconfig.h>
#include <kyruntime/graph/traversalmanager.h>
#include <kyruntime/graph/vertexdata.h>
#include <kyruntime/graph/vertexiteratorinworld.h>
#include <kyruntime/graph/virtualedge.h>
#include <kyruntime/lpf/ilpfmanager.h>
#include <kyruntime/lpf/ilpfmodule.h>
#include <kyruntime/lpf/lpfconstraint.h>
#include <kyruntime/lpf/lpfmanager.h>
#include <kyruntime/lpf/lpfmodule.h>
#include <kyruntime/mesh/inavmeshaccessor.h>
#include <kyruntime/mesh/inavmeshlayer.h>
#include <kyruntime/mesh/iobstacleaccessor.h>
#include <kyruntime/mesh/navmeshaccessor_database.h>
#include <kyruntime/mesh/navmeshlayerlocation.h>
#include <kyruntime/mesh/navmeshlayermanager.h>
#include <kyruntime/mesh/navmeshlayerquery.h>
#include <kyruntime/mesh/navmeshqueryserverwrapper.h>
#include <kyruntime/mesh/obstacleaccessor_pathobjectoutline.h>
#include <kyruntime/mesh/obstaclelayer.h>
#include <kyruntime/mesh/obstaclelayerblobbuilder.h>
#include <kyruntime/mesh/obstacleprojectionvolume.h>
#include <kyruntime/mesh/pointinfo_navtrianglesafeptr.h>
#include <kyruntime/mesh/polygonmerger_grid.h>
#include <kyruntime/mesh/polygonmerger_polygon.h>
#include <kyruntime/obstaclemanagement/ioutlineupdatepolicy.h>
#include <kyruntime/obstaclemanagement/obstacle.h>
#include <kyruntime/obstaclemanagement/obstaclemanager.h>
#include <kyruntime/obstaclemanagement/obstacleoutline.h>
#include <kyruntime/obstaclemanagement/outlineupdatepolicy_movementanalysis.h>
#include <kyruntime/obstaclemanagement/projectedoutline.h>
#include <kyruntime/obstaclemanagement/shapeobb.h>
#include <kyruntime/obstaclemanagement/shapepolyline.h>
#include <kyruntime/pathfinding/cango_navmesh.h>
#include <kyruntime/pathfinding/cango_raycast.h>
#include <kyruntime/pathfinding/checkdirectway_distance.h>
#include <kyruntime/pathfinding/checkdirectway_trivial.h>
#include <kyruntime/pathfinding/computetargetpoint_queue.h>
#include <kyruntime/pathfinding/computetargetpoint_shortcut.h>
#include <kyruntime/pathfinding/computetargetpoint_trivial.h>
#include <kyruntime/pathfinding/detectaccident_predictmove.h>
#include <kyruntime/pathfinding/detectgoalchanged_distance3d.h>
#include <kyruntime/pathfinding/detectgoalreached_distance2d5.h>
#include <kyruntime/pathfinding/detectgoalreached_distance3d.h>
#include <kyruntime/pathfinding/detectgoalreached_dontqueue.h>
#include <kyruntime/pathfinding/detectpathnodereached_distance2d5.h>
#include <kyruntime/pathfinding/detectpathnodereached_distance3d.h>
#include <kyruntime/pathfinding/edgestatusawareness_distance2dandtime.h>
#include <kyruntime/pathfinding/findnodesfrompositions_asyncnearestreachable.h>
#include <kyruntime/pathfinding/findnodesfrompositions_asyncnearestreachable_asyncmodule.h>
#include <kyruntime/pathfinding/findnodesfrompositions_asyncnearestreachable_asyncmodule_st.h>
#include <kyruntime/pathfinding/findnodesfrompositions_default.h>
#include <kyruntime/pathfinding/findnodesfrompositions_nearestreachable.h>
#include <kyruntime/pathfinding/goto_repulsordynamicavoidance.h>
#include <kyruntime/pathfinding/goto_trivial.h>
#include <kyruntime/pathfinding/icango.h>
#include <kyruntime/pathfinding/icheckdirectway.h>
#include <kyruntime/pathfinding/icomputetargetpoint.h>
#include <kyruntime/pathfinding/idetectaccident.h>
#include <kyruntime/pathfinding/idetectgoalchanged.h>
#include <kyruntime/pathfinding/idetectgoalreached.h>
#include <kyruntime/pathfinding/idetectpathnodereached.h>
#include <kyruntime/pathfinding/iedgestatusawareness.h>
#include <kyruntime/pathfinding/ifindnodesfrompositions.h>
#include <kyruntime/pathfinding/igoto.h>
#include <kyruntime/pathfinding/ilpfshortcut.h>
#include <kyruntime/pathfinding/imodifier.h>
#include <kyruntime/pathfinding/irefinegoal.h>
#include <kyruntime/pathfinding/iselectpathnodecandidate.h>
#include <kyruntime/pathfinding/isteering.h>
#include <kyruntime/pathfinding/lpfpremerger_grid.h>
#include <kyruntime/pathfinding/lpfpremerger_grid_config.h>
#include <kyruntime/pathfinding/lpfpremerger_polygon.h>
#include <kyruntime/pathfinding/lpfpremerger_polygon_config.h>
#include <kyruntime/pathfinding/lpfshortcut_simplejump.h>
#include <kyruntime/pathfinding/modifiers.h>
#include <kyruntime/pathfinding/pathfinder.h>
#include <kyruntime/pathfinding/refinegoal_adjustaltitude.h>
#include <kyruntime/pathfinding/refinegoal_lpfcompatible.h>
#include <kyruntime/pathfinding/refinegoal_nearestinsidenavmesh.h>
#include <kyruntime/pathfinding/refinegoal_outsidenavmesh.h>
#include <kyruntime/pathfinding/refinegoal_trivial.h>
#include <kyruntime/pathfinding/selectpathnodecandidate_asyncnextpathnode.h>
#include <kyruntime/pathfinding/selectpathnodecandidate_asyncnextpathnode_asyncmodule.h>
#include <kyruntime/pathfinding/selectpathnodecandidate_asyncnextpathnode_asyncmodule_st.h>
#include <kyruntime/pathfinding/selectpathnodecandidate_nextpathnode.h>
#include <kyruntime/pathfinding/smoothablepathobjecttraverseinfo.h>
#include <kyruntime/pathfinding/steering_fly.h>
#include <kyruntime/pathfinding/steering_simplebiped.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/basepathobjectfsm.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/state_approaching.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/state_blocked.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/state_escaping.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/state_traversing.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_approach_exit.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_approach_traverse.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_blocked_exit.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_escape_blocked.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_escape_exit.h>
#include <kyruntime/pathobjects/finitestatemachine_pathobject/transition_traverse_exit.h>
#include <kyruntime/pathobjects/ipathobject.h>
#include <kyruntime/pathobjects/ipathobjectbehavior.h>
#include <kyruntime/pathobjects/offtheshelf/approaches/queueapproach.h>
#include <kyruntime/pathobjects/offtheshelf/basepathobject.h>
#include <kyruntime/pathobjects/offtheshelf/basepathobjectbehavior.h>
#include <kyruntime/pathobjects/offtheshelf/door/doorgameobject.h>
#include <kyruntime/pathobjects/offtheshelf/door/doorpathobject.h>
#include <kyruntime/pathobjects/offtheshelf/door/doorpathobjectbehavior.h>
#include <kyruntime/pathobjects/offtheshelf/imove.h>
#include <kyruntime/pathobjects/offtheshelf/jump/jumpgameobject.h>
#include <kyruntime/pathobjects/offtheshelf/jump/jumppathobject.h>
#include <kyruntime/pathobjects/offtheshelf/jump/jumppathobjectbehavior.h>
#include <kyruntime/pathobjects/offtheshelf/ladder/laddergameobject.h>
#include <kyruntime/pathobjects/offtheshelf/ladder/ladderpathobject.h>
#include <kyruntime/pathobjects/offtheshelf/ladder/ladderpathobjectbehavior.h>
#include <kyruntime/pathobjects/offtheshelf/ladder/laddertraversebehavior.h>
#include <kyruntime/pathobjects/offtheshelf/ladder/laddertraversefsm.h>
#include <kyruntime/pathobjects/offtheshelf/moves/jumpmove.h>
#include <kyruntime/pathobjects/offtheshelf/moves/rotatemove.h>
#include <kyruntime/pathobjects/offtheshelf/moves/rotatemove_smooth.h>
#include <kyruntime/pathobjects/offtheshelf/moves/teleportmove.h>
#include <kyruntime/pathobjects/offtheshelf/moves/translationmove.h>
#include <kyruntime/pathobjects/offtheshelf/moves/translationmove_2D.h>
#include <kyruntime/pathobjects/offtheshelf/pathobjectbehaviorcontext.h>
#include <kyruntime/pathobjects/offtheshelf/teleporter/teleportergameobject.h>
#include <kyruntime/pathobjects/offtheshelf/teleporter/teleporterpathobject.h>
#include <kyruntime/pathobjects/offtheshelf/teleporter/teleporterpathobjectbehavior.h>
#include <kyruntime/pathobjects/pathobject.h>
#include <kyruntime/pathobjects/pathobjectlayer.h>
#include <kyruntime/pathobjects/pathobjectmanager.h>
#include <kyruntime/pathobjects/pathobjectsmoothquery.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/pointinfo_connexionspace.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/pointinfo_controlspace.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjectblobbuilder.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjectconnexionlink.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjectconnexionspace.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjectcontrolspace.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjectdata.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjecttopology.h>
#include <kyruntime/pathobjects/runtimepathobjecttopology/runtimepathobjecttopologyblobbuilder.h>
#include <kyruntime/perceptions/bodyinfo_distance.h>
#include <kyruntime/perceptions/bodyinfo_hostility.h>
#include <kyruntime/perceptions/bodyinfo_nearestbody.h>
#include <kyruntime/perceptions/bodyinfo_nearestenemy.h>
#include <kyruntime/perceptions/bodyinfo_nearestseenbody.h>
#include <kyruntime/perceptions/bodyinfo_nearestseenenemy.h>
#include <kyruntime/perceptions/bodyinfo_nearestvisiblebody.h>
#include <kyruntime/perceptions/bodyinfo_nearestvisibleenemy.h>
#include <kyruntime/perceptions/bodyinfo_sight.h>
#include <kyruntime/perceptions/bodyinfo_visibility.h>
#include <kyruntime/perceptions/pointlockmanager.h>
#include <kyruntime/spawnmanagement/spawnmanager.h>
#include <kyruntime/spawnmanagement/spawnquery.h>

#endif //KyRuntime_GlobalInclude_H
