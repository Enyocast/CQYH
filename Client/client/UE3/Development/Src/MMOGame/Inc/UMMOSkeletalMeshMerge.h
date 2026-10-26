
private:
	/**
	 * 
	 */
	UBOOL Validation();

	/**
	*/
	UBOOL MergeMeshes();

	/**
	*/
	UBOOL MergeTextures();

	// need to delete UTexUtil here
	virtual void BeginDestroy();

	UTexture2DDynamic* CreateTargetTexture( UBOOL bSRGB, TextureCompressionSettings cmps );