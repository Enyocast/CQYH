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
	     * 查找循序：
	     * 	1、首先根据环境变量 ${project.library.path}
	     * 	2、环境变量 ${project.home}/native
	     * 	3、环境变量 ${project.home}/.
	     * 	4、当前工作路径  
	     * 	5、最后 ${java.library.path}
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
	     * @param parent 当前类库所在的文件夹
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
