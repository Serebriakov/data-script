set (src 
  main.cpp 
  scanner_test.cpp
  )
set (hdr catch.hpp)
onyx_exec (unittest src hdr)
