/***************************************************************
 * the interface for the actor who activated a QTE on a player
 *                          -ming
***************************************************************/
Interface IQTEActor;

function QTEStart( MMOPlayerController playerCtrl );

function QTEEnd( MMOPlayerController playerCtrl );

event NotifyKeyDown();