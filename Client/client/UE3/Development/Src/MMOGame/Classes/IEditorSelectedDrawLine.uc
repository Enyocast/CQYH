//
// IEditorSelectedDrawLine
//
interface IEditorSelectedDrawLine
	native;

cpptext
{
	virtual void DrawEditorDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags = 0) = 0;
}