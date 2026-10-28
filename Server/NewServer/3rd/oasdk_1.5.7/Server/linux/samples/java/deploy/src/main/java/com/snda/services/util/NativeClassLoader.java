package com.snda.services.util;

import java.io.File;
import java.lang.reflect.Method;

import org.apache.log4j.Logger;

/**
 * 
 * @author StructChen
 *
 */
public class NativeClassLoader {
	private static Logger logger = Logger.getLogger(NativeClassLoader.class);
	   public static File findLibrary(File parent,String libraryName){
	    	String s = System.mapLibraryName(libraryName);
	    	return new File(parent,s);
	    }
	    
	    /**
	     * Search order:
	     * 	1. Environment variable ${project.library.path}
	     * 	2. Environment variable ${project.home}/native
	     * 	3. Environment variable ${project.home}/.
	     * 	4. Current working directory
	     * 	5. Finally, ${java.library.path}
	     * @param libraryName
	     */
	    public static void loadLibrary(String libraryName){
	    	String projectLibraryPath = System.getProperty("project.library.path");
	    	File libraryFile = null;
	    	boolean loaded = false;
	    	if(projectLibraryPath != null){
	    		libraryFile = findLibrary(new File(projectLibraryPath),libraryName);
	    		if(libraryFile.exists()){
	    			loadLibrary(libraryFile.getParentFile(),libraryName);
	    			loaded = true;
	    		}else{
	    			loaded = loadFromHomePath(libraryName);
	    		}
	    	}else{
	    		loaded = loadFromHomePath(libraryName);
	    	}
	    	
	    	if(!loaded){
	    		libraryFile = findLibrary(new File("."),libraryName);
				if(libraryFile.exists()){
					loadLibrary(libraryFile.getParentFile(),libraryName);
				}else{
					System.loadLibrary(libraryName);
					logger.info("libraryName="+System.mapLibraryName(libraryName)+" load from system path");
				}
	    	}
	    }
	    
	    private static boolean loadFromHomePath(String libraryName){
	    	File libraryFile = null;
	    	String projectHome = System.getProperty("project.home");
			if(projectHome != null){
				libraryFile = findLibrary(new File(projectHome,"native"),libraryName);
				if(libraryFile.exists()){
					loadLibrary(libraryFile.getParentFile(),libraryName);
					logger.info("loaded from "+libraryFile.getAbsolutePath());
					return true;
				}else{
					libraryFile = findLibrary(new File(projectHome),libraryName);
					if(libraryFile.exists()){
						loadLibrary(libraryFile.getParentFile(),libraryName);
						logger.info("loaded from "+libraryFile.getAbsolutePath());
						return true;
					}
				}
			}
			return false;
	    }
	    
	    /**
	     * 
	     * @param parent directory containing the library
	     * @param libraryName
	     */
	    public static void loadLibrary(File parent,String libraryName){
	    	Method llm;
	    	try {
		    	llm = ClassLoader.class.getDeclaredMethod("loadLibrary0", new Class[]{Class.class,File.class});
		    	llm.setAccessible(true);
		    	File lib = findLibrary(parent,libraryName);
		    	if(!lib.exists()){
		    		logger.error("loadLibrary error,File not found:"+lib.getAbsolutePath());
		    		throw new RuntimeException("File not found:"+lib.getAbsolutePath());
		    	}
		    	llm.invoke(null, new Object[]{NativeClassLoader.class,lib});
		    	logger.info("loaded from "+lib.getAbsolutePath());
	    	} catch (Exception e) {
	    		throw new RuntimeException(e);
	    	}
	    }
}
