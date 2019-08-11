

#find_package(Wayland QUIET)
#if(Wayland_FOUND)
  
#else()
  #find_package(XCB QUIET)
  #if(XCB_FOUND)
    
  #else()
    #find_package(X11 QUIET)
    #if(X11_FOUND)
      
    #else()
      #message(FATAL_ERROR "Could not detect unix window system")
    #endif()
  #endif()
#endif()
