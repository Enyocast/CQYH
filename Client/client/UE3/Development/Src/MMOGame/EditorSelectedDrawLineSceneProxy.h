#pragma once

class EditorSelectedDrawLineSceneProxy : public FPrimitiveSceneProxy
{
protected:

	typedef TScriptInterface<class IIEditorSelectedDrawLine> IEditorSelectedDrawLine;
	IEditorSelectedDrawLine DrawActor;

public:
	EditorSelectedDrawLineSceneProxy(const UPrimitiveComponent* InComponent)
		: FPrimitiveSceneProxy(InComponent)
	{
		DrawActor = ScriptInterfaceCast<IIEditorSelectedDrawLine>(InComponent->GetOwner());
		check(DrawActor);
	}

	virtual void DrawDynamicElements(FPrimitiveDrawInterface* PDI,const FSceneView* View,UINT DPGIndex,DWORD Flags = 0)
	{
		DrawActor->DrawEditorDynamicElements(PDI, View, DPGIndex, Flags);
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View)
	{
		FPrimitiveViewRelevance Result;
		Result.bDynamicRelevance = TRUE;
		Result.SetDPG( SDPG_UnrealEdForeground,TRUE );
		return Result;
	}

	virtual DWORD GetMemoryFootprint( void ) const { return( sizeof( *this ) + GetAllocatedSize() ); }
	DWORD GetAllocatedSize( void ) const { return( FPrimitiveSceneProxy::GetAllocatedSize() ); }

};