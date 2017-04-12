Ashley Currie 10159991


CPSC 587 Assignment 4 : User Manual


This a program which simulates flock behavior. The triangles called boids try to stay in close proximity to eachother and match eachothers velocity while 
avoiding colliding with one another. The simulation requires a value for a radius of avoidance, cohesion, and gathering as well as maximum values for force and velocity and a time increment.
The radius of avoidance will determine how many boids a single boid will try to avoid around it. A large value means it will be avoiding a larger number of it's neighbouring boids. 
The radius of cohesion determines how many boids an individual boid will be trying to stay close to. A larger value decreases the chance that the flock will break into smaller groups. 
The radius of gathering decides how many neighbouring boids a single boid will try to match it's velocity with. A higher value will mean that the boids will have a more consistent speed. 
The maximum force and velocity values tell the program how fast you would like the boids to be able to move and how much force will be applied to individual boids to enforce the rules above. 
Higher values will result in faster boids. The time increment tells the program how fast it should run. These values can be set in the file sim1.txt. 
The parameters were mentioned in this manual in the same order that they are listed in the file. To run the simulation open a terminal and navigate to where the .cpp files are located. 
Type in the command "make" and then type in the command "./Main".

This simulation was based on the psuedo code provided at this link: http://www.kfish.org/boids/pseudocode.html.