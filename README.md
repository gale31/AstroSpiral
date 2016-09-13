## AstroSpiral

The Astro Spiral project presents an innovative way to compare astronomical images of the sky by building a convex spiral (using a modification of the Graham Scan algorithm for convex hull) according to the bright objects in a photo. On that purpose, an application for Windows and Mac OS X, written in C++, is developed using the Cinder toolbox.

### Introduction

How do astronomers find near-Earth asteroids (NEAs)? 

In the night sky, we can see stars shining with their own light - but how do we know they are actually stars? While all sky objects appear bright, some stars and galaxies radiate light, as opposed to the Moon, planets, natural satellites, comets, and near-Earth asteroids, which reflect light. How can we distinguish the two types of objects? 

Below, you can see a background of stars, which are too far from us to observe a difference in position. The asteroid BJ19377, on the other hand, is close enough, so we can see it moving in the sky.

We can detect the movement of asteroids by comparing consecutive astronomical images of the sky.

<img src= "http://iasc.hsutx.edu/images/astro.gif" width="600">

Astronomers have studied the sky in the search of asteroids for nearly 200 years, but they have not managed to find all the asteroids in our solar system yet. The search for asteroids is very important for the development of astronomy. Near-Earth asteroids are of great interest because of the resources of valuable materials which they posses. The danger of collision of the Earth with an asteroid passing close makes the search of asteroids useful to our society, too. Therefore, in recent years the study of asteroids is becoming extremely important as a warning of a possible dangerous collision, upcoming space landing missions and the research and development of asteroid resources.

<img src= "https://i.ytimg.com/vi/fP8qTDIhYUE/maxresdefault.jpg" width="600">

The goal of this project is to create a software that builds a convex spiral according to the bright objects in an astronomical image of the sky. Given a set of astronomical images, taken successively by the same telescope, we can, very intuitively, by looking, find differences in their spirals and thus finding star-like moving objects, which are most likely to be asteroids.

### Wait, what?

Okay, look at those two images. Can you find a difference?

<img src= "https://s10.postimg.org/wiaxqrvjt/IMAGE1.jpg" width="302">
<img src= "https://s10.postimg.org/60kjrvyzd/IMAGE2.jpg" width="300">

What about now?

<img src= "https://s10.postimg.org/8hbwumwux/RESULT1.png" width="302">
<img src= "https://s17.postimg.org/xm43vnyov/RESULT2.png" width="300">

You found the small bright object on the bottom easier, didn't you? Well, that's the goal of this project.

The thing connecting the bright objects on the image is a "convex spiral", which is made by modifiying the Graham Scan algorithm for convex hull. So, I wrote an application which recieves an astronomical image and, following the modified algorithm, draws a convex spiral on it.


