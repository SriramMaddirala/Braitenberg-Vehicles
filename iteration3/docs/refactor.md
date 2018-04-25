The files being changed are arena.cc and arena.h
The method being changed is Arena::UpdateEntitiesTimestep()
The methods being added are Arena::CheckRobotsWall(), Arena::CheckRobotsCollision()
and Arena::CheckLightsCollision()
The changes occur at lines 108,109,110, 113-125, 127-157 and 159-174 of arena.cc and 155,157,159 of arena.h
At 108 instead of the code to iterate through robot entites checking for wall there 
is a method call for CheckRobotsWall() 
At 109 instead of the code to iterate through robot entites checking for collisions there 
is a method call for CheckRobotsCollision()
At 110 instead of the code to iterate through all entites checking for collisions between
other lights there is a method call for CheckLightsCollision()
These methods are declared at 155, 157, 158 of arena.h respectively
From 113-125 is CheckRobotsWall(). It iterates through robot entites checking for wall
From 127-157 is CheckRobotsCollison(). It iterates through robot entities checking for collisons
From 159-174 is CheckLightCollision(). It iterates through all Entities checking for collisions between lights

This change enhances the readability of my code as well as the structure and logic of my code greatly.
My UpdateEntitiesTimestep method was far too large, far too unsightly and fairly opaque as to the structure of 
the multiple similarly constructed but conditional and method call indundated loops running through entities.
It clearly divides the work previously done in UpdateEntitiesTimestep into three sections, each with its own functionality
that can be checked for in the final product and tested. This is a far more systematic option to having all that code ,which is standalone
and each one implementing a separate function, haphazardly tossed into one function instead of encapsulating it into individual methods.
