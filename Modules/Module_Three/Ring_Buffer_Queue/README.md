Originally I was using a dynamic allocation to get storage for the objects that would live in the container, however after getting some feedback from the C/C++ discord, 
I changed the implementation to std::array (as the previous implementation was fixed-size anyway). Because std::array will default-construct N elements of type T when created,
I no longer needed to do any construct_at because re-construction of initialized memory is UB as I understand it. 
Same goes with destroy_at, std::array will handle deconstruction at the end of the scope.

For objects that are going to be written over this is fine because the copy assignmenet operator (should) will handle all the cleanup necessary before copying another object into the memory.
